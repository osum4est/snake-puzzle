#include "LevelLoader.h"
#include <json.hpp>
#include <iostream>
#include <src/objects/definitions/SnakePartDefinition.h>

using namespace nlohmann;

LevelLoader::LevelLoader() {
}


LevelLoader::~LevelLoader() {
}

// This assumes the level file is made correctly!!!
std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>> LevelLoader::loadLevel(std::string file) {
    std::string token;
    std::string jsonStartChar = "{";
    auto fullPath = FileUtils::getInstance()->fullPathForFilename(file.c_str());
    auto result = FileUtils::getInstance()->getStringFromFile(fullPath);

    std::istringstream fileStringStream(result);

    auto levelData = std::vector<std::string>();
    auto propData = std::vector<json>();

    while (getline(fileStringStream, token)) {
        if (!token.empty() && token.find('\n') != 0 && token.find('\r') != 0) {
            if (token.find('{') == 0) {
                propData.push_back(json::parse(token));
            }
            else {
                levelData.push_back(token.c_str());
            }
        }
    }

    // Smart pointer so it doesn't get destroyed at end of method
    std::unique_ptr<std::vector<
            std::unique_ptr<std::vector<
                    std::unique_ptr<GameObjectDefinition>>>>>
                definitions(new std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>());

    // Start at levelData.size() because Cocos's coordinate system is backwards
    for (int y = levelData.size() - 1; y >= 0; y--) {
        std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>> objectLine(new std::vector<std::unique_ptr<GameObjectDefinition>>());
        for (int x = 0; x < levelData[y].size(); x++) {
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

    for (json props : propData) {
        definitions->at(definitions->size() - (int)(props["y"]))->at((int)(props["x"]) - 1)->setProperties(props);
        std::cout << "Assigning data: " << props << std::endl;
    }

    return definitions;
}
