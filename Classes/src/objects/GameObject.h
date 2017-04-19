#pragma once

#include <cocos2d.h>
#include "Id.h"

USING_NS_CC;

class GameObject
{
public:
	GameObject();
	GameObject(Id id, Color4F color, Vec2 position);
	GameObject(Id id, Color4F color, float x, float y);
	GameObject(Id id, Color4F color, float x, float y, const Vec2 rectangle[]);
	GameObject(Id id, Color4F color);
	GameObject(Id id, Color4F color, const Vec2 rectangle[]);

	void setPosition(const Vec2& position);
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setPositionY(float y);

	const Vec2& getPosition();
	float getPositionX();
	float getPositionY();

	DrawNode* getNode();
//	static GameObject& getNull();

	Id getId();

	~GameObject();

private:
	Id id;
	Color4F color;
	DrawNode* node;

	static const int SIZE = 20;

protected:
	static const Vec2 RECTANGLE_SMALL[4];
	static const Vec2 RECTANGLE[4];
};

