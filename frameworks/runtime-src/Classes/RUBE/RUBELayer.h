//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  RUBELayer
//
//  Extends BasicRUBELayer and also loads images. This is the class
//  you would typically extend to make your own layers.
//

#ifndef RUBE_LAYER
#define RUBE_LAYER
#define GRUBE b_RUBELayer
#define GRUBEInst b_RUBELayer::getInstance()
#include "BasicRUBELayer.h"
#include <H/b2tojs.h>

//
//  RUBEImageInfo
//
//  Holds information about one image in the layer, most importantly
//  the body it is attached to and its position relative to that body.
//
//  When the body is moved by the physics engine, this information is
//  used to place the image in the correct position to match the physics.
//  If the body is NULL, the position is relative to 0,0 and angle zero.
//
struct RUBEImageInfo {
    
    cocos2d::Sprite* sprite;      // the image
    std::string name;               // the file the image was loaded from
    class b2Body* body;             // the body this image is attached to (can be NULL)
    float scale;                    // a scale of 1 means the image is 1 physics unit high
    float aspectScale;              // modify the natural aspect of the image
    float angle;                    // 'local angle' - relative to the angle of the body
    cocos2d::Point center;        // 'local center' - relative to the position of the body
    float opacity;                  // 0 - 1
    bool flip;                      // horizontal flip
    int colorTint[4];               // 0 - 255 RGBA values
    
};

//-------------------------

class b_RUBELayer : public BasicRUBELayer
{
protected:
    std::set<RUBEImageInfo*> m_imageInfos;                  // holds some information about images in the scene, most importantly the
    static b_RUBELayer *sfptr;
    b_RUBELayer() { sfptr = this; };

    std::vector<gm::Body*> m_jsBodies;
    Layer *jsBodiesLayer = nullptr;
public:
	virtual ~b_RUBELayer() { sfptr = nullptr; };
	static inline b_RUBELayer *getInstance() { return sfptr; };

	static b_RUBELayer *create(const std::string& map);
    
    virtual cocos2d::Point initialWorldOffset();          // overrides base class
    virtual float initialWorldScale();                      // overrides base class
    
    virtual void afterLoadProcessing(b2dJson* json) override;        // overrides base class
    virtual void clear();                                   // overrides base class
    
    void setImagePositionsFromPhysicsBodies();              // called every frame to move the images to the correct position when bodies move
    
    virtual void update(float dt);                          // standard Cocos2d function
    
    void removeBodyFromWorld(b2Body* body);                 // removes a body and its images from the layer
    void removeImageFromWorld(RUBEImageInfo* imgInfo);      // removes an image from the layer
	void addImageToWorld(RUBEImageInfo* imgInfo);			// adding image to image info
	void clearImageFromWorld(RUBEImageInfo* imgInfo);		// just clear info about image whithout delete

    cocos2d::Sprite* getAnySpriteOnBody(b2Body* body);            // returns the first sprite found attached to the given body, or nil if there are none
    cocos2d::Sprite* getSpriteWithImageName(std::string name);    // returns the first sprite found with the give name (as named in the RUBE scene) or nil if there is none
};

#endif /* RUBE_LAYER */
