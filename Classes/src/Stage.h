#pragma once

#include <src/objects/Snake.h>
#include <src/objects/ObjectStack.h>

class Stage : public LayerColor
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Stage);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

    ~Stage();
private:
    Snake snake;
    std::vector<std::vector<ObjectStack>> level;

    static const int SIZE = 20;

    void loadLevel();
    GameObject * getObjectOnTopAt(Vec2 position);
    GameObject * getObjectBySnake(Utils::Direction direction);
    Vec2 getLevelCoords(Node* node);
    Vec2 screenToWorld(Vec2 screen);

    void moveSnake(Utils::Direction direction);
    void moveObject(GameObject* object, Vec2 newPos);
    void moveObject(GameObject *object, Utils::Direction direction);

    void addObject(std::unique_ptr<GameObject> object, Vec2 pos);
    void addObject(std::unique_ptr<GameObject> object);

    void removeObject(GameObject* object);

    void printDebugLevel();

    GameObject *getObjectByObject(GameObject *gameObject, Utils::Direction direction);
};
