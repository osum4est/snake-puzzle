//
// Created by osum4est on 4/18/17.
//

#ifndef MYGAME_COLORS_H
#define MYGAME_COLORS_H

#include <cocos2d.h>

USING_NS_CC;

class Colors {

// My own color scheme based on Monokai
private:
    static const Color4B& BLUE;
    static const Color4B& GREEN;
    static const Color4B& MAGENTA;
    static const Color4B& ORANGE;
    static const Color4B& WHITE;
    static const Color4B& BLACK;

public:
    static const Color4F& SNAKE_HEAD;
    static const Color4F& SNAKE_BODY_DEFAULT;
    static const Color4F& FOOD_DEFAULT;
    static const Color4F& WALL;
    static const Color4F& BOX;
    static const Color4B& BACKGROUND;
};

#endif //MYGAME_COLORS_H
