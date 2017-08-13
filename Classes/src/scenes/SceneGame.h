#pragma once

#include <src/objects/Snake.h>
#include <src/objects/ObjectStack.h>
#include <src/objects/definitions/SnakePartDefinition.h>

// TODO: Inherit from scene?
class SceneGame : public LayerColor
{
public:
    static SceneGame* createScene();
    virtual bool init();
    CREATE_FUNC(SceneGame);

    Scene* getScene();

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

    void loadLevel(const char *filename);
    void loadRemoteLevel(const char* filename);
    void remoteLevelCallback(std::string data);

    ~SceneGame();
private:
    Scene* scene;

    Snake snake;
    std::vector<std::vector<ObjectStack>> level;

    static const int SIZE = 20;

    void loadLevelFromDefinitions(
            std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<GameObjectDefinition>>>>>& definitions);

    GameObject * getObjectOnTopAt(Vec2 position);
    GameObject * getObjectBySnake(Utils::Direction direction);
    Vec2 getLevelCoords(Node* node);

    Vec2 screenToWorld(Vec2 screen);
    void moveSnake(Utils::Direction direction);
    void moveObject(GameObject* object, Vec2 newPos);

    void moveObject(GameObject* object, Utils::Direction direction);
    void addObject(std::unique_ptr<GameObject> object, Vec2 pos);

    void addObject(std::unique_ptr<GameObject> object);

    void removeObject(GameObject* object);

    void printDebugLevel();

    GameObject *getObjectByObject(GameObject *gameObject, Utils::Direction direction);
};
