#include "SortState.h"

SortState::SortState() : sortState(LEXOGRAPHIC), sortDirection(ASCENDING) { }

SortStateEnum SortState::getSortState() const { return sortState; }

SortStateEnum SortState::getSortDirection() const { return sortDirection; }

void SortState::setSortState(SortStateEnum state) { sortState = state; }

void SortState::setSortDirection(SortStateEnum direction)
{
	assert(direction == ASCENDING || direction == DESCENDING && "Invalid sort direction.");
	sortDirection = direction;
}
