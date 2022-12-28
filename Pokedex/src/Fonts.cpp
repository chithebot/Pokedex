#include "Fonts.h"

std::unordered_map<std::string, sf::Font*> Fonts::fonts;

sf::Font& Fonts::get(const std::string& fontPath) noexcept(false)
{
	load(fontPath);
	return *(fonts.at(fontPath));
}

void Fonts::load(const std::string& fontPath) noexcept(false)
{
	// Checking if path actually exists within map
	if (fonts.count(fontPath) == 0)
	{
		sf::Font* f_ptr = new sf::Font();

		// Loading font into a font map
		if (!f_ptr->loadFromFile(fontPath))
		{
			delete f_ptr;
			throw FontNotFoundException("Could not load " + fontPath);
		}
		else
		{
			fonts.insert({ fontPath, f_ptr });
		}
	}
}