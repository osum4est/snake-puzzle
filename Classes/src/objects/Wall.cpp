#include <src/Colors.h>
#include "Wall.h"



Wall::Wall(float x, float y) : GameObject(WALL, Colors::WALL, x, y, RECTANGLE)
{
}



Wall::~Wall()
{
}
