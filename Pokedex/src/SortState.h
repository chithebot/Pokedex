#ifndef SFML_GUI_PROJECT_SORT_STATE_H
#define SFML_GUI_PROJECT_SORT_STATE_H

#include <cassert>
#include "SortStateEnum.h"

class SortState
{
public:
	SortState();
	SortStateEnum getSortState() const;
	SortStateEnum getSortDirection() const;
	void setSortState(SortStateEnum type);
	void setSortDirection(SortStateEnum direction);
private:
	SortStateEnum sortState;
	SortStateEnum sortDirection;
};

#endif // SFML_GUI_PROJECT_SORT_STATE_H
