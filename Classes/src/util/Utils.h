#pragma once

#include "cocos2d.h"

USING_NS_CC;

// Can u see this?
class Utils
{
public:
	Utils();

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

	static int sgn(int number);
	static Vec2 getVec2FromDirection(Direction direction);
	static std::vector<std::string> split(const std::string string, char delimeter);

	~Utils();
};

