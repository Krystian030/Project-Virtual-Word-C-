#include "Plant.h"

void Plant::collision(Organism* adjacentOrganism){}

/*Metoda odpowiadajaca za rozprzestrzenianie sie organizmow, jeœli zajdzie uruchamiana jest metoda spread*/
void Plant::action() {
	int probability = 100 / PROBABILITY;
	if (!(rand() % probability)) spreading();
}

/*Metoda szuka wolnego miejsca do rozprzestrzenienia sie*/
Coordinates Plant::findField(Coordinates coordinates){
	Coordinates directions[DIRECTIONS],currCoordinations;
	int directionsPossibilities = 0;
	for (int i = -1; i < 2; i++) {
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
		return directions[index];
	}
	else return Coordinates(-1,-1);
}

/*Metoda odpowidaj¹ca za rozprzestrzenianie sie organizmu, szuka wolnego miejsca i tworzy tam nowy organizm roœlinny*/
void Plant::spreading() {
	Coordinates seedPosition = findField(coordinates);
	if (seedPosition != Coordinates(-1,-1)) {
		Organism* plantChild = world->createOrganismType(this->getName(), seedPosition);
		world->addOrganism(plantChild);
		string report = "Na swiecie rozprzestrzenia sie nowa roslina " + this->getName() +
			" na polu (" + to_string(seedPosition.GetX()) + ", " + to_string(seedPosition.GetY()) + ")";
		world->addReport(report);
	}
}
