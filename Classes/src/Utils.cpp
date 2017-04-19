#include "Utils.h"



Utils::Utils()
{
}

int Utils::sgn(int number)
{
	return number > 0 ? 1 : -1;
}

Utils::~Utils()
{
}

Vec2 Utils::getVec2FromDirection(Utils::Direction direction) {
	switch (direction) {
		case Utils::UP:
			return Vec2(0, 1);
		case Utils::DOWN:
			return Vec2(0, -1);
		case Utils::LEFT:
			return Vec2(-1, 0);
		case Utils::RIGHT:
			return Vec2(1, 0);
	}
}
