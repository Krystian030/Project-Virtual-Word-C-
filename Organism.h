#pragma once
#include <string>
#include "Coordinates.h"
#include "Organisms.h"
using namespace std;
class Organisms;

struct Features {
	int strength;
	int initiative;
	int age;
	char sign;
	string name;
	bool toDead; //Flaga do zabica organizmu
	bool isDead; //Flaga czy organizm zosta³ ju¿ "zabity"
};

class Organism {

	
protected:
	Features features;
	Coordinates coordinates;
	Organisms* world;

public:
	Organism();
	virtual void action() = 0;
	virtual void action(int move);
	virtual void collision(Organism* adjacentOrganism) = 0;
	virtual void draw();
	virtual void defensive(Organism* enemy);
	Features getFeatures() const;
	Coordinates getCoordinates() const;
	void getOlder();
	void increaseStrength(int number);
	void setExistence();	//Ustawia flage toDead na true jeœli organizm ma zostaæ usuniêty
	void setIsDead(); //Ustawia flage isDead na true jesli organizm zosta³ usuniêty
	void takeMove(Coordinates coordinates);
	Organisms* getWorld();
	bool canMove(Coordinates coordinates);
	int getAge() const;
	void setAge(int age);
	int getStrength() const;
	void setStrength(int strength);
	string getName() const;
};
