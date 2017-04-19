//
// Created by osum4est on 4/10/17.
//

#ifndef MYGAME_SNAKEPARTDEFINITION_H
#define MYGAME_SNAKEPARTDEFINITION_H


#include "GameObjectDefinition.h"

class SnakePartDefinition : public GameObjectDefinition {

public:
    SnakePartDefinition(Id id, int partIndex);

    int getPartIndex();

private:
    int partIndex;
};


#endif //MYGAME_SNAKEPARTDEFINITION_H
