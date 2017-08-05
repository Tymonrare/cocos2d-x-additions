#include <H/GameScene.h>
#include "RUBE/RUBELayer.h"
#include "ScriptingCore.h"
#include <H/SplineBasedContent.h>


GameScene *GameScene::instance = nullptr;

GameScene * GameScene::create(const std::string &script, const std::string &worldname)
{
	GameScene * ret = new (std::nothrow) GameScene();

	if (ret && ret->init(script, worldname))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);

	return ret;
}

bool GameScene::init(const std::string &script, const std::string &worldname)
{
	cocos2d::log("scene created with %s script and %s world", script.c_str(), worldname.c_str());
	instance = this;

	if(worldname.length()){
		auto RUBELayer = b_RUBELayer::create(worldname);
		this->addChild(RUBELayer, 0);
	}
	
	if(script.length())
		ScriptingCore::getInstance()->runScript(gm::path::scripts + script);

	PointArray *points = PointArray::create(0);
	for(int posx = 0, posy = 0;posx <= 1000; posx += 20, posy += random(-10, 10))
		points->addControlPoint(Vec2(posx, posy)); 

	auto veg = SplineBasedVegetation::createWithFilename(points, "res/images/develop-tile.png");
	addChild(veg);
	veg->setBatchProperties(Size(8, 8));
	veg->growUp(.03, 0.3);

	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	

	schedule([=](float dt){
			auto cpoints = points->getControlPoints();
			for(int i = 0;i < cpoints->size();i++)
				cpoints->at(i)->y = sin(i+(float)Director::getInstance()->getTotalFrames()/100)*10;
			veg->updateSpline();
			}, .01f, "test resume");

	log("scene create success");
	return true;
}

GameScene::GameScene(){
}
GameScene::~GameScene(){
}

void GameScene::simpleJScallback(){
	log("js test init callback");
}
