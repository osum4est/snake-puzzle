#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <src/objects/definitions/GameObjectDefinition.h>
#include <network/HttpClient.h>
#include "cocos2d.h"

USING_NS_CC;

class LevelLoader
{
public:
	LevelLoader();

	static std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>> loadLevel(std::string file);
	static void loadRemoteLevel(std::string file);
	void onRemoteLevelRecieved(network::HttpClient* sender, network::HttpResponse* response);

	~LevelLoader();
private:
};

