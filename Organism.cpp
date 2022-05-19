#include "Organism.h"
#include <Windows.h>
#include "Colors.h"
#include <iostream>

//odpowiada za kolor
HANDLE static color = GetStdHandle(STD_OUTPUT_HANDLE);

Organism::Organism(){}

void Organism::action(int move){}

/*Metoda rysujaca znak danego organizmu*/
void Organism::draw(){
	switch (features.sign) {
	case 'H': 
		SetConsoleTextAttribute(color, WHITE);		//HUMAN
		break;
	case 'A':
		SetConsoleTextAttribute(color, BROWN);		//ANTELOPE
		break;
	case 'F':
		SetConsoleTextAttribute(color, RED);		//FOX
		break;
	case 'W':
		SetConsoleTextAttribute(color, DARKGRAY);	//WOLF
		break;
	case '*':
		SetConsoleTextAttribute(color, LIGHTBLUE);	//DANDELION
		break;
	case '+':
		SetConsoleTextAttribute(color, MAGENTA);    //DEADLYNIGHTSHADES
		break;
	case ',':
		SetConsoleTextAttribute(color, LIGHTGREEN);	//GRASS
		break;
	case '@':	
		SetConsoleTextAttribute(color, LIGHTRED);	//GUARANA
		break;
	case 'S':
		SetConsoleTextAttribute(color, LIGHTGRAY);	//SHEEP
		break;
	case '#':
		SetConsoleTextAttribute(color, BLUE);		//SOSNOWSKY HOGWEED
		break;
	case 'T':                                      //TURTLE
		SetConsoleTextAttribute(color, CYAN);
		break;
	}
	std::putchar(features.sign);
	SetConsoleTextAttribute(color, WHITE);
}

void Organism::defensive(Organism* enemy){}

Features Organism::getFeatures() const {
	return this->features;
}

Coordinates Organism::getCoordinates() const {
	return this->coordinates;
}

void Organism::getOlder(){
	features.age++;
}

void Organism::increaseStrength(int number){
	features.strength += number;
}

/*Metoda ustawiajaca istnienie organizmu na martwy*/
void Organism::setExistence(){
	this->features.toDead = true;
}

/*Metoda ustawia organizm do smierci*/
void Organism::setIsDead(){
	features.isDead = true;
}

/*metoda wykonujaca ruch organizmu*/
void Organism::takeMove(Coordinates newCoordinates){
	if (canMove(newCoordinates)) {
		world->removeField(this->coordinates);
		this->coordinates = newCoordinates;
		world->addOrganismToBoard(this);
	}
}

Organisms* Organism::getWorld(){
	return this->world;
}

/*Metoda sprawdzajaca czy dany ruch jest mozliwy do wykonania (organizm nie wychodzi za plansze)*/
bool Organism::canMove(Coordinates coordinates){
	if (coordinates.GetX() < 0 || coordinates.GetX() > world->getWidth() - 1
		|| coordinates.GetY() < 0 || coordinates.GetY() > world->getHeight() - 1) return false;
	else return true;
}

int Organism::getAge() const{
	return this->features.age;
}

void Organism::setAge(int age){
	this->features.age = age;
}

int Organism::getStrength() const{
	return this->features.strength;
}

void Organism::setStrength(int strength){
	this->features.strength = strength;
}

string Organism::getName() const{
	return this->features.name;
}
