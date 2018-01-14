#pragma once

#include <H/Source.h>

class GameScene : public Scene
{

public:
	static GameScene *create(const std::string &script, const std::string &worldconf);
	inline static GameScene *getInstance(){return instance;};

	~GameScene();
	void simpleJScallback();

	inline float getPhysWorldScale(){return physWorldScale;};
	inline void setPhysWorldScale(float scale){physWorldScale = scale;};

private:
	static GameScene *instance;

	bool init(const std::string &script, const std::string &worldname);
	void proceedConsoleCommand(const std::vector<std::string>& args);
	void setWorld(const std::string &worldname);

	GameScene();

	float physWorldScale = 100;
};

