//funkcja main, wywoluje elementy innych klas, niekoniecznie robiac cos tutaj
//to do
//rozmnazanie w random kierunku -> mniejsza szansa na bakteria-like rozmnozenie
//logs appear sooner than actual move

#include <curses.h>
#include <algorithm>
#include "World.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Antelope.h"

using namespace std;

int main() {
    //inicjaizacja ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(-1);

    //tworzymy obiekt world
    World world(10, 10);

    // dodawanie organizmow, [todo] zrobic to lepiej, tablica albo cos
    //Sheep* sheep1 = new Sheep(8, 8, &world);
    //Sheep* sheep2 = new Sheep(7, 7, &world);
    Wolf* wolf1 = new Wolf(7, 7, &world);

    Antelope* antelope1 = new Antelope(5, 5, &world);

    //dodac organizmy nowe do zbioru organizmow?
    //world.addOrganism(sheep1);
    //world.addOrganism(sheep2);
    world.addOrganism(wolf1);
    world.addOrganism(antelope1);

    //glowna petla gry/symulacji
    while (true) 
    {
        //czyscimy stare logi
        world.clearLogs();

        //rysujemy swiat, z obecnymi pozycjami zwierzatek
        //world.drawWorld();

        world.log("Tura startuje");
       // mvprintw(1, 1, "Nacisnij klawisz aby wykonac ture (ESC = koniec)");
         
        //ostatnie dwie byly tutaj
        world.log("Tura konczy sie");
        //refresh();

        

        //kopiujemy liste organizmow? moze to jako metoda w world, error powodowalo wyjscie poza mape
        vector<Organism*> toMove = world.getOrganisms();

        world.sortOrganisms();


        for (Organism* org : toMove) {
            if (org != nullptr) {
                org->move();
                org->incrementAge();
            }
        }
        //pozniej bedzie tu sterowanie graczem
        world.drawWorld();
        refresh();
        int ch = getch();
        if (ch == 27) break;
        
    }

    //end simulation
    endwin();
    return 0;
}
