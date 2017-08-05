//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  RUBELayer
//
//  See header file for description.
//

#include "RUBELayer.h"
#include "rubestuff/b2dJson.h"
#include "rubestuff/b2dJsonImage.h"
#include "H/Source.h"
#include "H/GameScene.h"

using namespace std;
using namespace cocos2d;
b_RUBELayer *b_RUBELayer::sfptr = nullptr;

b_RUBELayer * b_RUBELayer::create(const std::string & map)
{
	b_RUBELayer * ret = new (std::nothrow) b_RUBELayer();
	if (ret && ret->init(map))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);

	return ret;
}


// Override superclass to set different starting offset
Point b_RUBELayer::initialWorldOffset()
{
    // If you are not sure what to set the starting position as, you can
    // pan and zoom the scene until you get the right fit, and then set
    // a breakpoint in the draw or update methods to see what the values
    // of [self scale] and [self position] are.
    //
    // For the images.json scene, I did this on my iPad in landscape (1024x768)
    // and came up with a value of 475,397 for the position. Since the
    // offset is measured in pixels, we need to set this as a percentage of
    // the current screen height instead of a fixed value, to get the same
    // result on different devices.
    // 
    return Vec2::ZERO;
}


// Override superclass to set different starting scale
float b_RUBELayer::initialWorldScale()
{
    return GSInst->getPhysWorldScale(); //screen will be 35 physics units high
}


// This is called after the Box2D world has been loaded, and while the b2dJson information
// is still available to do extra loading. Here is where we load the images.
void b_RUBELayer::afterLoadProcessing(b2dJson* json)
{
    // fill a vector with all images in the RUBE scene
    std::vector<b2dJsonImage*> b2dImages;
    json->getAllImages(b2dImages);
        
    // loop through the vector, create Sprites for each image and store them in m_imageInfos
    for (int i = 0; i < b2dImages.size(); i++) {
        b2dJsonImage* img = b2dImages[i];
        log("Loading image: %s", img->file.c_str());
        
        // try to load the sprite image, and ignore if it fails
        Sprite* sprite = Sprite::create(img->file.c_str());
        if ( ! sprite ){
		log("image %s loading error", img->file.c_str());
            continue;
	}
        
        // add the sprite to this layer and set the render order
        addChild(sprite);
        reorderChild(sprite, img->renderOrder); //watch out - RUBE render order is float but cocos2d uses integer (why not float?)
        
        // these will not change during simulation so we can set them now
        sprite->setFlippedX(img->flip);
        sprite->setColor(Color3B(img->colorTint[0], img->colorTint[1], img->colorTint[2]));
        sprite->setOpacity(img->colorTint[3]);
        sprite->setScale(img->scale / sprite->getContentSize().height);
        
        // create an info structure to hold the info for this image (body and position etc)
        RUBEImageInfo* imgInfo = new RUBEImageInfo;
        imgInfo->sprite = sprite;
        imgInfo->name = img->name;
        imgInfo->body = img->body;
        imgInfo->scale = img->scale;
        imgInfo->aspectScale = img->aspectScale;
        imgInfo->angle = img->angle;
        imgInfo->center = Vec2(img->center.x, img->center.y);
        imgInfo->opacity = img->opacity;
        imgInfo->flip = img->flip;
        for (int n = 0; n < 4; n++)
            imgInfo->colorTint[n] = img->colorTint[n];
        
        // add the info for this image to the list
        m_imageInfos.insert(imgInfo);
        log("image %s loaded", img->file.c_str());
    }

    //add js bodies
    json->getAllJSBodies(m_jsBodies);
        
    // loop through the vector, create Sprites for each image and store them in m_imageInfos
    jsBodiesLayer = Layer::create();
    GSInst->addChild(jsBodiesLayer, 1);
    for (int i = 0; i < m_jsBodies.size(); i++) {
	    jsBodiesLayer->addChild(m_jsBodies[i]);
    }
    
    // start the images at their current positions on the physics bodies
    setImagePositionsFromPhysicsBodies();
}


// This method should undo anything that was done by afterLoadProcessing, and make sure
// to call the superclass method so it can do the same
void b_RUBELayer::clear()
{
    for (set<RUBEImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        RUBEImageInfo* imgInfo = *it;
        removeChild(imgInfo->sprite, true);
    }
    m_imageInfos.clear();

    if(jsBodiesLayer){
	    jsBodiesLayer->removeFromParent();
	    jsBodiesLayer = nullptr;
    }
    
    BasicRUBELayer::clear();
}


// Standard Cocos2d method. Call the super class to step the physics world, and then
// move the images to match the physics body positions
void b_RUBELayer::update(float dt)
{
    //superclass will Step the physics world
    BasicRUBELayer::update(dt);
    setImagePositionsFromPhysicsBodies();
}


// Move all the images to where the physics engine says they should be
void b_RUBELayer::setImagePositionsFromPhysicsBodies()
{
    for (set<RUBEImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        RUBEImageInfo* imgInfo = *it;
        Point pos = imgInfo->center;
        float angle = -imgInfo->angle;
        if ( imgInfo->body ) {            
            //need to rotate image local center by body angle
            b2Vec2 localPos( pos.x, pos.y );
            b2Rot rot( imgInfo->body->GetAngle() );
            localPos = b2Mul(rot, localPos) + imgInfo->body->GetPosition();
            pos.x = localPos.x;
            pos.y = localPos.y;
            angle += -imgInfo->body->GetAngle();
        }
        imgInfo->sprite->setRotation( CC_RADIANS_TO_DEGREES(angle) );
        imgInfo->sprite->setPosition( pos );
    }

    for(auto b : m_jsBodies){
	auto b2p = b->getB2Body()->GetPosition();
	b->setDrawPosition(Vec2(b2p.x*GSInst->getPhysWorldScale(), b2p.y*GSInst->getPhysWorldScale()));
	auto b2r = b->getB2Body()->GetAngle();
	b->setDrawRotation(CC_RADIANS_TO_DEGREES(-b2r));
    }
}

// Remove one body and any images is had attached to it from the layer
void b_RUBELayer::removeBodyFromWorld(b2Body* body)
{
	if (m_world) {
		//destroy the body in the physics world
		m_world->DestroyBody(body);

		//go through the image info array and remove all sprites that were attached to the body we just deleted
		vector<RUBEImageInfo*> imagesToRemove;
		for (set<RUBEImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
			RUBEImageInfo* imgInfo = *it;
			if (imgInfo->body == body) {
				removeChild(imgInfo->sprite, true);
				imagesToRemove.push_back(imgInfo);
			}
		}

		//also remove the infos for those images from the image info array
		for (int i = 0; i < imagesToRemove.size(); i++)
			m_imageInfos.erase(imagesToRemove[i]);
	}
}


// Remove one image from the layer
void b_RUBELayer::removeImageFromWorld(RUBEImageInfo* imgInfo)
{
    removeChild(imgInfo->sprite, true);
    m_imageInfos.erase(imgInfo);
}

void b_RUBELayer::addImageToWorld(RUBEImageInfo * imgInfo)
{
	m_imageInfos.insert(imgInfo);
}

void b_RUBELayer::clearImageFromWorld(RUBEImageInfo * imgInfo)
{
	m_imageInfos.erase(imgInfo);
}

Sprite* b_RUBELayer::getAnySpriteOnBody(b2Body* body)
{
    for (set<RUBEImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        RUBEImageInfo* imgInfo = *it;
        if ( imgInfo->body == body )
            return imgInfo->sprite;
    }
    return NULL;
}

Sprite* b_RUBELayer::getSpriteWithImageName(std::string name)
{
    for (set<RUBEImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        RUBEImageInfo* imgInfo = *it;
        if ( imgInfo->name == name )
            return imgInfo->sprite;
    }
    return NULL;
}





