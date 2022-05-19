#include "Organisms.h"
#include "Initializer.h"
#include "Plant.h"
#include "Guarana.h"
#include <fstream>

Organisms::Organisms(){
	reportsNumbers = 0;
	deathsNumbers = 0;
}

int Organisms::getOrganismPopulity() const{
	return this->organismPopulity;
}

void Organisms::setOrganismPopulity(int number){
	this->organismPopulity = number;
}

list<Organism*>* Organisms::getList(){
	return &listOrganisms;
}

/*Pobiera tablice raportów*/
string* Organisms::getReports(){
	return this->reports;
}

/*Dodaje raport do tablicy raportow*/
void Organisms::addReport(string report){
	if (reportsNumbers < REPORT_NUMBER) {
		this->reports[reportsNumbers] = report;
		++reportsNumbers;
	}
}

/*Ustawia ilosc raportow w tablicy*/
void Organisms::setReportsNumbers(int reportsNumbers){
	this->reportsNumbers = reportsNumbers;
}

/*Pobiera informacje na temat ilosci raportow w tablicy raprtow (wielkosc tablicy)*/
int Organisms::getReportsNumbers(){
	return this->reportsNumbers;
}

/*Tworzy plansze z organizmami*/
void Organisms::createOrganismsBoard(int x, int y){
	organismsBoard = new Board * [y];
	organismsToKill = new Board[x * y];
	/*Inicjalizacja tablicy organizmów do zabica*/
	for (int i = 0; i < x * y; ++i) {
		organismsToKill[i].organism = nullptr;
		organismsToKill[i].isEmpty = true;
	}
	/*Inicjalizacja planszy rozgrywki*/
	for (int i = 0; i < y; ++i) {
		organismsBoard[i] = new Board[x];
	}
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			organismsBoard[i][j].organism = nullptr;
			organismsBoard[i][j].isEmpty= true;
		}
	}
}

Board** Organisms::getOrganismsBoard(){
	return organismsBoard;
}

/*Tworzy organizmy na poczatku symulacji*/
void Organisms::createOrganisms(){
	for (int i = 0; i < organismPopulity; ++i) {
		Coordinates tmpCoordinates = drawCoordinates();
		Organism* tmpOrganism;
		if (tmpCoordinates != Coordinates(-1, -1)) {
			tmpOrganism = createOrganism(i, tmpCoordinates);
			addOrganism(tmpOrganism);
			string report = "Organizm " + tmpOrganism->getName() + " powstal/a na pozycji (" + 
				to_string(tmpOrganism->getCoordinates().GetX()) + ", " + to_string(tmpOrganism->getCoordinates().GetY()) + ")";
			addReport(report);
		}
	}
}

/*Funkcja wspó³dzia³aj¹ca z createOrganisms, tworzy organizmy na poczatku planszy*/
Organism* Organisms::createOrganism(int speciesNumber, Coordinates coordinates){

	if (speciesNumber % SPECIESNUMBER == 0) {
		return new Antelope(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 1) {
		return new Fox(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 2) {
		return new Wolf(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 3) {
		return new Turtle(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 4) {
		return new Sheep(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 5) {
		return new Grass(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 6) {
		return new Dandelion(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 7) {
		return new DeadlyNightshades(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 8) {
		return new Guarana(this, coordinates);
	}
	else if (speciesNumber % SPECIESNUMBER == 9) {
		return new SosnowskyHogweed(this, coordinates);
	}
	else return nullptr;
}

/*Funkcja zwraca organizm o podanych wspó³rzêdnych*/
Organism* Organisms::getOrganism(Coordinates coordinates) {
	for (list<Organism*>::iterator tmpOrganism = listOrganisms.begin(); tmpOrganism != listOrganisms.end(); tmpOrganism++) {
		Organism* tmp = *tmpOrganism;
		if (tmp->getCoordinates() == coordinates && !tmp->getFeatures().toDead) {
			return tmp;
		}
	}
	return nullptr;
}

/*Funkcja dodaje organizm do planszy i do listy*/
void Organisms::addOrganism(Organism* organism){
	if (!listOrganisms.empty()) {
		bool organismIsSet = false;
		for (list<Organism*>::iterator tmpOrganism = listOrganisms.begin(); tmpOrganism != listOrganisms.end(); tmpOrganism++) {
			Organism* tmp = *tmpOrganism;
			Features tmpFeatures = tmp->getFeatures();
			if (organism->getFeatures().initiative > tmpFeatures.initiative) {
				listOrganisms.insert(tmpOrganism, organism);
				organismIsSet = true;
				break;
			}
		}
		if (!organismIsSet) listOrganisms.push_back(organism);
	}
	else listOrganisms.push_front(organism);
	addOrganismToBoard(organism);
}

/*Funkcja dodaje organizm do zabicia na koniec tury w funkcji update*/
void Organisms::addTokillOrganism(Coordinates coordinates){
	Organism* organismToKill = getOrganism(coordinates);
	organismToKill->setExistence();
	organismsToKill[deathsNumbers].isEmpty = false;
	organismsToKill[deathsNumbers].organism = organismToKill;
	++deathsNumbers;
}

/*Funkcja wspó³pracuj¹ca z funkcj¹ update, zabija organizm*/
void Organisms::killOrganism(Coordinates coordinates){
	listOrganisms.erase(getIterator(coordinates));
}

/*Funkcja zwraca iterator listy*/
list<Organism*>::iterator Organisms::getIterator(Coordinates coordinates) {
	list<Organism*>::iterator organismIterator;
	for (list<Organism*>::iterator tmpOrganism = listOrganisms.begin(); tmpOrganism != listOrganisms.end(); tmpOrganism++) {
		Organism* tmp = *tmpOrganism;
		if (tmp->getCoordinates() == coordinates && tmp->getFeatures().toDead && !tmp->getFeatures().isDead) {
			tmp->setIsDead();
			return tmpOrganism;
		}
	}
}

/*Funkcja szuka wolnych koordynatów do rozmna¿ania siê organizmów zwierzêcych*/
Coordinates Organisms::findCoordinates(Coordinates firstParent,Coordinates secondParent){
	Coordinates directions[COORDINATIONSPOSSIBILITY], firstParentArea,secondParentArea, childCoordinates;
	Organism* firstParentOrganism = getOrganism(firstParent);
	Organism* secondParentOrganism = getOrganism(secondParent);

	int directionsPossibilities = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			firstParentArea = firstParent.move(i, j);
			secondParentArea = secondParent.move(i, j);

			if (firstParentOrganism->canMove(firstParentArea) && getOrganism(firstParentArea)==nullptr) {
				directions[directionsPossibilities] = firstParentArea;
				++directionsPossibilities;
			}
			if (secondParentOrganism->canMove(secondParentArea) && getOrganism(secondParentArea) == nullptr) {
				directions[directionsPossibilities] = secondParentArea;
				++directionsPossibilities;
			}
		}
	}
	if (directionsPossibilities) {
		int index = rand() % directionsPossibilities;
		childCoordinates = directions[index];
		return childCoordinates;
	}
	else return Coordinates(-1, -1);
}

/*Funkcja czysci tablice organizmow do zabicia organismsToKill*/
void Organisms::update(){  
	for (int i = 0; i < deathsNumbers; ++i) {
		killOrganism(organismsToKill[i].organism->getCoordinates());
		organismsToKill[i].organism = nullptr;
		organismsToKill[i].isEmpty = true;
	}
	deathsNumbers = 0;
}

/*Funkcja dodaje organizmy do tablicy*/
void Organisms::addOrganismToBoard(Organism* organism){
	organismsBoard[organism->getCoordinates().GetY()][organism->getCoordinates().GetX()].organism = organism;
	organismsBoard[organism->getCoordinates().GetY()][organism->getCoordinates().GetX()].isEmpty = false;
}

/*Funkcja czysci pole z organizmu*/
void Organisms::removeField(Coordinates oldCoordinates){
	organismsBoard[oldCoordinates.GetY()][oldCoordinates.GetX()].isEmpty = true;
	organismsBoard[oldCoordinates.GetY()][oldCoordinates.GetX()].organism = nullptr;
}

int Organisms::getWidth() const {
	return worldWidth;
}

int Organisms::getHeight() const {
	return worldHeight;
}

void Organisms::setWidth(int width) {
	this->worldWidth = width;
}

void Organisms::setHeight(int height) {
	this->worldHeight = height;
}

/*Tworzy organizm o podanym typie*/
Organism* Organisms::createOrganismType(string type, Coordinates coordinates){
	if (type == "Czlowiek") {
		return new Human(this, coordinates);
	}
	else if (type == "Antylopa") {
		return new Antelope(this, coordinates);
	}
	else if (type == "Lis") {
		return new Fox(this, coordinates);
	}
	else if (type == "Wilk") {
		return new Wolf(this, coordinates);
	}
	else if (type == "Zolw") {
		return new Turtle(this, coordinates);
	}
	else if (type == "Owca") {
		return new Sheep(this, coordinates);
	}
	else if (type == "Trawa") {
		return new Grass(this, coordinates);
	}
	else if (type == "Mlecz") {
		return new Dandelion(this, coordinates);
	}
	else if (type == "Wilcze jagody") {
		return new DeadlyNightshades(this, coordinates);
	}
	else if (type == "Guarana") {
		return new Guarana(this, coordinates);
	}
	else if (type == "Barszcz Sosnowskiego") {
		return new SosnowskyHogweed(this, coordinates);
	}
	else return nullptr;
}

/*Losuje wspolrzedne dla organizmow na pocz¹tku rozgrywki*/
Coordinates Organisms::drawCoordinates() {
	for (int i = 0; i < worldHeight; ++i) {
		for (int j = 0; j < worldWidth; ++j) {
			if (organismsBoard[i][j].isEmpty) {
				while (true) {
					int x = rand() % worldWidth;
					int y = rand() % worldHeight;
					if (organismsBoard[y][x].isEmpty) return Coordinates(x, y);
				}
			}
		}
	}
	return Coordinates(-1, -1);
}
