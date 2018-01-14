#include <H/Source.h>

namespace Tests {

	void createSplineBasedWave(){
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

	}
}
