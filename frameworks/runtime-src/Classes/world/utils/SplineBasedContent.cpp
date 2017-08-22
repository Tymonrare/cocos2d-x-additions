#include "H/SplineBasedContent.h"

SplineBasedContentBase::SplineBasedContentBase(){};
SplineBasedContentBase::~SplineBasedContentBase(){
	spline->release();
};

Point SplineBasedContentBase::getPointOnSpline(float where){
	auto points = spline->getControlPoints();
	int totalPoints = points->size() - 1;

	//find nearest point on spline
	int pI = std::min((int)std::floor(where * totalPoints), totalPoints - 1);

	//find points spline relative pos
	float wherePI1 = ((float)pI)/totalPoints;
	float wherePI2 = ((float)pI+1)/totalPoints;

	//calculate "middle" pos
	float vecLen = (where - wherePI1)/(wherePI2 - wherePI1);

	//TODO: use spline->getControlPointAtIndex instead
	return *points->at(pI) + (*points->at(pI + 1) - *points->at(pI))*vecLen;
};

Vec2 SplineBasedContentBase::getPointNolmal(float where){
	auto points = spline->getControlPoints();
	int totalPoints = points->size() - 1;

	//find nearest point on spline
	int pI = std::min((int)std::floor(where * totalPoints), totalPoints - 1);

	//TODO: use spline->getControlPointAtIndex instead
	Vec2 vec = (*points->at(pI+1) - *points->at(pI)).getNormalized();
	vec.rotate(Vec2::ZERO, M_PI/2);

	return vec;
};

float SplineBasedContentBase::getSplineLength(PointArray *spline){
	auto points = spline->getControlPoints();
	float len = 0;

	//TODO: use spline->getControlPointAtIndex instead
	for(int i = 0;i < points->size() - 1;i++)
		len += (*points->at(i + 1) - *points->at(i)).length();

	return len;
}
float SplineBasedContentBase::getSplineLength(){
	return getSplineLength(spline);
}

PointArray *SplineBasedContentBase::makeCardinalSpline(PointArray *config, float tension,  unsigned int segments)
{
	PointArray *spline = PointArray::create(0);

	ssize_t p;
	float lt;
	float deltaT = 1.0f / config->count();

	for( unsigned int i=0; i < segments+1;i++) {

		float dt = (float)i / segments;

		// border
		if( dt == 1 ) {
			p = config->count() - 1;
			lt = 1;
		} else {
			p = dt / deltaT;
			lt = (dt - deltaT * (float)p) / deltaT;
		}

		// Interpolate
		Vec2 pp0 = config->getControlPointAtIndex(p-1);
		Vec2 pp1 = config->getControlPointAtIndex(p+0);
		Vec2 pp2 = config->getControlPointAtIndex(p+1);
		Vec2 pp3 = config->getControlPointAtIndex(p+2);

		Vec2 newPos = ccCardinalSplineAt( pp0, pp1, pp2, pp3, tension, lt);
		spline->addControlPoint(newPos);
	}

	return spline;
	//CC_SAFE_DELETE_ARRAY(vertices);
}

SplineBasedVegetation *SplineBasedVegetation::create(cocos2d::PointArray *spline){
	SplineBasedVegetation * ret = new (std::nothrow) SplineBasedVegetation();

	if (ret && ret->init(spline))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);

	return ret;
};

bool SplineBasedVegetation::init(cocos2d::PointArray *spline){
	//auto draw = DrawNode::create();
	//draw->drawCardinalSpline(spline, 0.5f, spline->count()*10, Color4F(1,1,1,1));
	//addChild(draw);
	this->spline = spline;
	spline->retain();
	makeSplineVertexDistEqual();
	return true;
};

void SplineBasedContentBase::makeSplineVertexDistEqual(){
	CCASSERT(!spline, "spline empty, can't process");

	
	float minDist = -1;
	for(int i = 0;i < spline->count() - 1;i++){
		float dist = (spline->getControlPointAtIndex(i+1) - spline->getControlPointAtIndex(i)).length();
		log("%f", dist);
		if(minDist < 0 || dist < minDist)
			minDist = dist;
	}
	for(int i = 0;i < spline->count() - 1;i++){
		float dist = (spline->getControlPointAtIndex(i+1) - spline->getControlPointAtIndex(i)).length();
		if(dist > minDist*2){
			Vec2 point = (spline->getControlPointAtIndex(i+1) - spline->getControlPointAtIndex(i)).getNormalized()*minDist + spline->getControlPointAtIndex(i);
			spline->insertControlPoint(point, i+1);
		}
	}
}

SplineBasedVegetation *SplineBasedVegetation::createWithFilename_jsb(Vec2 *spline, int splineLen, const std::string &path, const Vec2 &textureAnchor){
	PointArray *points = PointArray::create(0);
	for(int i = 0; i < splineLen;i++)
		points->addControlPoint(spline[i]);

	return createWithFilename(points, path, textureAnchor);
}

SplineBasedVegetation *SplineBasedVegetation::createWithFilename(cocos2d::PointArray *spline, const std::string &path, const Vec2 &textureAnchor){
	SplineBasedVegetation * ret = new (std::nothrow) SplineBasedVegetation();

	if (ret && ret->initWithFilename(spline, path, textureAnchor))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);

	return ret;
};
bool SplineBasedVegetation::initWithFilename(cocos2d::PointArray *spline, const std::string &path, const Vec2 &textureAnchor){
	init(spline);

	texturePath = path;
	this->textureAnchor = textureAnchor;
	batchParent = SpriteBatchNode::create(texturePath);
	addChild(batchParent);

	auto img = new Image();
	img->initWithImageFile(texturePath);
	batchRect.push_back(Rect(0,0, img->getWidth(), img->getHeight()));

	return true;
};

void SplineBasedVegetation::setBatchProperties(cocos2d::Size framesCount){
	useBatched = true;
	CCASSERT(texturePath.empty(), "texturePath empty, can't use setBatchProperties");

	batchRect.clear();

	auto img = new Image();
	img->initWithImageFile(texturePath);

	Size frameSize(img->getWidth()/framesCount.width, img->getHeight()/framesCount.height);

	for(int y = 0;y < framesCount.height; y++)
		for(int x = 0;x < framesCount.width;x++){
			batchRect.push_back(Rect(x*frameSize.width, y*frameSize.height, frameSize.width, frameSize.height));
		}
}
void SplineBasedVegetation::setBatchProperties(std::vector<cocos2d::Rect> frames){
	useBatched = true;

	batchRect = frames;
}

void SplineBasedVegetation::updateSpline(PointArray *spline){
	if(spline){
		this->spline->release();
		this->spline = spline;
		spline->retain();
	}

	auto children = batchParent->getChildren();
	int childCount = children.size();

	for(int i = 0;i < childCount;i++){
		auto ch = children.at(i);

		float dt = 0;
		if(i) dt = ((float)i)/childCount;

		ch->setPosition(getPointOnSpline(dt));

		if(useSplineNormals){
			Vec2 vec = getPointNolmal(dt);
			ch->setRotation(CC_RADIANS_TO_DEGREES(atan2f(vec.x, vec.y)));
		}
	}
}

SplineBasedVegetation::SplineBasedVegetation(){};
SplineBasedVegetation::~SplineBasedVegetation(){
	spline->release();
};

void SplineBasedVegetation::growUp(float step, float spreadPos, float spreadAngle, float spreadH, int spreadDepth, bool useSplineAngle, bool splineRelative){
	CCASSERT(texturePath.empty(), "texturePath empty, can't use growUp");

	useSplineNormals = useSplineAngle;
	float splineLen = getSplineLength();

	if(!splineRelative) step = step/splineLen;

	for(float dt = 0; dt <= 1; dt += step*random(1-spreadPos, 1+spreadPos)){
		Node *obj;
		obj = Sprite::create(texturePath, batchRect.at(random(0, (int)batchRect.size()-1)));
		obj->setAnchorPoint(textureAnchor);


		float rotation = random(-spreadAngle, spreadAngle);
		Vec2 rotvec = getPointNolmal(dt);
		if(useSplineAngle)
			rotation += CC_RADIANS_TO_DEGREES(atan2f(rotvec.x, rotvec.y));

		int Hpos = random(-spreadH, spreadH);
		Vec2 position = getPointOnSpline(dt) + Vec2(0, Hpos).rotateByAngle(Vec2::ZERO, rotation);


		obj->setRotation(rotation);
		obj->setPosition(position);

		batchParent->addChild(obj, random(-spreadDepth, spreadDepth) - Hpos);
	}
}
