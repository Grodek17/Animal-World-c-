#include "Animal.h"
#include "World.h"  // potrzebny do world->metody

#include <algorithm>
#include <random>
#include <vector>
#include <typeinfo>


void Animal::move() {
    //tutaj chyba potem to zmienic na zwykly random aby poruszalo sie gora dol lewo prawo
    static const int dx[] = { 1, -1, 0, 0 };
    static const int dy[] = { 0, 0, 1, -1 };

    std::vector<int> directions = { 0, 1, 2, 3 };

    // Generator losowy do std::shuffle
    static std::random_device rd;
    static std::mt19937 g(rd());

    std::shuffle(directions.begin(), directions.end(), g);

    //nie rozumiem tego zapisu z dwukropkiem chatgpt prosze wytlumacz to dziekuje
    for (int dir : directions) 
    {
        int newX = x + dx[dir];
        int newY = y + dy[dir];

        //sprawdzamy czy nowe koordynaty s¹ wewn¹trz planszy?
        if (world->isInside(newX, newY)) {
            //sprawdzamy czy na nowym miejscu jest jakis organizm
            Organism* other = world->getOrganismAt(newX, newY);

            //jesli nie, po prostu wchodzimy na to miejsce
            if (other == nullptr) {
                world->moveOrganism(this, newX, newY);
                world->log("ruch: " + std::string(1, this->draw()) +
                    " | wiek: " + std::to_string(this->getAge()) +
                    " | inicjatywa: " + std::to_string(this->getInitiative()));
                return;
            }
            else {
                collision(other);
                return;
            }
        }
    }
}

void Animal::collision(Organism* other) {
    if (typeid(*this) == typeid(*other)) {
        
        int spawnX = x;
        int spawnY = y;
        if (world->findFreeNeighbor(x, y, spawnX, spawnY)) {
            Organism* child = this->createCopy(spawnX, spawnY);
            world->addOrganism(child);
            world->log("rozmna¿anie: " + std::string(1, draw()));
        }
    }
    else {
        

        world->log("walka: " + std::string(1, draw()) +
            " (" + std::to_string(getStrength()) + ")" +
            " vs " + std::string(1, other->draw()) +
            " (" + std::to_string(other->getStrength()) + ")");

        if (getStrength() >= other->getStrength()) {
            // this wygrywa
            world->removeOrganism(other); // trzeba dodaæ!
            world->moveOrganism(this, other->getX(), other->getY());

            world->log("zwyciezca: " + std::string(1, draw()));
        }
        else {
            // this przegrywa
            world->log("zgin¹³: " + std::string(1, draw()));
            world->removeOrganism(this);
            
        }
    }
}