#ifndef SFML_GUI_PROJECT_POKEDEX_H
#define SFML_GUI_PROJECT_POKEDEX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "PokemonMap.h"
#include "TextInput.h"
#include "DropdownMenu.h"
#include "PokemonEntryList.h"
#include "ScrollableCustomSprite.h"

void initializeHeader(sf::RenderWindow& window, sf::Sprite& logo,
	sf::RectangleShape& headerBackground, sf::RectangleShape& headerLayer,
	TextInput& searchBar, sf::Text& instructions, DropdownMenu& filter);

void initializeMain(sf::RenderWindow& window, ScrollableCustomSprite& mainBackground1,
	sf::RectangleShape& mainBackground2, PokemonEntryList& entryList, 
	sf::RectangleShape& headerBackground);

void drawHeaderElements(sf::RenderWindow& window, sf::Sprite& logo,
	sf::RectangleShape& headerBackground, sf::RectangleShape& headerLayer,
	TextInput& searchBar, sf::Text& instructions, DropdownMenu& filter);

void drawMainElements(sf::RenderWindow& window, ScrollableCustomSprite& mainBackground1,
	sf::RectangleShape& mainBackground2, PokemonEntryList& entryList);

template <typename LIST_TYPE>
void pollFilterButtons(DropdownMenu& filter, LIST_TYPE& list);

#include "PokedexTemplate.cpp"

#endif // SFML_GUI_PROJECT_POKEDEX_H
