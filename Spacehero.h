#ifndef SPACEHERO_H
#define SPACEHERO_H

#include "SpaceDisplay.h"
#include "Universe.h"

class Spacehero
{
  // Zustaende des Spielautomaten
  //
  // Endzustaende: next und exit
	enum SpaceheroState { 
		spacehero_edit, 
		spacehero_simulate, 
		spacehero_next, 
		spacehero_exit 
	} state;

	bool won;

	SpaceDisplay &display;
	Universe &universe;

public:

	Spacehero(SpaceDisplay &d, Universe &u);

	bool play();

	SpaceheroState edit();
	SpaceheroState simulate();
	SpaceheroState handleEvents();


};
#endif
