//klasa abstrakcyjna animal dziedzicz¹ca po organizmie
#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
    //ten konstruktor jest troche dziwny, wiem ze dziedziczymy po organizmie
    Animal(int str, int init, int x, int y, char look, World* world)
        : Organism(str, init, x, y, look, world) {
    }

    //co oznacza override?
    virtual void move() override;
    virtual void collision(Organism* other) override;


    virtual Organism* createCopy(int newX, int newY) = 0; // czysto wirtualna do klonowania
};
