#pragma once

#include <src/objects/Id.h>

class GameObjectDefinition
{
public:
    GameObjectDefinition();

    GameObjectDefinition(Id id);

    Id getId();

	virtual ~GameObjectDefinition();

private:
	Id id;
};

