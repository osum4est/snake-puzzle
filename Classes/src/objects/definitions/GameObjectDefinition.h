#pragma once

#include <src/objects/Id.h>
#include <json.hpp>

using namespace nlohmann;

class GameObjectDefinition {
public:
    GameObjectDefinition();

    GameObjectDefinition(Id id);

    Id getId();

    json getProperties();

    void setProperties(json properties);

    virtual ~GameObjectDefinition();

private:
    Id id;
    json properties;
};

