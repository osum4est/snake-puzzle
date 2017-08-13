//
// Created by osum4est on 8/13/17.
//

#include <src/Colors.h>
#include "SceneMainMenu.h"
#include "SceneGame.h"

Scene *SceneMainMenu::createScene() {
    auto scene = Scene::create();
    auto layer = SceneMainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool SceneMainMenu::init() {
    if (!LayerColor::initWithColor(Colors::BACKGROUND)) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(SceneMainMenu::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    auto buttonLoadLevel = ui::Button::create("button.png");
    buttonLoadLevel->setTitleText("Load test level");
    buttonLoadLevel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    buttonLoadLevel->ignoreContentAdaptWithSize(false);
    buttonLoadLevel->setContentSize(Size(100, 50));
    buttonLoadLevel->addClickEventListener(CC_CALLBACK_1(SceneMainMenu::buttonLoadLevelEvent, this));
    this->addChild(buttonLoadLevel);

    textFieldRemoteLevel = ui::TextField::create("easy001.lvl", "Arial", 14);
    textFieldRemoteLevel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));
    this->addChild(textFieldRemoteLevel);

    auto buttonLoadRemoteLevel = ui::Button::create("button.png");
    buttonLoadRemoteLevel->setTitleText("Load remote level");
    buttonLoadRemoteLevel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));
    buttonLoadRemoteLevel->ignoreContentAdaptWithSize(false);
    buttonLoadRemoteLevel->setContentSize(Size(100, 50));
    buttonLoadRemoteLevel->addClickEventListener(CC_CALLBACK_1(SceneMainMenu::buttonLoadRemoteLevelEvent, this));
    this->addChild(buttonLoadRemoteLevel);
}

void SceneMainMenu::menuCloseCallback(cocos2d::Ref *sender) {
    EventCustom customEndEvent("game_scene_close_event");
    _eventDispatcher->dispatchEvent(&customEndEvent);
}

void SceneMainMenu::buttonLoadLevelEvent(Ref *sender) {
    auto game = SceneGame::createScene();
    game->loadLevel("001.lvl");
    Director::getInstance()->pushScene(TransitionCrossFade::create(.25, game->getScene()));
}

void SceneMainMenu::buttonLoadRemoteLevelEvent(Ref *sender) {
    auto game = SceneGame::createScene();
    game->loadRemoteLevel(textFieldRemoteLevel->getString().c_str());
    Director::getInstance()->pushScene(TransitionCrossFade::create(.25, game->getScene()));
}
