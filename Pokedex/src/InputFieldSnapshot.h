#ifndef SFML_GUI_PROJECT_TEXT_SNAPSHOT_H
#define SFML_GUI_PROJECT_TEXT_SNAPSHOT_H

#include "Snapshot.h"

struct InputFieldSnapshot : public Snapshot
{
	sf::String input;
	sf::String viewed;
};

#endif // SFML_GUI_PROJECT_SNAPSHOT_H
