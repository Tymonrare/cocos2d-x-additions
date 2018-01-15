#include <H/GameScene.h>
#include "RUBE/RUBELayer.h"
#include "ScriptingCore.h"
#include <H/SplineBasedContent.h>
#include <H/SystemInput.h>
#include <H/tests/Cases.h>

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

	setWorld(worldname);
	
	if(script.length())
		ScriptingCore::getInstance()->runScript(gm::path::scripts + script);

	auto bind = std::bind(&GameScene::proceedConsoleCommand, this, std::placeholders::_1);
	sys::SystemInput::listenCommand("scene", bind);

	Tests::SplineBasedContent::simpleWave();

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

void GameScene::setWorld(const std::string &worldname){
	if(worldname.length()){
		auto prev = this->getChildByName("worldNode");
		if(prev) this->removeChild(prev);

		auto RUBELayer = b_RUBELayer::create(worldname);
		RUBELayer->setName("worldNode");
		this->addChild(RUBELayer, 0);
	}
}

void GameScene::proceedConsoleCommand(const std::vector<std::string>& args){
	if(args.at(0) == "setworld"){
		setWorld(args.at(1));
	}
}

