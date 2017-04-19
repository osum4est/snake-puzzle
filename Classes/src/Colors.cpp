#include <src/Colors.h>

// My own color scheme based on Monokai
const Color4B& Colors::BLUE                 = Color4B(102, 217, 239, 255);
const Color4B& Colors::GREEN                = Color4B(166, 226, 46 , 255);
const Color4B& Colors::MAGENTA              = Color4B(249, 38 , 114, 255);
const Color4B& Colors::ORANGE               = Color4B(253, 151, 31 , 255);
const Color4B& Colors::WHITE                = Color4B(248, 248, 242, 255);
const Color4B& Colors::BLACK                = Color4B(39 , 40 , 34 , 255);

const Color4F& Colors::SNAKE_HEAD           = Color4F(BLUE);
const Color4F& Colors::SNAKE_BODY_DEFAULT   = Color4F(GREEN);
const Color4F& Colors::FOOD_DEFAULT         = Color4F(MAGENTA);
const Color4F& Colors::BOX                  = Color4F(ORANGE);
const Color4F& Colors::WALL                 = Color4F(WHITE);
const Color4B& Colors::BACKGROUND           = Color4B(BLACK);