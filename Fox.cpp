#include "Fox.h"

Fox::Fox(Organisms* organisms, Coordinates coordinates) {
	features.strength = 3;
	features.initiative = 7;
	features.age = 0;
	features.sign = 'F';
	features.name = "Lis";
	world = organisms;
	this->coordinates = coordinates;
}

/*Metoda obslugujaca akcje lisa, lis nie zajmie pola ktore jest zajete przez silniejszy organizm*/
void Fox::action(){
	Coordinates directions[DIRECTIONS], newCoordinations, currCoordinations;
	Organism* adjacentOrganism = nullptr;
	int directionsPossibilities = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			currCoordinations = coordinates.move(i, j);
			if (this->canMove(currCoordinations)) {
				adjacentOrganism = world->getOrganism(currCoordinations);
				if (adjacentOrganism == nullptr) {
					directions[directionsPossibilities] = currCoordinations;
					++directionsPossibilities;
				}
				else if (adjacentOrganism->getFeatures().strength < features.strength) {
					directions[directionsPossibilities] = currCoordinations;
					++directionsPossibilities;
				}
			}
		}
	}
	if (directionsPossibilities != 0) {
		int index = rand() % directionsPossibilities;
		newCoordinations = directions[index];
		adjacentOrganism = world->getOrganism(newCoordinations);
		if (adjacentOrganism != nullptr && adjacentOrganism != this) {
			collision(adjacentOrganism);
		}
		else {
			this->takeMove(newCoordinations);
		}
	}
}

