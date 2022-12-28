#include "PokemonEntryComparison.h"

bool PokemonEntryLexographicA::operator()(PokemonEntry* left, PokemonEntry* right) const
{
	return (left->getName().toAnsiString()) > (right->getName().toAnsiString());
}

bool PokemonEntryLexographicD::operator()(PokemonEntry* left, PokemonEntry* right) const
{
	return (left->getName().toAnsiString()) < (right->getName().toAnsiString());
}

bool PokemonEntryNumericA::operator()(PokemonEntry* left, PokemonEntry* right) const
{
	return std::stoi(left->getNumber().toAnsiString()) > std::stoi(right->getNumber().toAnsiString());
}

bool PokemonEntryNumericD::operator()(PokemonEntry* left, PokemonEntry* right) const
{
	return std::stoi(left->getNumber().toAnsiString()) < std::stoi(right->getNumber().toAnsiString());
}