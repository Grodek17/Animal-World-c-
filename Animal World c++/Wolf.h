// Klasa Wolf - dziedziczy po Animal
// Silny drapie¿nik, atakuje inne organizmy w collision()
// Litera 'W', si³a 9, inicjatywa 5
#pragma once
#include "Animal.h"

class Wolf : public Animal
{
public:
    Wolf(int x, int y, World* world)
        : Animal(9, 5, x, y, 'W', world) {
    }

    virtual Organism* createCopy(int newX, int newY) override {
        return new Wolf(newX, newY, world);
    }

    virtual char draw() const override {
        return getLook();
    }
};

