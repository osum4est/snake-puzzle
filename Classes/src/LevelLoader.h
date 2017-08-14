#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <src/objects/definitions/GameObjectDefinition.h>
#include <network/HttpClient.h>
#include <src/scenes/SceneGame.h>
#include "cocos2d.h"

USING_NS_CC;

class LevelLoader
{
public:
	LevelLoader();

	std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>> loadLevelFromFile(std::string file);
    void loadRemoteLevel(std::string file, SceneGame* sceneGame);
    std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>> loadLevel(std::vector<std::string> levelData);

    void remoteLevelLoaded(std::vector<std::string> level);

    ~LevelLoader();
private:
    std::function<void(std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>>)> callback;
    SceneGame* sceneGame;
};

