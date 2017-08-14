#include "LevelLoader.h"
#include "HttpClient.h"
#include <iostream>
#include <src/objects/definitions/SnakePartDefinition.h>
#include <json.hpp>


using namespace nlohmann;

LevelLoader::LevelLoader() {
}


LevelLoader::~LevelLoader() {
}

std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>>
LevelLoader::loadLevelFromFile(std::string file) {
    std::string token;
    auto fullPath = FileUtils::getInstance()->fullPathForFilename(file.c_str());
    auto result = FileUtils::getInstance()->getStringFromFile(fullPath);

    std::istringstream fileStringStream(result);

    auto levelData = std::vector<std::string>();

    while (getline(fileStringStream, token)) {
        levelData.push_back(token.c_str());
    }

    return loadLevel(levelData);
}

// TODO: does 2d vector of object (non-reference or pointer) do bad things?
std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>> LevelLoader::loadLevel(std::vector<std::string> levelData) {

    // Smart pointer so it doesn't get destroyed at end of method
    std::unique_ptr<std::vector<
            std::unique_ptr<std::vector<
                    std::unique_ptr<GameObjectDefinition>>>>>
                definitions(new std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>());

    // Start at levelData.size() because Cocos's coordinate system is backwards
    for (int y = levelData.size() - 1; y >= 0; y--) {
        std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>> objectLine(new std::vector<std::unique_ptr<GameObjectDefinition>>());
        for (auto x = 0; x < levelData[y].size(); x++) {
            std::unique_ptr<GameObjectDefinition> definition = nullptr;
            switch (levelData[y][x]) {
                case 'X':
                    definition = std::unique_ptr<GameObjectDefinition>(new GameObjectDefinition(WALL));
                    break;
                case 'S':
                    definition = std::unique_ptr<GameObjectDefinition>(new GameObjectDefinition(SNAKE_HEAD));
                    break;
                case 'B':
                    definition = std::unique_ptr<GameObjectDefinition>(new GameObjectDefinition(BOX));
                    break;
                case 'F':
                    definition = std::unique_ptr<GameObjectDefinition>(new GameObjectDefinition(FOOD));
                    break;
                default:
                    int number = levelData[y][x] - '0';
                    if (number >= 0 && number < 10) {
                        definition = std::unique_ptr<GameObjectDefinition>(new SnakePartDefinition(SNAKE_BODY, number));
                    }
                    else {
                        definition = std::unique_ptr<GameObjectDefinition>(new GameObjectDefinition(EMPTY_SPACE));
                    }
                    break;

            }
            objectLine->emplace_back(std::unique_ptr<GameObjectDefinition>(std::move(definition)));

        }
        definitions->push_back(std::move(objectLine));
    }

    return definitions;
}

void LevelLoader::loadRemoteLevel(std::string file, SceneGame* sceneGame) {
    this->callback = callback;
    this->sceneGame = sceneGame;
    std::unique_ptr<HttpClient> client(new HttpClient());
    client->getFile(file, this);
}

void LevelLoader::remoteLevelLoaded(std::vector<std::string> level) {
//    callback(loadLevel(level));
//    loadLevel(level);
    auto d = loadLevel(level);
    sceneGame->loadLevelFromDefinitions(loadLevel(level));
//    SceneGame::instance->loadLevelFromDefinitions(loadLevel(level));
//    SceneGame::instance->loadLevelFromDefinitions(loadLevel(level));
}
