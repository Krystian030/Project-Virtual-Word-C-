#include "SosnowskyHogweed.h"

SosnowskyHogweed::SosnowskyHogweed(Organisms* organisms, Coordinates coordinates){
	features.strength = 10;
	features.initiative = 0;
	features.age = 0;
	features.sign = '#';
	features.name = "Barszcz Sosnowskiego";
	world = organisms;
	this->coordinates = coordinates;
}

/*Metoda odpowiedzialna za rozprzestrzenianie sie barszczu sosnowskiego oraz zabicu organizmow w jego s¹siedztwie*/
void SosnowskyHogweed::action(){
	//Próba rozprzestrzeniania siê
	int probability = 100 / SOSNOWSKYHOGWEEED_PROBABILITY;
	if (!(rand() % probability)) spreading();

	//Zabicie wszystkich zwierz¹t w swoim s¹siedztwie
	Coordinates currCoordinations;
	Organism* organismAround;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			currCoordinations = coordinates.move(i, j);
			organismAround = world->getOrganism(currCoordinations);
			if (organismAround != nullptr && organismAround != this && organismAround->getName() != this->getName()) {
				world->addTokillOrganism(organismAround->getCoordinates());
				world->removeField(organismAround->getCoordinates());
				string report = "Barszcz sosnowskiego zabija " + organismAround->getName();
				world->addReport(report);
			}
		}
	}
}

/*Metoda odpowiedzialna za zabicie organizmu po zjedzeniu barszczu sosnowskiego*/
void SosnowskyHogweed::collision(Organism* adjacentOrganism) {
	Coordinates adjacentCoordinates = adjacentOrganism->getCoordinates();
	world->addTokillOrganism(adjacentCoordinates);
	world->addTokillOrganism(coordinates);
	world->removeField(coordinates);
	world->removeField(adjacentCoordinates);
	string report = adjacentOrganism->getName() + " zjadl/a " + this->getName() + " co doprowadza go do smierci ";
	world->addReport(report);
}