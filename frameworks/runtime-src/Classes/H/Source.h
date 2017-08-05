#pragma once
#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "scripting/js-bindings/manual/component/CCComponentJS.h"

USING_NS_CC;

extern Size screenSize;

namespace gm{
	namespace path{
		static const std::string body_components = "src/body/components/";
		static const std::string scripts = "src/";
		static const std::string maps = "res/maps/";
		static const std::string images = "res/images/";
	};

}

#define GSInst GameScene::getInstance()
