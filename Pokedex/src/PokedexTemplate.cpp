#ifndef SFML_GUI_PROJECT_POKEDEX_TEMPLATE_CPP
#define SFML_GUI_PROJECT_POKEDEX_TEMPLATE_CPP

#include "Pokedex.h"

template <typename LIST_TYPE>
void pollFilterButtons(DropdownMenu& filter, LIST_TYPE& list)
{
	filter.getButton(0).onClick(&LIST_TYPE::setSortState, &LIST_TYPE::setSortDirection, NUMERIC, ASCENDING, list);
	filter.getButton(1).onClick(&LIST_TYPE::setSortState, &LIST_TYPE::setSortDirection, NUMERIC, DESCENDING, list);
	filter.getButton(2).onClick(&LIST_TYPE::setSortState, &LIST_TYPE::setSortDirection, LEXOGRAPHIC, ASCENDING, list);
	filter.getButton(3).onClick(&LIST_TYPE::setSortState, &LIST_TYPE::setSortDirection, LEXOGRAPHIC, DESCENDING, list);
}

#endif // SFML_GUI_PROJECT_POKEDEX_TEMPLATE_CPP
