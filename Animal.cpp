#include "Animal.h"

/*Akcja, metoda odpowiedzialna za ruch organizmów zwierzêcych*/
void Animal::action(){
	Coordinates directions[DIRECTIONS],newCoordinations, currCoordinations;
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

/*Kolizja, metoda odpowiadaj¹ca za wzajemne kolizje miedzy organizmami*/
void Animal::collision(Organism* adjacentOrganism){
	Features tmpFeatures = adjacentOrganism->getFeatures();

	if (tmpFeatures.name == "Guarana") {
		adjacentOrganism->collision(this);
	}
	else if (tmpFeatures.name == "Wilcze jagody") {
		adjacentOrganism->collision(this);
	}
	else if (tmpFeatures.name == "Barszcz Sosnowskiego") {
		adjacentOrganism->collision(this);
	}
	else if (tmpFeatures.name == "Antylopa") {
		adjacentOrganism->defensive(this);
	}
	else if (tmpFeatures.sign != this->features.sign) {

		if (tmpFeatures.strength > this->features.strength) {
			world->addTokillOrganism(coordinates);
			string report = adjacentOrganism->getName() + " zjadl/a " + this->getName();
			world->addReport(report);
		}
		else {
			if (tmpFeatures.name == "Zolw") {             //Jezeli organizm zaatakuje ¿ó³wia to ¿ó³w ma szanse, aby odeprzeæ atak
				adjacentOrganism->defensive(this);
			}
			else {
				world->addTokillOrganism(adjacentOrganism->getCoordinates());
				this->takeMove(adjacentOrganism->getCoordinates());
				string report = this->getName() + " zjadl/a " + adjacentOrganism->getName();
				world->addReport(report);
			}
		}
	}
	else {
		if (world->getList()->size() < (world->getHeight() * world->getWidth())) {		//Sprawdzenie czy s¹ dostêpne miejsca na rozmna¿anie
			breeding(this);
		}
	}
}

/*Metoda odpowiedzialna za rozmna¿anie sie organizmów*/
void Animal::breeding(Organism* adjacentOrganism){
	Coordinates childCoordinates = world->findCoordinates(coordinates, adjacentOrganism->getCoordinates());
	if (childCoordinates != Coordinates(-1, -1)) {
		Organism* child = world->createOrganismType(this->getName(), childCoordinates); //(world, childCoordinates);
		world->addOrganism(child);
		string report = "Nowy piekny poczatek " + adjacentOrganism->getName() + " wydaje na swiat dziecko na polu ("
			+ to_string(childCoordinates.GetX()) + " ," + to_string(childCoordinates.GetY()) + ")";
		world->addReport(report);
	}
}

