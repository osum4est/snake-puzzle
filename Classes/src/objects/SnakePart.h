#pragma once
#include "GameObject.h"

class SnakePart : public GameObject
{
public:
	SnakePart(Id id, Color4F color);
	~SnakePart();
};

