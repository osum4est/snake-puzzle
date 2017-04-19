//

#include "ObjectStack.h"

//
// Created by osum4est on 4/17/17.

ObjectStack::ObjectStack() {

}

GameObject *ObjectStack::getBottom() {
    if (isEmpty())
        return nullptr;
    return stack.front().get();
}

GameObject *ObjectStack::getTop() {
    if (isEmpty())
        return nullptr;
    return stack.back().get();
}

void ObjectStack::pushBottom(std::unique_ptr<GameObject> object) {
    stack.insert(stack.begin(), std::unique_ptr<GameObject>(std::move(object)));
}

void ObjectStack::pushBottom(GameObject *object) {
    stack.insert(stack.begin(), std::unique_ptr<GameObject>(std::move(object)));

}

void ObjectStack::pushTop(std::unique_ptr<GameObject> object) {
    stack.push_back(std::unique_ptr<GameObject>(std::move(object)));

}

void ObjectStack::pushTop(GameObject *object) {
    stack.push_back(std::unique_ptr<GameObject>(std::move(object)));
}

int ObjectStack::size() {
    return stack.size();
}

GameObject *ObjectStack::operator[](int i) {
    return stack[i].get();
}

void ObjectStack::remove(GameObject *object) {
    for (int i = 0; i < stack.size(); i++) {
        if (stack[i].get() == object) {
            stack[i].reset();
            stack.erase(stack.begin() + i);
        }
    }
}

void ObjectStack::release(GameObject *object) {
    for (int i = 0; i < stack.size(); i++) {
        if (stack[i].get() == object) {
            stack[i].release();
            stack.erase(stack.begin() + i);
        }
    }
}

bool ObjectStack::isEmpty() {
    return stack.empty();
}
