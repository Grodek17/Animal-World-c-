#pragma once
#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep(int x, int y, World* world)
        : Animal(4, 4, x, y, 'S', world) {
    }

    virtual Organism* createCopy(int newX, int newY) override {
        return new Sheep(newX, newY, world);
    }

    virtual char draw() const override {
        return getLook();
    }
};
