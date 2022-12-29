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
#include "MusicPlaylist.h"

class Pokedex
{
public:
	Pokedex();
	Pokedex(const sf::Vector2u& videoSize);
	~Pokedex();
	void run();
private:
	void initializePlaylist();
	void initializeHeaderElements();
	void initializeMainElements();
	void drawMembers();
	void scrollEvent(sf::View& view, float initialScrollBound, sf::Event event);
	void pollFilterButtons();
private:
	// ESSENTIAL MEMBERS
	sf::RenderWindow* window;
	MusicPlaylist* playlist;
	float scrollSpeed;

	// HEADER ELEMENTS
	sf::Sprite* logo;
	sf::RectangleShape* headerBackground;
	sf::RectangleShape* headerLayer;
	TextInput* searchBar;
	sf::Text* instructions;
	DropdownMenu* filter;

	// MAIN ELEMENTS
	PokemonEntryList* entryList;
	ScrollableCustomSprite* mainBackground;
	sf::RectangleShape* mainLayer;
};

#endif // SFML_GUI_PROJECT_POKEDEX_H
