#include "States.h"

States::States()
{
	// Inserting state-boolean key-value pair
	for (unsigned i = 0; i < NUM_STATES; ++i)
		states.insert({ static_cast<StateEnum>(i), false });
}

bool States::checkState(StateEnum state) const { return states.at(state); }

void States::toggleState(StateEnum state) { states.at(state) = !states.at(state); }

void States::enableState(StateEnum state) { states.at(state) = true; }

void States::disableState(StateEnum state) { states.at(state) = false; }
