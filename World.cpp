#include "World.h"
#include <Windows.h>
#include <conio.h>
#include "Colors.h"
#include <fstream>
#include "Human.h"
#define BORDEREPORTWIDTH 40

HANDLE static color = GetStdHandle(STD_OUTPUT_HANDLE);

World::World() {
	this->width = 0;
	this->height = 0;
	turnNumber = 0;
}

World::World(int width, int height){
	this->width = width;
	this->height = height;
	turnNumber = 0;
}

void World::setTurnNumber(int turnNumber){
	this->turnNumber = turnNumber;
}

void World::setOrganisms(Organisms* organisms){
	this->organisms = *organisms;
}

int World::getWidth() const {
	return this->width;
}

int World::getHeight() const {
	return this->height;
}

void World::setWidth(int width){
	this->width = width;
}

void World::setHeight(int height){
	this->height = height;
}

/*Metoda odpowiedzialna za wykonanie tury*/
void World::takeTurn(int btn) {
	list<Organism*> tmpListOrganisms = *getOrganisms()->getList();
	for (list<Organism*>::iterator tmpOrganism = tmpListOrganisms.begin(); tmpOrganism != tmpListOrganisms.end(); tmpOrganism++) {
		Organism* tmp = *tmpOrganism;
		Features features = tmp->getFeatures();
		if (!features.toDead) {
			tmp->getOlder();
			if (features.sign == 'H') {
				tmp->action(btn);
			}
			else tmp->action();
		}
	}
	organisms.update();

	system("cls");
	drawWorld();
}

/*Metoda odpowiedzialna za rysowanie œwiata*/
void World::drawWorld() {
	turnNumber++;
	Board** tmpOrganismsBoard = this->getOrganisms()->getOrganismsBoard();
	/*Autor*/
	SetConsoleTextAttribute(color, LIGHTGREEN);
	cout << "========Autor==========\n";
	cout << "Krystian Jandy s184589\n";
	cout << "=======================\n";
	SetConsoleTextAttribute(color, MAGENTA);
	cout << "Sterowanie: \n";
	cout << "Esc - wyjscie\nstrzalki - sterowanie czlowiekiem\nSpace - aktywowanie umiejetnosci specjalnej\ns - zapis do pliku\n";
	SetConsoleTextAttribute(color, YELLOW);
	cout << "Numer tury: " << turnNumber << endl;
	cout << "Libcza zywych organizmow: " << organisms.getList()->size() << endl;
	/*Rysowanie œwiata - mapy*/
	//granica górna
	SetConsoleTextAttribute(color, LIGHTRED);
	for (int i = 0; i < BORDER_WIDTH; ++i) {
		for (int j = 0; j < 2*this->width + 2 * BORDER_WIDTH; ++j) {
			cout << "=";
		}
		cout << endl;
	}
	for (int i = 0; i < this->height; ++i) {
		//lewa granica
		for (int j = 0; j < BORDER_WIDTH; ++j) {
			putchar('|');
			if (j != BORDER_WIDTH - 1) putchar(' ');
		}
		//plansza z organizmami
		for (int j = 0; j < this->width; ++j) {
			cout << " ";
			if (tmpOrganismsBoard[i][j].isEmpty) putchar('-');
			else {
				tmpOrganismsBoard[i][j].organism->draw();
				SetConsoleTextAttribute(color, LIGHTRED);
			}
		}
		//prawa granica
		for (int j = 0; j < BORDER_WIDTH; ++j) {
			putchar('|');
			if (j != BORDER_WIDTH - 1) putchar(' ');
		}
		cout << endl;
	}
	//granica dolna
	for (int i = 0; i < BORDER_WIDTH; ++i) {
		for (int j = 0; j < 2 * this->width + 2 * BORDER_WIDTH; ++j) {
			cout << "=";
		}
		cout << endl;
	}
	string* reports = this->getOrganisms()->getReports();
	
	//Górna krawêdŸ
	SetConsoleTextAttribute(color, BLUE);
	for (int i = 0; i < BORDEREPORTWIDTH; ++i) {
		cout << "==";
	}
	cout << endl;
	
	//Raport
	SetConsoleTextAttribute(color, YELLOW);
	cout << "Raport: \n";
	SetConsoleTextAttribute(color, WHITE);
	if (organisms.getReportsNumbers() != 0) {
		for (int i = 0; i < organisms.getReportsNumbers(); ++i) {
			cout << to_string(i + 1) + ") " + reports[i] << endl;
		}
	}
	else {
		SetConsoleTextAttribute(color, LIGHTRED);
		cout << "Aktualnie brak jakiejkolwiek aktywnosci" << endl;
	}
	//Dolna krawêdŸ
	SetConsoleTextAttribute(color, BLUE);
	for (int i = 0; i < BORDEREPORTWIDTH; ++i) {
		cout << "==";
	}
	cout << endl;
	organisms.setReportsNumbers(0);

	SetConsoleTextAttribute(color, WHITE);
}

Organisms* World::getOrganisms(){
	return &organisms;
}

/*Metoda zapisuj¹ca œwiat*/
void World::saveWorld() {
	fstream file;
	string fileName, organismType;
	cout << "Podaj nazwe pliku\n";
	cin >> fileName;
	fileName += ".txt";
	file.open(fileName, fstream::app);
	if (!file.is_open()) cout << "Nie mozna utworzyc pliku\n";
	else {
		list<Organism*>* listOrganisms = getOrganisms()->getList();
		file << getWidth();
		file << " ";
		file << getHeight();
		file << "\n";
		for (list<Organism*>::iterator tmpOrganism = (*listOrganisms).begin(); tmpOrganism != (*listOrganisms).end(); tmpOrganism++) {
			Organism* tmp = *tmpOrganism;
			file << tmp->getName();
			file << " ";
			file << tmp->getCoordinates().GetX();
			file << " ";
			file << tmp->getCoordinates().GetY();
			file << " ";
			file << tmp->getStrength();
			file << " ";
			file << tmp->getAge();
			if (tmp->getName() == "Czlowiek") {
				file << " ";
				Human* human = (Human*)tmp;
				file << human->getTurnsToBoost();
				file << " ";
				file << human->getBoostTurns();
			}
			file << "\n";
		}
		file.close();
		cout << "Symulacja zostala zapisana pomyslnie!\n";
	}
}

/*Metoda inicjalizuj¹ca zapisany œwiat*/
void World::initiateWorld(Organisms* organisms){
	fstream file;
	string fileName, organismType,tmpString;
	cout << "Podaj nazwe pliku\n";
	cin >> fileName;
	fileName += ".txt";
	file.open(fileName);
	if (!file.is_open()) {
		cout << "Nie mozna otworzyc pliku! Podany plik nie istnieje\n";
	}
	else {
		string organismType;
		file >> this->width; 
		file >> this->height;
		organisms->setWidth(this->width); organisms->setHeight(this->height);
		Organism* tmpOrganism = nullptr;
		organisms->createOrganismsBoard(width, height);
		while (!file.eof()) {
			int x, y, strength, age,tmp;
			file >> organismType;
			if (organismType == "Wilcze" || organismType == "Barszcz") {
				file >> tmpString;
				organismType = organismType + " " + tmpString;
			}
			file >> x;
			file >> y;
			file >> strength;
			file >> age;
			
			tmpOrganism = organisms->createOrganismType(organismType, Coordinates(x, y));
			tmpOrganism->setStrength(strength);
			tmpOrganism->setAge(age);
			organisms->addOrganism(tmpOrganism);
			
			if (organismType == "Czlowiek") {
				Human* human = (Human*)tmpOrganism;
				file >> tmp;
				human->setTurnsToBoost(tmp);
				file >> tmp;
				human->setBoostTurns(tmp);
				if (human->getBoostTurns()) {
					human->setBoostIsActive(true);
					human->setBoostIsAvaliable(false);
				}
			}
		}
		file.close();
	}
}