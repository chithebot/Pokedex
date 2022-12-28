#include "PokemonMap.h"

std::unordered_map<unsigned, std::string*> PokemonMap::pokemons;

const std::string& PokemonMap::get(unsigned key) noexcept(false)
{
	find(key);
	return *(pokemons.at(key));
}

void PokemonMap::find(unsigned key) noexcept(false)
{
	// Attempts to find a value for key in database if key does not exist in map
	if (pokemons.count(key) == 0)
	{
		std::ifstream inputFile;
		inputFile.open("src/Data/PokemonInformation.txt");
		assert(!inputFile.fail() && "File could not open properly.");

		bool found = false;
		std::string* data = new std::string();
		unsigned i = 0;

		// Looks for data associated to key if it exist in database
		inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// Ignores header line
		while (!inputFile.eof() && i < key)
		{
			std::getline(inputFile, *data);
			++i;
		}

		// Checks that key has been found
		if (i == key)
			found = true;

		// Inserts key-value pair into map if it exist
		if (found)
		{
			pokemons.insert({ key, data });
		}
		// Throws an exception if data does not exist
		else
		{
			delete data;
			throw PokemonNotFoundException();
		}
	}
}
