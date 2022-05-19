#include <iostream>
#include "Button.h"
#include "Initializer.h"
#include <conio.h>
#include <ctime>

using namespace std;
int main() {
	srand(time(NULL));
	World world;
	Initializer universe(&world);
	universe.initializer();

	int sign = 0,move = 0;
	while (sign != KEY_ESC) {
		sign = _getch();
		move = _getch();
		if (sign == KEY_s) world.saveWorld();
		else {
			world.takeTurn(move);
		}
	}
	return 0;
}