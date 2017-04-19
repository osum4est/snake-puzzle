#include "Snake.h"



Snake::Snake()
{
	setMoving(false);
}

bool Snake::isMoving()
{
	return moving;
}

void Snake::setMoving(bool moving)
{
	this->moving = moving;
}

Snake::~Snake()
{
}

SnakePart * Snake::getHead() {
    return head;
}

void Snake::setHead(SnakePart *head) {
	this->head = head;
}

std::deque<SnakePart *> & Snake::getBody() {
	return body;
}

void Snake::addBodyPart(SnakePart *part) {
	part->setPosition(head->getPosition());
	body.push_front(part);
}
