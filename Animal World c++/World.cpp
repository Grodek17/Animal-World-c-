#include "World.h"
#include <iostream>
#include <algorithm>

World::World(int width, int height)
    : width(width), height(height) {
    worldWin = newwin(height + 2, width + 2, 3, 3);
    box(worldWin, 0, 0);
    wrefresh(worldWin);

    //tego tez do konca nie rozumiem
    board = std::vector<std::vector<Organism*>>(height, std::vector<Organism*>(width, nullptr));

    //lista organizmow jest pusta
    organisms = {};
}

World::~World() {
    delwin(worldWin);
}

void World::drawWorld() {
    box(worldWin, 0, 0);

    //czemu ++y a nie y++
    //czyszczenie planszy
    for (int y = 1; y <= height; ++y) {
        for (int x = 1; x <= width; ++x) {
            mvwaddch(worldWin, y, x, ' ');
        }
    }

    //drukowanie organizmow na planszy
    //jwszcze raz co oznacza ten zapis z dwukropkiem?
    for (Organism* org : organisms) {
        int x = org->getX();
        int y = org->getY();
        char look = org->getLook();
        //+1 omija ramke
        mvwaddch(worldWin, y + 1, x + 1, look);
    }
    wrefresh(worldWin);
}

//sprawdza czy dana koordynata znajduje sie w granicach mapy
bool World::isInside(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

//zwraca organizm na okreslinym polu
Organism* World::getOrganismAt(int x, int y) const {
    if (!isInside(x, y)) return nullptr;
    return board[y][x];
}

//przemieszcza organizm na nowe miejsce
void World::moveOrganism(Organism* org, int newX, int newY) {
    

    int oldX = org->getX();
    int oldY = org->getY();

    board[oldY][oldX] = nullptr;
    board[newY][newX] = org;
    org->setPosition(newX, newY);
}

//znajdz pole odpowiednie do reprodukcji
bool World::findFreeNeighbor(int x, int y, int& outX, int& outY) const {
    static const int dx[] = { 1, -1, 0, 0 };
    static const int dy[] = { 0, 0, 1, -1 };
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isInside(nx, ny) && board[ny][nx] == nullptr) {
            outX = nx;
            outY = ny;
            return true;
        }
    }
    return false;
}

//dodaj organizm w danym miejscu
void World::addOrganism(Organism* org) {
    organisms.push_back(org);
    int x = org->getX();
    int y = org->getY();
    board[y][x] = org;
}

//prosty log, nie wiadomo czy dzialalalal
void World::log(const std::string& text) {
    mvprintw(logCounter, width + 4, "[LOG] %s", text.c_str()); // np. obok planszy
    refresh();
    logCounter++;
}

void World::clearLogs() {
    for (int i = 0; i < logCounter; ++i) {
        mvprintw(i, width + 4, "                              "); // czyszczenie linii logów
    }
    logCounter = 0;
}

//sortowanie organizmow po inicjatywie i wieku
void World::sortOrganisms() {
    sort(organisms.begin(), organisms.end(), [](Organism* a, Organism* b) {
        if (a->getInitiative() != b->getInitiative())
            return a->getInitiative() > b->getInitiative();
        return a->getAge() > b->getAge();
        });
}

//usuwanie organizmu
void World::removeOrganism(Organism* org) {
    int x = org->getX();
    int y = org->getY();

    board[y][x] = nullptr;

    // usuwamy ze struktury organisms
    organisms.erase(std::remove(organisms.begin(), organisms.end(), org), organisms.end());

    delete org; // zwalniamy pamiêæ
}