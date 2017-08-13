#pragma once

#include <cocos2d.h>
#include <ui/UITextField.h>
#include <ui/UIButton.h>

USING_NS_CC;

class SceneMainMenu : public LayerColor {
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SceneMainMenu);

    void menuCloseCallback(cocos2d::Ref* sender);

    void buttonLoadLevelEvent(Ref* sender);
    void buttonLoadRemoteLevelEvent(Ref* sender);

private:
    ui::TextField* textFieldRemoteLevel;
};