#include "DeadlyNightshades.h"

DeadlyNightshades::DeadlyNightshades(Organisms* organisms, Coordinates coordinates){
	features.strength = 99;
	features.initiative = 0;
	features.age = 0;
	features.sign = '+';
	features.name = "Wilcze jagody";
	world = organisms;
	this->coordinates = coordinates;
}
/*Metoda akcji, pr�ba rozprzestrzeniania si� - zmniejszona ni� dla pozosta�ych gatunk�w ro�lin*/
void DeadlyNightshades::action(){
	//Pr�ba rozprzestrzeniania si�
	int probability = 100 / DEADLYNIGHTSHADES_PROBABILITY;
	if (!(rand() % probability)) spreading();
}

/*Metoda kolizji obs�uguje �mier� organizmu kt�ry zje wilcze jagody*/
void DeadlyNightshades::collision(Organism* adjacentOrganism){
	Coordinates adjacentCoordinates = adjacentOrganism->getCoordinates();
	world->addTokillOrganism(adjacentCoordinates);
	world->addTokillOrganism(coordinates);
	world->removeField(coordinates);
	world->removeField(adjacentCoordinates);
	string report = adjacentOrganism->getName() + " zjadl/a  trujace " + this->getName() + " co doprowadza go do smierci ";
	world->addReport(report);
}
