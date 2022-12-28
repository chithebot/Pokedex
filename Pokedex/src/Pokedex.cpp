#include "Pokedex.h"

void initializeHeader(sf::RenderWindow& window, sf::Sprite& logo,
	sf::RectangleShape& headerBackground, sf::RectangleShape& headerLayer,
	TextInput& searchBar, sf::Text& instructions, DropdownMenu& filter)
{
	sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

	// Setting up logo
	logo.setScale({ 0.5, 0.5 });

	// Setting up header background
	headerBackground.setFillColor(sf::Color(50, 50, 50));
	headerBackground.setPosition({ 0.f, 0.f });
	headerBackground.setOutlineThickness(3.f);
	headerBackground.setOutlineColor(sf::Color::Black);
	Position::upperLeft(headerBackground, logo, 25.f);
	Position::centerX(headerBackground, logo);

	// Setting up search bar
	searchBar.setCharacterSize(36);
	searchBar.setLabelFont(Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"));
	searchBar.setLabel("Search");
	searchBar.setLabelColor(sf::Color::White);
	searchBar.setLabelCharacterSize(30);
	Position::bottomLeft(headerBackground, searchBar, headerBackground.getSize().y / 3.5f);
	Position::centerX(logo, searchBar);
	
	// Setting up header layer
	headerLayer.setSize({ windowSize.x, searchBar.getGlobalBounds().top + searchBar.getGlobalBounds().height - logo.getGlobalBounds().top + 25.f });
	headerLayer.setFillColor(sf::Color(25, 25, 25));
	headerLayer.setOutlineThickness(1.f);
	headerLayer.setOutlineColor(sf::Color::Black);
	headerLayer.setPosition({ 0.f, 0.f });
	Position::upperLeft(headerBackground, headerLayer, 12.5f);
	Position::centerX(headerBackground, headerLayer);

	// Setting up instructions
	instructions.setFillColor(sf::Color::White);
	instructions.setOutlineColor(sf::Color::Black);
	instructions.setOutlineThickness(2.f);
	Position::down(searchBar, instructions, 35.f);
	Position::centerX(searchBar, instructions);

	// Setting up filter
	filter.addMenuItem("Lowest number (first)");
	filter.addMenuItem("Highest number (first)");
	filter.addMenuItem("A-Z");
	filter.addMenuItem("Z-A");
	filter.setCurrentItemText("Select a filter");
	filter.setCurrentItemTextSize(18);
	filter.setCurrentItemSize({ 225.f, 50.f });
	filter.setCurrentItemFillColor(sf::Color::White);
	filter.setCurrentItemHoverColor(sf::Color::White);
	filter.setCurrentItemTextColor(sf::Color(25, 25, 25));
	filter.setButtonSize({ 225.f, 50.f });
	filter.setButtonTextSize(14);
	filter.setButtonFillColor(sf::Color::White);
	filter.setButtonHoverColor(sf::Color(25, 25, 25));
	filter.setButtonTextColor(sf::Color(100, 100, 100));
	Position::bottomRight(headerBackground, filter, 30.f);
}

void initializeMain(sf::RenderWindow& window, ScrollableCustomSprite& mainBackground1,
	sf::RectangleShape& mainBackground2, PokemonEntryList& entryList, sf::RectangleShape& headerBackground)
{
	sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

	// Setting up pokemon entry list
	entryList.addEntriesFromFile("src/Data/PokemonInformation.txt",
		"Assets/Textures/Images/Pokemon/");
	entryList.setNumEntriesPerRow(4);
	entryList.setHorizonalPadding(50);
	entryList.setVerticalPadding(50);
	entryList.setCharacterSize(24);
	entryList.setEntryHeight(300);
	
	// Setting up main background 1
	mainBackground1.setSize({ windowSize.x, windowSize.y });
	mainBackground1.setPosition({ 0.f, 0.f });

	// Setting up main background 2 and resizing entry list
	mainBackground2.setSize({ mainBackground1.getSize().x * 0.75f, mainBackground1.getSize().y });
	mainBackground2.setFillColor(sf::Color(50, 50, 50, 99));
	mainBackground2.setOutlineColor(sf::Color(25, 25, 25));
	mainBackground2.setOutlineThickness(3.f);
	Position::down(headerBackground, mainBackground2);
	Position::centerX(headerBackground, mainBackground2);
	entryList.setSize(mainBackground2.getSize());
	entryList.setPosition(mainBackground2.getPosition());
	mainBackground2.setSize(entryList.getSize());
}

void drawHeaderElements(sf::RenderWindow& window, sf::Sprite& logo,
	sf::RectangleShape& headerBackground, sf::RectangleShape& headerLayer,
	TextInput& searchBar, sf::Text& instructions, DropdownMenu& filter)
{
	window.draw(headerBackground);
	window.draw(headerLayer);
	window.draw(logo);
	window.draw(searchBar);
	window.draw(instructions);
	window.draw(filter);
}

void drawMainElements(sf::RenderWindow& window, ScrollableCustomSprite& mainBackground1,
	sf::RectangleShape& mainBackground2, PokemonEntryList& entryList)
{
	window.draw(mainBackground1);
	window.draw(mainBackground2);
	window.draw(entryList);
}
