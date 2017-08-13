
#include <src/objects/Wall.h>
#include <src/scenes/SceneGame.h>
#include <src/LevelLoader.h>
#include <iostream>
#include <src/objects/Box.h>
#include <src/objects/Food.h>
#include <network/HttpRequest.h>
#include <network/HttpClient.h>
#include "src/Colors.h"
#include "src/HttpClientTest.h"

SceneGame* SceneGame::createScene()
{
    auto scene = Scene::create();
    auto layer = SceneGame::create();
    scene->addChild(layer);
    layer->scene = scene;
    return layer;
}

Scene *SceneGame::getScene() {
    return scene;
}

bool SceneGame::init() {
    if (!LayerColor::initWithColor(Colors::BACKGROUND)) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    std::cout << "DONE" << std::endl;
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this);
    eventListener->onTouchMoved = CC_CALLBACK_2(SceneGame::onTouchMoved, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(SceneGame::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    // TODO: Make this dynamic
    setPosition(10, 10);



//    network::HttpRequest* request = new network::HttpRequest();
//    request->setUrl("http://lb.8bitforest.com/list_files/");
////    request->setUrl("http://lb.8bitforest.com/get_file/med001.lvl/");
//    request->setRequestType(network::HttpRequest::Type::GET);
//    request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
//    request->setTag("GET test1");
//
////    const char* postData = "{\"filename\":\"fromapp.lvl\"}";
////    request->setRequestData(postData, strlen(postData));
//
//    cocos2d::network::HttpClient::getInstance()->send(request);
//    request->release();


    return true;
}

void SceneGame::loadLevel(const char *filename) {
    // 2d vector array of GameObjectDefinitions
    auto definitions = LevelLoader::loadLevel("001.lvl");
    loadLevelFromDefinitions(definitions);
}

void SceneGame::loadRemoteLevel(const char *filename) {
    LevelLoader::loadRemoteLevel("easy001.lvl");
}

void SceneGame::remoteLevelCallback(std::string data) {

}

void SceneGame::loadLevelFromDefinitions(std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>>& definitions) {
    for (int y = 0; y < definitions->size(); y++) {
        level.push_back(std::vector<ObjectStack>());
        std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>> definitionRow = std::move(definitions.get()->at(y));
        auto& objectRow = level[y];
        for (int x = 0; x < definitionRow->size(); x++) {
            GameObjectDefinition* definition = definitionRow.get()->at(x).get();
            std::unique_ptr<GameObject> newObj = nullptr;
            int xPos = x * SIZE;
            int yPos = y * SIZE;
            switch (definition->getId()) {
                case SNAKE_HEAD: {
                    std::unique_ptr<SnakePart> head(new SnakePart(SNAKE_HEAD, Colors::SNAKE_HEAD));
                    head->setPosition(xPos, yPos);
                    snake.setHead(head.get());
                    newObj = std::unique_ptr<GameObject>(std::move(head));
                    break;
                }
                case SNAKE_BODY: {
                    SnakePartDefinition *spd = dynamic_cast<SnakePartDefinition *>(definition);
                    while (snake.getBody().size() <= spd->getPartIndex()) {
                        snake.getBody().push_back(nullptr);
                    }
                    std::unique_ptr<SnakePart> bodyPart(new SnakePart(SNAKE_BODY, Colors::SNAKE_BODY_DEFAULT));
                    bodyPart->setPosition(xPos, yPos);
                    snake.getBody().at(spd->getPartIndex()) = bodyPart.get();
                    newObj = std::unique_ptr<GameObject>(std::move(bodyPart));
                    break;
                }
                case WALL:
                    newObj = std::unique_ptr<GameObject>(new Wall(xPos, yPos));
                    break;
                case BOX:
                    newObj = std::unique_ptr<GameObject>(new Box(xPos, yPos));
                    break;
                case FOOD:
                    newObj = std::unique_ptr<GameObject>(new Food(xPos, yPos));
                    break;
            }
            objectRow.push_back(ObjectStack());
            if (newObj != nullptr) {
                objectRow.back().pushTop(std::move(newObj));
            }
        }
    }

    for (int y = 0; y < level.size(); y++) {
        for (int x = 0; x < level[0].size(); x++) {
            for (int i = 0; i < level[y][x].size(); i++) {
                addChild(level[y][x][i]->getNode());
            }
        }
    }
}

bool SceneGame::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    auto worldLocation = screenToWorld(touch->getLocation());
	auto x = worldLocation.x - snake.getHead()->getPosition().x;
	auto y = worldLocation.y - snake.getHead()->getPosition().y;
	if (abs(x) < 25 && abs(y) < 25)
	{
		snake.setMoving(true);
        return true;
	}
    return false;
}

void SceneGame::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (snake.isMoving())
	{
        auto worldLocation = screenToWorld(touch->getLocation());
		auto x = worldLocation.x - snake.getHead()->getPosition().x;
		auto y = worldLocation.y - snake.getHead()->getPosition().y;

		if (abs(x) > 10 || abs(y) > 10)
		{
            Utils::Direction direction;
			if (abs(x) > abs(y))
			{
				direction = x > 0 ? Utils::RIGHT : Utils::LEFT;
			}
			else
			{
				direction = y > 0 ? Utils::UP : Utils::DOWN;
			}
            GameObject* nextPos = getObjectBySnake(direction);
            if (nextPos == nullptr) {
                moveSnake(direction);
            }
            else if (nextPos->getId() == BOX) {
                GameObject* nextPosBox = getObjectByObject(nextPos, direction);
                if (nextPosBox == nullptr) {
                    //TODO: Use recursion to push multiple boxes
                    moveObject(nextPos, direction);
                    moveSnake(direction);
                }
            }
            else if (nextPos->getId() == FOOD) {
                std::unique_ptr<SnakePart> newPart(new SnakePart(SNAKE_BODY, Colors::SNAKE_BODY_DEFAULT));
                moveSnake(direction);
                snake.addBodyPart(newPart.get());
                // TODO: Can I change to passing GameObject*
                addObject(std::move(newPart));
                removeObject(nextPos);
            }
		}
	}
}

void SceneGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	snake.setMoving(false);
}

SceneGame::~SceneGame()
{
    std::cout << "Stage deconstructing. Deleting snake..." << std::endl;
}

Vec2 SceneGame::getLevelCoords(Node *node) {
    return Vec2(node->getPosition() / SIZE);
}

GameObject* SceneGame::getObjectOnTopAt(Vec2 position) {
    return level[position.y][position.x].getTop();
}

Vec2 SceneGame::screenToWorld(Vec2 screen) {
    return screen - getPosition();
}

GameObject* SceneGame::getObjectByObject(GameObject* gameObject, Utils::Direction direction) {
    Vec2 move = Utils::getVec2FromDirection(direction);
    return getObjectOnTopAt(getLevelCoords(gameObject->getNode()) + move);
}

GameObject* SceneGame::getObjectBySnake(Utils::Direction direction) {
    return getObjectByObject(snake.getHead(), direction);
}

void SceneGame::moveSnake(Utils::Direction direction) {
    // Must start with head in order to move references in moveObject()

    Vec2 oldPos(snake.getHead()->getPosition() / SIZE);
    Vec2 newPos(oldPos);
    moveObject(snake.getHead(), snake.getHead()->getPosition() / SIZE + Utils::getVec2FromDirection(direction));
    oldPos.set(newPos);
    newPos.set(snake.getBody()[0]->getPosition() / SIZE);
    if (oldPos != newPos) {
        moveObject(snake.getBody()[0], oldPos);
        for (int i = 1; i < snake.getBody().size(); i++) {
            oldPos.set(newPos);
            newPos.set(snake.getBody()[i]->getPosition() / SIZE);
            moveObject(snake.getBody()[i], oldPos);
        }
    }
}

/**
 *
 * @param object
 * @param newPos - Position in map coords
 */
void SceneGame::moveObject(GameObject* object, Vec2 newPos) {
    Vec2 oldPos = object->getPosition();
    level[newPos.y][newPos.x].pushTop(object);
    level[oldPos.y / SIZE][oldPos.x / SIZE].release(object);
    object->setPosition(newPos * SIZE);
}

void SceneGame::moveObject(GameObject* object, Utils::Direction direction) {
    Vec2 move = Utils::getVec2FromDirection(direction);
    moveObject(object, object->getPosition() / SIZE + move);
}

void SceneGame::printDebugLevel() {
    for (int y = level.size() - 1; y >= 0 ; y--) {
        for (int x = 0; x < level[y].size(); x++) {
            if (!level[y][x].isEmpty()) {
                std::cout << level[y][x].getTop() << "\t";
            }
            else {
                std::cout << "\t\t\t";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "END LEVEL" << std::endl;
}

void SceneGame::addObject(std::unique_ptr<GameObject> object, Vec2 pos) {
    addChild(object->getNode());
    level[pos.y][pos.x].pushTop(std::move(object));
}

void SceneGame::addObject(std::unique_ptr<GameObject> object) {
    addChild(object->getNode());
    // Need to cache for some reason
    Vec2 levelPos = object->getPosition() / SIZE;
    level[levelPos.y][levelPos.x].pushBottom(std::move(object));
//    level[object->getPositionY() / SIZE][object->getPositionX() / SIZE].pushBottom(std::move(object));
}

void SceneGame::removeObject(GameObject *object) {
    Vec2 levelPos = object->getPosition() / SIZE;
    removeChild(object->getNode(), true);
    level[levelPos.y][levelPos.x].remove(object);
}

