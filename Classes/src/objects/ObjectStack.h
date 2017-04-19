//
// Created by osum4est on 4/17/17.
//

#ifndef SNAKE_PUZZLE_OBJECTSTACK_H
#define SNAKE_PUZZLE_OBJECTSTACK_H


#include <bits/unique_ptr.h>
#include "GameObject.h"

class ObjectStack {

public:
    ObjectStack();

    GameObject* getBottom();
    GameObject* getTop();

    GameObject* operator[](int i);

    void pushBottom(std::unique_ptr<GameObject> object);
    void pushBottom(GameObject* object);
    void pushTop(std::unique_ptr<GameObject> object);
    void pushTop(GameObject* object);

    bool isEmpty();

    void remove(GameObject* object);
    void release(GameObject* object);

    int size();

private:
    std::vector<std::unique_ptr<GameObject>> stack;
};


#endif //SNAKE_PUZZLE_OBJECTSTACK_H
