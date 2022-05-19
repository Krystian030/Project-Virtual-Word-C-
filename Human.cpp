#include "Human.h"
#include "Button.h"
#define BOOST_TIME 5

Human::Human(Organisms* organisms, Coordinates coordinates) {
	boostIsAvaliable = true;
	boostIsActive = false;
	isAlive = true;
	turnsToBoost = 0;
	boostTurns = 0;
	features.strength = 5;
	features.initiative = 4;
	features.age = 0;
	features.sign = 'H';
	features.name = "Czlowiek";
	world = organisms;
	this->coordinates = coordinates;
}

/*Metoda obslugujaca akcje wykonywana przez czlowieka - ruch strzalkami oraz aktywowanie umiejetnosci specjalnej - spacja*/
void Human::action(int btn){
	boostLoading();
	int dx = 0, dy = 0;
	switch (btn) {
	case KEY_UP:
		dy = -1;
		break;
	case KEY_DOWN:
		dy = 1;
		break;
	case KEY_RIGHT:
		dx = 1;
		break;
	case KEY_LEFT:
		dx = -1;
		break;
	case KEY_SPACE:
		boostActivating();
		break;
	}
	Coordinates newCoordinates = this->coordinates.move(dx, dy);
	Organism* adjacentOrganism = world->getOrganism(newCoordinates);
	if (!boostIsActive) {
		if (adjacentOrganism != nullptr && adjacentOrganism != this) {
			collision(adjacentOrganism);
		}
		else {
			this->takeMove(newCoordinates);
		}
	}
	else {
		boostManagement(newCoordinates);
	}
}

/*Metoda aktywowania umiejetnosci specjalnej*/
void Human::boostActivating(){
	if (boostIsAvaliable) {
		boostIsAvaliable = false;
		boostIsActive = true;
		string report = "Umiejentosc Calopaenia zostala aktywowana przez czlowieka";
		world->addReport(report);
	}
	else {
		string report = "Umiejentosc Calopaenia nie jest aktualnie dostepna, badz jest juz aktywna";
		world->addReport(report);
	}

}

/*Metoda laduje umiejetnosc specjalna czlowieka*/
void Human::boostLoading() {
	if (turnsToBoost > 0 && !boostIsActive) {
		--turnsToBoost;
	}
	else if (turnsToBoost == 0 && !boostIsActive) {
		boostIsAvaliable = true;
	}
}

/*Metoda wykonujaca specjalna umiejetnosc przez czlowieka - calopalenie, trwa 5 rund i niszczy wszystkie organizmy wokol*/
void Human::boostManagement(Coordinates coordinates){
	if (boostTurns < BOOST_TIME) {
		this->takeMove(coordinates);

		Coordinates currCoordinations;
		Organism* organismAround;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				currCoordinations = coordinates.move(i, j);
				organismAround = world->getOrganism(currCoordinations);
				if (organismAround != nullptr && organismAround != this) {
					world->addTokillOrganism(organismAround->getCoordinates());
					world->removeField(organismAround->getCoordinates());
					string report = "Umiejentosc Calopaenia zneutralizowala " + organismAround->getName();
					world->addReport(report);
				}
			}
		}
		++boostTurns;
	}
	else {
		boostIsActive = false;
		boostIsAvaliable = false;
		turnsToBoost = 5;
		boostTurns = 0;
	}
}

int Human::getTurnsToBoost() const{
	return this->turnsToBoost;
}

int Human::getBoostTurns() const{
	return this->boostTurns;
}

void Human::setTurnsToBoost(int turnsToBoost){
	this->turnsToBoost = turnsToBoost;
}

void Human::setBoostTurns(int boostTurns){
	this->boostTurns = boostTurns;
}

void Human::setBoostIsActive(bool option){
	this->boostIsActive = option;
}

void Human::setBoostIsAvaliable(bool option){
	this->boostIsAvaliable = option;
}
