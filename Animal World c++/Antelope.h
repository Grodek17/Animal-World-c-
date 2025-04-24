//Antelope animal
// 4 initiative, 4 strenght
//moves two fields instead of one
//has 50% chance to escape from attack
#pragma once
#include "Animal.h"
class Antelope : public Animal
{
public:
    Antelope(int x, int y, World* world)
        : Animal(4, 4, x, y, 'A', world) {
    }

    virtual Organism* createCopy(int newX, int newY) override {
        return new Antelope(newX, newY, world);
    }

    virtual char draw() const override {
        return getLook();
    }

    //override of move and colision functions

    //Antelope moves two fields instead of one
    virtual void move() override;       

    //antelope has 50% chance of escaping on neighbouring field when attacked
    virtual void collision(Organism* other) override;
};

