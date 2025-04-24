#include "Antelope.h"
#include <random>
#include <algorithm>

void Antelope::move() {
    static const int dx[] = { 2, -2, 0, 0 };
    static const int dy[] = { 0, 0, 2, -2 };

    std::vector<int> directions = { 0, 1, 2, 3 };
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);

    for (int dir : directions) {
        int newX = x + dx[dir];
        int newY = y + dy[dir];

        if (!world->isInside(newX, newY))
            continue;

        Organism* other = world->getOrganismAt(newX, newY);
        if (other == nullptr) {
            world->moveOrganism(this, newX, newY);
            world->log("antylopa skacze!");
            return;
        }
        else {
            collision(other);
            return;
        }
    }
}

void Antelope::collision(Organism* other) {
    if (this == other) return;

    static std::random_device rd;
    static std::mt19937 g(rd());
    std::uniform_int_distribution<> dist(0, 1);

    if (dist(g) == 0) {
        int escapeX = x, escapeY = y;
        if (world->findFreeNeighbor(x, y, escapeX, escapeY) &&
            world->isInside(escapeX, escapeY)) {
            world->moveOrganism(this, escapeX, escapeY);
            world->log("Antylopa uciek³a przed " + std::string(1, other->draw()));
            return;
        }
    }

    Animal::collision(other);
}
