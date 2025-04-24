//klasa czysto "wirtualna"/abstrakcyjna, nie posiada funkcji w pliku .cpp
#pragma once
#include <curses.h>
#include "World.h"

//make class World visible for organism
class World;

class Organism
{
protected:
	int str;
	int init;
	int x;
	int y;
	int age = 0; 
	char look;
	World* world; 

public:
	Organism(int str, int init, int x, int y, char look, World* world)
		: str(str), init(init), x(x), y(y), look(look), world(world){}

	virtual ~Organism() {}

	virtual void move() = 0;
	virtual void collision(Organism* other) = 0;
	virtual char draw() const = 0;

	//getters and setters
	int getX() const { return x; }
	int getY() const { return y; }
	void setPosition(int newX, int newY) { x = newX; y = newY; }

	int getStrength() const { return str; }
	void setStrength(int s) { str = s; }

	int getInitiative() const { return init; }

	int getAge() const { return age; }
	void incrementAge() { age++; }

	char getLook() const { return look; }
	void changeLook(char l) { look = l; }

	World* getWorld() const { return world; }
};

