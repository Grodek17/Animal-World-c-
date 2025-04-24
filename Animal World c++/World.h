//glowny "manager" symulacji, posiada mape oraz  rozporzadza ruchem organizmow oraz przebiegeiem gry
#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include "Organism.h"

using namespace std;

class Organism;

class World {
private:
    int width;
    int height;
    WINDOW* worldWin;

    //dwuwymiarowy wektor zawieraj¹cy organizmy na naszej planszy?
    vector<vector<Organism*>> board;

    //lista organizmow na planszy
    vector<Organism*> organisms;

    int logCounter = 0; // y-koordynata aktualnego loga (np. start od 0 lub od height+1)

public:
    World(int width = 25, int height = 30);
    ~World();

    //wypisz mape gry na ekran, bez zadnych aktualizacji ani nic
    void drawWorld();

    //sprawdz czy podany koordynat jest w mapie, moze petla while poki nie bedzie
    bool isInside(int x, int y) const;

    //sprawdz jaki organizm znajduje sie na danym miejscu, null jesli nic nie ma
    Organism* getOrganismAt(int x, int y) const;

    //porusza danym organizmem -> tu chyba zaczyna sie magia polimorfizmu -> nie wazne czy to wolf, sheep czy cokolwiek innego wystarczy pointer na organizm 
    void moveOrganism(Organism* org, int newX, int newY);

    //prawdopodobnie dla rozmnazania
    bool findFreeNeighbor(int x, int y, int& outX, int& outY) const;

    //glowna funkcja rozmnazania
    void addOrganism(Organism* org);

    //wypisywanie logow
    void log(const string& text);

    //czyszczenie okienka logow
    void clearLogs();

    //sortowanie organizmow po inicjatywie i wieku
    void sortOrganisms();

    //nie wiem co to jest i do  czego to sluzy
    const vector<Organism*>& getOrganisms() const { return organisms; }

    //usun organizm
    void removeOrganism(Organism* org);
};
