#include "GameObjectDefinition.h"


GameObjectDefinition::GameObjectDefinition() {
}


GameObjectDefinition::~GameObjectDefinition() {
}

GameObjectDefinition::GameObjectDefinition(Id id) : id(id) {

}

Id GameObjectDefinition::getId() {
    return id;
}

json GameObjectDefinition::getProperties() {
    return properties;
}

void GameObjectDefinition::setProperties(json properties) {
    this->properties = properties;
}
