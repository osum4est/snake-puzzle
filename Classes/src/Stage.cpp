#include <src/objects/definitions/SnakePartDefinition.h>
#include <src/objects/Wall.h>
#include <src/Stage.h>
#include <src/LevelLoader.h>
#include <iostream>
#include <src/objects/Box.h>
#include <src/objects/Food.h>
#include "Colors.h"

Scene* Stage::createScene()
{
    auto scene = Scene::create();
    std::cout << "Starting." << std::endl;

    auto layer = Stage::create();

    scene->addChild(layer);

    return scene;
}

bool Stage::init() {
    if (!LayerColor::initWithColor(Colors::BACKGROUND)) {
        return false;
    }

    loadLevel();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int y = 0; y < level.size(); y++) {
        for (int x = 0; x < level[0].size(); x++) {
            for (int i = 0; i < level[y][x].size(); i++) {
                addChild(level[y][x][i]->getNode());
            }
        }
    }
    std::cout << "DONE" << std::endl;
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(Stage::onTouchBegan, this);
    eventListener->onTouchMoved = CC_CALLBACK_2(Stage::onTouchMoved, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(Stage::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, getChildren().at(0));

    // TODO: Make this dynamic
    setPosition(10, 10);
 
    return true;
}

void Stage::loadLevel() {
    // 2d vector array of GameObjectDefinitions
    auto definitions = LevelLoader::loadLevel("001.lvl");

    for (int y = 0; y < definitions->size(); y++) {
        level.push_back(std::vector<ObjectStack>());
        std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>> definitionRow = std::move(definitions.get()->at(y));
        auto& objectRow = level[y];
        for (int x = 0; x < definitionRow->size(); x++) {
            GameObjectDefinition* definition = definitionRow.get()->at(x).get();
            json properties = definition->getProperties();
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
                // Generic Properties
                if (properties != nullptr) {
                    try {
                        newObj->setColor(Colors::fromHex(properties.at("color")));
                    } catch (std::out_of_range) { }
                }
                objectRow.back().pushTop(std::move(newObj));
            }
        }
    }
}

bool Stage::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
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

void Stage::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (snake.isMoving())
	{
        auto worldLocation = screenToWorld(touch->getLocation());
		auto x = worldLocation.x - snake.getHead()->getPosition().x;
		auto y = worldLocation.y - snake.getHead()->getPosition().y;

		if (abs(x) > 10 || abs(y) > 10) {
            Utils::Direction direction;
            if (abs(x) > abs(y)) {
                direction = x > 0 ? Utils::RIGHT : Utils::LEFT;
            }
            else {
                direction = y > 0 ? Utils::UP : Utils::DOWN;
            }

            GameObject *nextPos = getObjectBySnake(direction);

            if (nextPos == nullptr) {
                moveSnake(direction);
            }
            else if (nextPos->getId() == BOX) {
                GameObject *nextPosBox = getObjectByObject(nextPos, direction);
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

void Stage::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	snake.setMoving(false);
}

Stage::~Stage()
{
    std::cout << "Stage deconstructing. Deleting snake..." << std::endl;
}

Vec2 Stage::getLevelCoords(Node *node) {
    return Vec2(node->getPosition() / SIZE);
}

GameObject* Stage::getObjectOnTopAt(Vec2 position) {
    return level[position.y][position.x].getTop();
}

Vec2 Stage::screenToWorld(Vec2 screen) {
    return screen - getPosition();
}

GameObject* Stage::getObjectByObject(GameObject* gameObject, Utils::Direction direction) {
    Vec2 move = Utils::getVec2FromDirection(direction);
    return getObjectOnTopAt(getLevelCoords(gameObject->getNode()) + move);
}

GameObject* Stage::getObjectBySnake(Utils::Direction direction) {
    return getObjectByObject(snake.getHead(), direction);
}

void Stage::moveSnake(Utils::Direction direction) {
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
void Stage::moveObject(GameObject* object, Vec2 newPos) {
    Vec2 oldPos = object->getPosition();
    level[newPos.y][newPos.x].pushTop(object);
    level[oldPos.y / SIZE][oldPos.x / SIZE].release(object);
    object->setPosition(newPos * SIZE);
}

void Stage::moveObject(GameObject* object, Utils::Direction direction) {
    Vec2 move = Utils::getVec2FromDirection(direction);
    moveObject(object, object->getPosition() / SIZE + move);
}

void Stage::printDebugLevel() {
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

void Stage::addObject(std::unique_ptr<GameObject> object, Vec2 pos) {
    addChild(object->getNode());
    level[pos.y][pos.x].pushTop(std::move(object));
}

void Stage::addObject(std::unique_ptr<GameObject> object) {
    addChild(object->getNode());
    // Need to cache for some reason
    Vec2 levelPos = object->getPosition() / SIZE;
    level[levelPos.y][levelPos.x].pushBottom(std::move(object));
//    level[object->getPositionY() / SIZE][object->getPositionX() / SIZE].pushBottom(std::move(object));
}

void Stage::removeObject(GameObject *object) {
    Vec2 levelPos = object->getPosition() / SIZE;
    removeChild(object->getNode(), true);
    level[levelPos.y][levelPos.x].remove(object);
}

// aaaabbbccd
// a
// b c
// d
