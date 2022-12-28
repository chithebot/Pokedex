#ifndef SFML_GUI_PROJECT_POKEMON_MAP_H
#define SFML_GUI_PROJECT_POKEMON_MAP_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <cassert>
#include "PokemonNotFoundException.h"

class PokemonMap
{
public:
	static const std::string& get(unsigned key) noexcept(false);
private:
	static void find(unsigned key) noexcept(false);
private:
	static std::unordered_map<unsigned, std::string*> pokemons;
};

#endif // SFML_GUI_PROJECT_POKEMON_MAP_H
