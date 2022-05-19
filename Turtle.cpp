#include "Turtle.h"
#define PROBABILITY 25
#define DEFENSIVE 5 //Wartoœæ do której ¿ó³w odpiera atak

Turtle::Turtle(Organisms* organisms, Coordinates coordinates) {
	features.strength = 2;
	features.initiative = 1;
	features.age = 0;
	features.sign = 'T';
	features.name = "Zolw";
	world = organisms;
	this->coordinates = coordinates;
}

/*Metoda odpowiadajaca za powstrzymanie poruszanie siê ¿ó³wia, w 75% przypadkach nie zmienia on swojej pozycji*/
void Turtle::action(){
	int probability = 100/PROBABILITY;
	if (!(rand() % probability)) {
		Coordinates directions[DIRECTIONS], newCoordinations, currCoordinations;
		int directionsPossibilities = 0;
		for (int i = -1; i < 2; i++) {
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
}

/*Metoda defensywna ¿ó³wia, w wyniku natarcia organizmu atakuj¹cego ma mo¿liwoœæ obronienia sie*/
void Turtle::defensive(Organism* enemy){
	if (enemy->getFeatures().strength <= DEFENSIVE) {
		string report = this->getName() + " odparl atak " + enemy->getName() + " i zostaje na swoim polu";
		world->addReport(report);
	}
	else {
		world->addTokillOrganism(coordinates);
		enemy->takeMove(coordinates);
		string report = enemy->getName() + " zjadl/a " + this->getName();
		world->addReport(report);
	}
}

