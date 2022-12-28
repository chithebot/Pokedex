#ifndef SFML_GUI_PROJECT_STATES_H
#define SFML_GUI_PROJECT_STATES_H

#include <map>
#include "StateEnum.h"

class States
{
private:
	std::map<StateEnum, bool> states;
public:
	States();
	bool checkState(StateEnum state) const;
	void toggleState(StateEnum state);
	void enableState(StateEnum state);
	void disableState(StateEnum state);
};

#endif // SFML_GUI_PROJECT_STATES_H
