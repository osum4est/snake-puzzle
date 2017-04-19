#include "GameObject.h"

// TODO: we shouldn't need this
GameObject::GameObject() : GameObject(Id::EMPTY_SPACE, Color4F(0, 0, 0, 0)) {

}

GameObject::GameObject(Id id, Color4F color, const Vec2 rectangle[]) : color(color), node(DrawNode::create()), id(id) {
    node->drawPolygon(rectangle, rectangle->length(), color, 0, Color4F::BLACK);
}

GameObject::GameObject(Id id, Color4F color, Vec2 position) : GameObject(id, color)
{
	node->setPosition(position);
}

GameObject::GameObject(Id id, Color4F color, float x, float y) : GameObject(id, color)
{
	node->setPosition(x, y);
}

GameObject::GameObject(Id id, Color4F color, float x, float y, const Vec2 rectangle[]) : GameObject(id, color, rectangle) {
    node->setPosition(x, y);
}

GameObject::GameObject(Id id, Color4F color) : GameObject(id, color, RECTANGLE_SMALL)
{

}

void GameObject::setPosition(const Vec2& position)
{
	node->setPosition(position);
}

void GameObject::setPosition(float x, float y)
{
	node->setPosition(x, y);
}

void GameObject::setPositionX(float x)
{
	node->setPositionX(x);
}

void GameObject::setPositionY(float y)
{
	node->setPositionY(y);
}

const Vec2& GameObject::getPosition()
{
	return node->getPosition();
}

float GameObject::getPositionX()
{
	return node->getPositionX();
}

float GameObject::getPositionY()
{
	return node->getPositionY();
}

GameObject::~GameObject()
{
}

const Vec2 GameObject::RECTANGLE[4] =
{
		Vec2(SIZE / 2, SIZE / 2),
		Vec2(SIZE / 2, -SIZE / 2),
		Vec2(-SIZE / 2, -SIZE / 2),
		Vec2(-SIZE / 2, SIZE / 2)
};

const Vec2 GameObject::RECTANGLE_SMALL[4] =
{
	Vec2(SIZE / 2 * .8, SIZE / 2 * .8),
	Vec2(SIZE / 2 * .8, -SIZE / 2 * .8),
	Vec2(-SIZE / 2 * .8, -SIZE / 2 * .8),
	Vec2(-SIZE / 2 * .8, SIZE / 2 * .8)
};

DrawNode *GameObject::getNode() {
	return node;
}

Id GameObject::getId() {
    return id;
}

//GameObject & GameObject::getNull() {
//	return null;
//}
//
//const GameObject& GameObject::null = GameObject();