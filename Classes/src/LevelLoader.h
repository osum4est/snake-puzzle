#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <src/objects/definitions/GameObjectDefinition.h>
#include "cocos2d.h"

USING_NS_CC;

class LevelLoader
{
public:
	LevelLoader();

	static std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>> loadLevel(std::string file);

	~LevelLoader();
	

private:
};

