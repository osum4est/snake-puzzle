#include "GameObjectDefinition.h"



GameObjectDefinition::GameObjectDefinition()
{
}


GameObjectDefinition::~GameObjectDefinition()
{
}

GameObjectDefinition::GameObjectDefinition(Id id) : id(id){

}

Id GameObjectDefinition::getId() {
    return id;
}
