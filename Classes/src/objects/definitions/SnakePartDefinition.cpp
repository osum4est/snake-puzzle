//
// Created by osum4est on 4/10/17.
//

#include <src/objects/Id.h>
#include "SnakePartDefinition.h"

SnakePartDefinition::SnakePartDefinition(Id id, int partIndex) : GameObjectDefinition(id), partIndex(partIndex) {

}

int SnakePartDefinition::getPartIndex() {
    return partIndex;
}
