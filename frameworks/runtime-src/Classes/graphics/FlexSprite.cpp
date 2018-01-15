#include <H/SpritePolygon.h>

using namespace Tools;

FlexSprite* FlexSprite::create(const std::string& filename, const Size &density)
{
    FlexSprite *sprite = new (std::nothrow) FlexSprite();
    if (sprite && sprite->initWithFile(filename, density))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool FlexSprite::initWithFile(const std::string& filename, const Size &density){
	if (filename.empty())
	{
		CCLOG("Call Sprite::initWithFile with blank resource filename.");
		return false;
	}

	_fileName = filename;
	_fileType = 0;

	Texture2D *texture = _director->getTextureCache()->addImage(filename);
	if (texture)
	{
		Rect rect = Rect::ZERO;
		rect.size = texture->getContentSize();
		if(!initWithTexture(texture, rect)) return false;

		_polyInfo = SpritePolygonManager::genGridPolygon(rect.size, density);
		_renderMode = RenderMode::POLYGON;
		Node::setContentSize(_polyInfo.getRect().size / _director->getContentScaleFactor());
		return true;
	}

	// don't release here.
	// when load texture failed, it's better to get a "transparent" sprite then a crashed program
	// this->release();
	return false;
}
PolygonInfo *FlexSprite::getPolygonInfoDirect(){
	return &_polyInfo;
}
