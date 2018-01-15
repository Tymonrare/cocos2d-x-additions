#pragma once

#include <H/Source.h>

/**
 * @brief class for generate spline-based content
 */
class SplineBasedContentBase : public Node
{

public:
	//static SplineBasedContentBase *create(cocos2d::PointArray *spline);
	~SplineBasedContentBase();

	/**
	 * @brief better to use spline with equal segmants length
	 *
	 * @Param where value 0-1 that point on position on spline
	 *
	 * @Returns exact pos on spline 
	 */
	Point getPointOnSpline(float where);
	/**
	 * @brief returns normal of spline point
	 *
	 * @Param where value 0-1 that point on position on spline
	 *
	 * @Returns normal
	 */
	Vec2 getPointNolmal(float where);
	/**
	 * @brief spline length in pixels
	 *
	 * @Returns   
	 */
	float getSplineLength();
	float getSplineLength(PointArray *spline);
	float getSplinePointsDensity();

	void setDebugDraw(bool enabled);
private:
	virtual bool init(cocos2d::PointArray *spline) = 0;

protected:
	PointArray *spline = nullptr, *cardinalSpline = nullptr;
	SplineBasedContentBase();

	PointArray *makeCardinalSpline(PointArray *config, float tension,  unsigned int segments);
	void makeSplineVertexDistEqual();
};

/**
 * @brief class for generate spline-based vegetation(Or any surface objects)
 */
class SplineBasedVegetation : public SplineBasedContentBase
{

public:
	static SplineBasedVegetation *create(cocos2d::PointArray *spline);
	/**
	 * @brief creates "vegetation"
	 *
	 * @Param spline control points of surface
	 * @Param path path to file
	 * @Param textureAnchor anchor point of texture
	 *
	 * @Returns   
	 */
	static SplineBasedVegetation *createWithFilename(cocos2d::PointArray *spline, const std::string &path, const Vec2 &textureAnchor = Vec2::ANCHOR_MIDDLE);

	/**
	 * @brief for js bind. createWithFile in js
	 *
	 * @Param spline points of spline
	 * @Param splineLen len of array
	 * @Param path path to texture
	 * @Param textureAnchor sprite anchor point
	 *
	 * @Returns   
	 */
	static SplineBasedVegetation *createWithFilename_jsb(Vec2 *spline, int splineLen, const std::string &path, const Vec2 &textureAnchor = Vec2::ANCHOR_MIDDLE);
	
	/**
	 * @brief starts "grow"(add) objects on spline
	 *
	 * @Param step distance between objects in pixels OR count of objects if splineRelative == true
	 * @Param spreadPos randomize step. 0-1
	 * @Param spreadAngle randomize of "vegetation" angle. Absolute, positive degrees value
	 * @Param spreadH randomize Y pos. Absolute value in pixels 
	 * @Param spreadDepth randomize of objects Z-order
	 * @Param useSplineNormal will be use angle of "grow" surface point (normal)
	 * @Param splineRelative if true will be use values for step between 0-1(Percents of spline length), otherwise pixels
	 */
	void growUp(float step, float spreadPos = 0, float spreadAngle = 0, float spreadH = 0, int spreadDepth = 1, bool useSplineAngle = true, bool splineRelative = true);

	/**
	 * @brief adds cache from plist
	 *
	 * @Param plist path to plist
	 */
	void setBatchProperties(const std::string &plist);
	/**
	 * @brief sets properties for batch with equal frame sizes
	 *
	 * @Param framesCount count of frames
	 */
	void setBatchProperties(cocos2d::Size framesCount);

	/**
	 * @brief sets properties for batch with individual frame properties
	 *
	 * @Param frames vector of frames rects
	 */
	void setBatchProperties(std::vector<cocos2d::Rect> frames);

	/**
	 * @brief updates pos of sprites and pointer for spline if needed 
	 *
	 * @Param spline new spline points or null if points the same
	 */
	void updateSpline(PointArray *spline = nullptr);

	~SplineBasedVegetation();

	virtual bool initWithFilename(cocos2d::PointArray *spline, const std::string &path, const Vec2 &textureAnchor);
private:
	SplineBasedVegetation();
	virtual bool init(cocos2d::PointArray *spline);

	//data
	std::string texturePath;
	Vec2 textureAnchor;
	SpriteBatchNode *batchParent;

	//runtime
	bool useSplineNormals = false;

	//batch
	bool useBatched = false;
	std::vector<cocos2d::Rect> batchRect;
};

