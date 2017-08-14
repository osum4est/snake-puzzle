#pragma once

#include <src/util/Utils.h>
#include "SnakePart.h"

USING_NS_CC;

class Snake
{

public:
	Snake();

	bool isMoving();
	void setMoving(bool moving);
//	void move(Utils::Direction direction);

	SnakePart* getHead();
	void setHead(SnakePart* head);
	std::deque<SnakePart*>& getBody();
	void addBodyPart(SnakePart* part);

	~Snake();

private:
	SnakePart* head;
	std::deque<SnakePart*> body;

	bool moving;
//	Utils::Direction facing;
};

