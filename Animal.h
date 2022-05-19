#pragma once
#include "Organism.h"

	class Animal : public Organism {
	protected:
		virtual void action();
		virtual void collision(Organism* adjacentOrganism);
		virtual void breeding(Organism* adjacentOrganism);
	};
