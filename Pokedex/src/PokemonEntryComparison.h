#ifndef SFML_GUI_PROJECT_POKEMON_ENTRY_COMPARISON_H
#define SFML_GUI_PROJECT_POKEMON_ENTRY_COMPARISON_H

#include <algorithm>
#include "PokemonEntry.h"

struct PokemonEntryLexographicA
{
	bool operator()(PokemonEntry* left, PokemonEntry* right) const;
};

struct PokemonEntryLexographicD
{
	bool operator()(PokemonEntry* left, PokemonEntry* right) const;
};

struct PokemonEntryNumericA
{
	bool operator()(PokemonEntry* left, PokemonEntry* right) const;
};

struct PokemonEntryNumericD
{
	bool operator()(PokemonEntry* left, PokemonEntry* right) const;
};

#endif // SFML_GUI_PROJECT_POKEMON_ENTRY_COMPARISON_H
