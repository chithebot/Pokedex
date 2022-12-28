#include "MusicPlaylist.h"
#include "Pokedex.h"

//#ifndef SFML_GUI_PROJECT_
//#define SFML_GUI_PROJECT_

//#endif // SFML_GUI_PROJECT_

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900, 32), "Pokedex");
	sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
	window.setFramerateLimit(60);

	MusicPlaylist playlist("Assets/Music/");
	playlist.pushTrack("AnvilleTown.ogg");
	playlist.pushTrack("CianwoodCity.ogg");
	playlist.pushTrack("FortreeCity.ogg");
	playlist.pushTrack("HumilauCity.ogg");
	playlist.setVolume(10.f);
	playlist.load();
	playlist.play();

	// HEADER ELEMENTS
	sf::Sprite logo(Images::get("Assets/Textures/Images/pokemon_logo.png"));
	sf::RectangleShape headerBackground({ windowSize.x, windowSize.y / 2.5f });
	TextInput searchBar(Fonts::get("Assets/Fonts/Product-Sans-Regular.ttf"),
		Images::get("Assets/Textures/System/text_cursor.png"));
	sf::RectangleShape headerLayer;
	sf::Text instructions("Search for a pokémon by its name or national Pokédex number!",
		Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 32);
	DropdownMenu filter;
	initializeHeader(window, logo, headerBackground, headerLayer, searchBar, instructions, filter);

	// MAIN ELEMENTS
	PokemonEntryList entryList({ windowSize.x * 0.75f, windowSize.y});
	ScrollableCustomSprite mainBackground1(Images::get("Assets/Textures/Images/pokeball_background.jpg"));
	sf::RectangleShape mainBackground2;
	initializeMain(window, mainBackground1, mainBackground2, entryList, headerBackground);

	// SCREEN SCROLLING
	sf::View view;
	view.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
	float scrolled = 0.f;
	float scrollInitialLimit = 0.f;
	float scrollSpeed = 75.f;
	mainBackground1.setScrollSpeed(scrollSpeed);

	// Handles window being opened
	while (window.isOpen())
	{
		// Handles event polling
		sf::Event event;

		while (window.pollEvent(event))
		{
			// Handles closing window event
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			// Handles scrolling events
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				float offset = -1 * event.mouseWheelScroll.delta;
				view.move(0.f, offset * scrollSpeed);
				scrolled = scrolled + offset;

				// Handles off-screen scrolling
				if ((view.getCenter().y - view.getSize().y / 2.f) < scrollInitialLimit)
				{
					view.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
					scrolled = scrollInitialLimit;
				}
			}
			entryList.eventHandler(window, event);
			searchBar.eventHandler(window, event);
			filter.eventHandler(window, event);
			mainBackground1.eventHandler(window, event);
			playlist.eventHandler(window, event);
		}
		pollFilterButtons(filter, entryList);
		entryList.onClickDetailPanel();
		entryList.search(searchBar.getInput());
		entryList.update();
		searchBar.update();
		filter.update();
		window.setView(view);
		window.clear(sf::Color::Black);
		drawMainElements(window, mainBackground1, mainBackground2, entryList);
		drawHeaderElements(window, logo, headerBackground, headerLayer, searchBar, instructions, filter);
		window.display();
	}
}
