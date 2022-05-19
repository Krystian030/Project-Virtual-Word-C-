#include "Antelope.h"
#define PROBABILITY 50
#define ANTELOPE_POSSIBILITIES 16

Antelope::Antelope(Organisms* organisms, Coordinates coordinates) {
	features.strength = 4;
	features.initiative = 4;
	features.age = 0;
	features.sign = 'A';
	features.name = "Antylopa";
	world = organisms;
	this->coordinates = coordinates;
}

/*Metoda odpowiedziala za akcje antylopy - ma ona zasieg ruchu na 2 pola*/
void Antelope::action(){
	Coordinates directions[ANTELOPE_POSSIBILITIES], newCoordinations, currCoordinations;    
	int directionsPossibilities = 0;
	for (int i = -2; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			currCoordinations = coordinates.move(i, j);
			if (this->canMove(currCoordinations)) {
				directions[directionsPossibilities] = currCoordinations;
				++directionsPossibilities;
			}
		}
	}
	int index = rand() % directionsPossibilities;
	newCoordinations = directions[index];
	Organism* adjacentOrganism = world->getOrganism(newCoordinations);
	if (adjacentOrganism != nullptr && adjacentOrganism != this) {
		collision(adjacentOrganism);
	}
	else {
		this->takeMove(newCoordinations);
	}
}
/*Metoda odpowiedzialna za defensywna postawe antylopy w razie jej zaatakowania ma 50% szans na ucieczke*/
void Antelope::defensive(Organism* enemy){
	bool runAway = false;
	int probability = 100 / PROBABILITY;
	if (!(rand() % probability)) {
		Coordinates directions[ANTELOPE_POSSIBILITIES], newCoordinations, currCoordinations;
		int directionsPossibilities = 0;
		for (int i = -2; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				currCoordinations = coordinates.move(i, j);
				if (this->canMove(currCoordinations) && world->getOrganism(currCoordinations)==nullptr) {
					directions[directionsPossibilities] = currCoordinations;
					++directionsPossibilities;
				}
			}
		}
		if (directionsPossibilities) {
			int index = rand() % directionsPossibilities;
			newCoordinations = directions[index];
			enemy->takeMove(coordinates);
			this->takeMove(newCoordinations);
			string report = "Antylopa uciekla przed " + enemy->getName() + " uciekajac na pole "
			+ " (" + to_string(newCoordinations.GetX()) + ", " + to_string(newCoordinations.GetY()) + ")";
			world->addReport(report);
			runAway = true;
		}
	}
	if(!runAway) {
		if (enemy->getFeatures().strength >= this->features.strength) {
			world->addTokillOrganism(coordinates);
			enemy->takeMove(coordinates);
			string report = enemy->getName() + " zjadl/a " + this->getName();
			world->addReport(report);
		}
		else {
			world->addTokillOrganism(enemy->getCoordinates());
			string report = this->getName() + " zjadl/a " + enemy->getName();
			world->addReport(report);
		}
	}
}