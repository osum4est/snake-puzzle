#include "LevelLoader.h"
#include "HttpClientTest.h"
#include <iostream>
#include <src/objects/definitions/SnakePartDefinition.h>
#include <network/HttpRequest.h>
#include <network/HttpClient.h>


LevelLoader::LevelLoader() {
}


LevelLoader::~LevelLoader() {
}

// TODO: does 2d vector of object (non-reference or pointer) do bad things?
std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>> LevelLoader::loadLevel(std::string file) {
    std::string token;
    auto fullPath = FileUtils::getInstance()->fullPathForFilename(file.c_str());
    auto result = FileUtils::getInstance()->getStringFromFile(fullPath);

    std::istringstream fileStringStream(result);

    auto levelData = std::vector<std::string>();

    while (getline(fileStringStream, token)) {
//        log(token.c_str());
        levelData.push_back(token.c_str());
    }

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

void LevelLoader::loadRemoteLevel(std::string file) {
    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl("http://lb.8bitforest.com/get_file/" + file + "/");
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(LevelLoader::onRemoteLevelRecieved, LevelLoader()));
    request->setTag("GET remotelevel");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

void LevelLoader::onRemoteLevelRecieved(network::HttpClient *sender, network::HttpResponse *response) {
    // dump data
    auto buffer = response->getResponseData();

    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
    }
    printf("\n");
//    std::cout << response->getResponseDataString() << std::endl;
}
