#include <H/Source.h>
#include <H/GameScene.h>
#include <H/SplineBasedContent.h>
#include <H/tests/Cases.h>
#include <H/SpritePolygon.h>

using namespace Tests;

void SplineBasedContent::simpleWave(){
	PointArray *points = PointArray::create(0);
	for(int posx = 0, posy = 0;posx <= 1000; posx += 20, posy += random(-10, 10))
		points->addControlPoint(Vec2(posx, posy)); 

	auto veg = SplineBasedVegetation::createWithFilename(points, "res/tests/images/develop-tile.png");
	GSInst->addChild(veg);
	veg->setBatchProperties(Size(8, 8));
	veg->growUp(.03, 0.3);

	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	GSInst->schedule([=](float dt){
			auto cpoints = points->getControlPoints();
			for(int i = 0;i < cpoints->size();i++)
			cpoints->at(i)->y = sin(i+(float)Director::getInstance()->getTotalFrames()/100)*10;
			veg->updateSpline();
			veg->setDebugDraw(true);
			}, .01f, "test resume");

}
void SplineBasedContent::meshTiledWave(){
}

void Graphics::simpleSpriteMesh(){
	{//simple
		auto sp = FlexSprite::create("res/tests/images/develop.png", Size(10,10));
		GSInst->addChild(sp);
		Tools::SpritePolygonManager::setDebugDraw(sp, true);
	}
	{//modificated
		auto sp = FlexSprite::create("res/tests/images/develop.png", Size(5,5));
		GSInst->addChild(sp);
		sp->setPositionX(250);

		auto poly = sp->getPolygonInfoDirect();

		int count = poly->triangles.vertCount; 
		for(int i = 0; i < count; i++){
			poly->triangles.verts[i].vertices.y += sin(poly->triangles.verts[i].texCoords.u*90)*20;
		}

		//debug draw is statik grid image, you have to use it after poly manipulations
		Tools::SpritePolygonManager::setDebugDraw(sp, true);
	}
}
