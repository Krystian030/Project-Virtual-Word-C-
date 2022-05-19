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
/*Metoda akcji, próba rozprzestrzeniania siê - zmniejszona ni¿ dla pozosta³ych gatunków roœlin*/
void DeadlyNightshades::action(){
	//Próba rozprzestrzeniania siê
	int probability = 100 / DEADLYNIGHTSHADES_PROBABILITY;
	if (!(rand() % probability)) spreading();
}

/*Metoda kolizji obs³uguje œmieræ organizmu który zje wilcze jagody*/
void DeadlyNightshades::collision(Organism* adjacentOrganism){
	Coordinates adjacentCoordinates = adjacentOrganism->getCoordinates();
	world->addTokillOrganism(adjacentCoordinates);
	world->addTokillOrganism(coordinates);
	world->removeField(coordinates);
	world->removeField(adjacentCoordinates);
	string report = adjacentOrganism->getName() + " zjadl/a  trujace " + this->getName() + " co doprowadza go do smierci ";
	world->addReport(report);
}
