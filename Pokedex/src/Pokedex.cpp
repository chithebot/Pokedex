#include "Pokedex.h"

Pokedex::Pokedex() : Pokedex({1600, 900}) { }

Pokedex::Pokedex(const sf::Vector2u& size)
	: window(new sf::RenderWindow(sf::VideoMode(size.x, size.y, sf::VideoMode::getDesktopMode().bitsPerPixel), "Pokédex")),
	playlist(new MusicPlaylist()), scrollSpeed(75.f), logo(new sf::Sprite()), headerBackground(new sf::RectangleShape()),
	headerLayer(new sf::RectangleShape()), searchBar(new TextInput()), instructions(new sf::Text()), filter(new DropdownMenu()),
	entryList(new PokemonEntryList()), mainBackground(new ScrollableCustomSprite(Images::get("Assets/Textures/Images/pokeball_background.jpg"))),
	mainLayer(new sf::RectangleShape())
{
	window->setFramerateLimit(60);
	initializePlaylist();
	initializeHeaderElements();
	initializeMainElements();
}

Pokedex::~Pokedex()
{
	// Deleting essential members
	delete window;
	delete playlist;

	// Deleting header elements
	delete logo;
	delete headerBackground;
	delete headerLayer;
	delete searchBar;
	delete instructions;
	delete filter;

	// Deleting main elements
	delete entryList;
	delete mainBackground;
	delete mainLayer;
}

void Pokedex::run()
{
	sf::Vector2f winSize = (sf::Vector2f)window->getSize();

	// MUSIC PLAYLIST
	playlist->play();

	// SCREEN SCROLLING
	sf::View view;
	view.reset(sf::FloatRect(0, 0, winSize.x, winSize.y));

	// Handles window being opened
	while (window->isOpen())
	{
		// Handles event polling
		sf::Event event;

		while (window->pollEvent(event))
		{
			// Handles closing window event
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			scrollEvent(view, 0.f, event);
			entryList->eventHandler(*window, event);
			searchBar->eventHandler(*window, event);
			filter->eventHandler(*window, event);
			mainBackground->eventHandler(*window, event);
			playlist->eventHandler(*window, event);
		}
		pollFilterButtons();
		entryList->onClickDetailPanel();
		entryList->search(searchBar->getInput());
		entryList->update();
		searchBar->update();
		filter->update();
		window->setView(view);
		window->clear(sf::Color::Black);
		drawMembers();
		window->display();
	}
}

void Pokedex::initializePlaylist()
{
	playlist->setMusicFolderPath("Assets/Music/");
	playlist->pushTrack("AnvilleTown.ogg");
	playlist->pushTrack("CianwoodCity.ogg");
	playlist->pushTrack("FortreeCity.ogg");
	playlist->pushTrack("HumilauCity.ogg");
	playlist->setVolume(15.f);
	playlist->load();
}

void Pokedex::initializeHeaderElements()
{
	sf::Vector2f winSize = (sf::Vector2f)window->getSize();

	// Setting up logo
	logo->setTexture(Images::get("Assets/Textures/Images/pokemon_logo.png"));
	float logoTargetHeight = 0.163f * winSize.y;
	float logoScale = logoTargetHeight / logo->getGlobalBounds().height;
	logo->scale(logoScale, logoScale);

	// Setting up header background
	headerBackground->setSize({ winSize.x, winSize.y * 0.4f });
	headerBackground->setFillColor(sf::Color(50, 50, 50));
	headerBackground->setPosition({ 0.f, 0.f });
	headerBackground->setOutlineThickness(3.f);
	headerBackground->setOutlineColor(sf::Color::Black);
	Position::upperLeft(*headerBackground, *logo, winSize.y * 0.028f);
	Position::centerX(*headerBackground, *logo);
	
	// Setting up search bar
	searchBar->setCharacterFont(Fonts::get("Assets/Fonts/Product-Sans-Regular.ttf"));
	searchBar->setLabelFont(Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"));
	searchBar->setLength(10);
	searchBar->setCharacterColor(sf::Color::Black);
	searchBar->setCharacterSize(36);
	searchBar->setLabel("Search");
	searchBar->setLabelColor(sf::Color::White);
	searchBar->setLabelCharacterSize(30);
	Position::bottomLeft(*headerBackground, *searchBar, headerBackground->getSize().y * 0.286f);
	Position::centerX(*logo, *searchBar);

	// Setting up header layer
	headerLayer->setSize({ winSize.x, searchBar->getGlobalBounds().top + searchBar->getGlobalBounds().height - logo->getGlobalBounds().top + winSize.y * 0.028f });
	headerLayer->setFillColor(sf::Color(25, 25, 25));
	headerLayer->setOutlineThickness(1.f);
	headerLayer->setOutlineColor(sf::Color::Black);
	headerLayer->setPosition({ 0.f, 0.f });
	Position::upperLeft(*headerBackground, *headerLayer, winSize.y * 0.014f);
	Position::centerX(*headerBackground, *headerLayer);

	// Setting up instructions
	instructions->setString("Search for a pokémon by its name or national Pokédex number!");
	instructions->setFont(Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"));
	instructions->setCharacterSize(32);
	instructions->setFillColor(sf::Color::White);
	instructions->setOutlineColor(sf::Color::Black);
	instructions->setOutlineThickness(2.f);
	Position::down(*searchBar, *instructions, winSize.y * 0.039f);
	Position::centerX(*searchBar, *instructions);

	// Setting up filter
	filter->addMenuItem("Lowest number (first)");
	filter->addMenuItem("Highest number (first)");
	filter->addMenuItem("A-Z");
	filter->addMenuItem("Z-A");
	filter->setCurrentItemText("Select a filter");
	filter->setCurrentItemTextSize(18);
	filter->setCurrentItemSize({ 225.f, 50.f });
	filter->setCurrentItemFillColor(sf::Color::White);
	filter->setCurrentItemHoverColor(sf::Color::White);
	filter->setCurrentItemTextColor(sf::Color(25, 25, 25));
	filter->setButtonSize({ 225.f, 50.f });
	filter->setButtonTextSize(14);
	filter->setButtonFillColor(sf::Color::White);
	filter->setButtonHoverColor(sf::Color(25, 25, 25));
	filter->setButtonTextColor(sf::Color(100, 100, 100));
	Position::bottomRight(*headerBackground, *filter, 30.f);
}

void Pokedex::initializeMainElements()
{
	sf::Vector2f winSize = (sf::Vector2f)window->getSize();

	// Setting up pokemon entry list
	entryList->setNumEntriesPerRow(4);
	entryList->setSize({ winSize.x * 0.75f, winSize.y });
	entryList->setHorizonalPadding(winSize.x * 0.0078f);
	entryList->setVerticalPadding(winSize.y * 0.028f);
	entryList->addEntriesFromFile("src/Data/PokemonInformation.txt", "Assets/Textures/Images/Pokemon/");
	entryList->setCharacterSize(24);
	entryList->setEntryHeight(300);

	// Setting up main background
	/*mainBackground->setTexture(Images::get("Assets/Textures/Images/pokeball_background.jpg"));*/
	mainBackground->setScrollSpeed(scrollSpeed);
	mainBackground->setSize({ winSize.x, winSize.y });
	mainBackground->setPosition({ 0.f, 0.f });

	// Setting up main layer
	mainLayer->setSize(entryList->getSize());
	mainLayer->setFillColor(sf::Color(50, 50, 50, 99));
	mainLayer->setOutlineColor(sf::Color(25, 25, 25));
	mainLayer->setOutlineThickness(3.f);
	Position::down(*headerBackground, *mainLayer);
	Position::centerX(*headerBackground, *mainLayer);
	entryList->setPosition(mainLayer->getPosition());
	mainLayer->setSize(entryList->getSize());
}

void Pokedex::drawMembers()
{
	window->draw(*mainBackground);
	window->draw(*mainLayer);
	window->draw(*entryList);
	window->draw(*headerBackground);
	window->draw(*headerLayer);
	window->draw(*logo);
	window->draw(*searchBar);
	window->draw(*instructions);
	window->draw(*filter);
}

void Pokedex::scrollEvent(sf::View& view, float initialScrollBound, sf::Event event)
{
	sf::Vector2f winSize = (sf::Vector2f)window->getSize();

	// Handles scrolling events
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		float offset = -1 * event.mouseWheelScroll.delta;
		view.move(0.f, offset * scrollSpeed);

		// Handles off-screen scrolling
		if ((view.getCenter().y - view.getSize().y / 2.f) < initialScrollBound)
			view.reset(sf::FloatRect(0, 0, winSize.x, winSize.y));
	}
}

void Pokedex::pollFilterButtons()
{
	filter->getButton(0).onClick(&PokemonEntryList::setSortState, &PokemonEntryList::setSortDirection,
		NUMERIC, ASCENDING, *entryList);
	filter->getButton(1).onClick(&PokemonEntryList::setSortState, &PokemonEntryList::setSortDirection,
		NUMERIC, DESCENDING, *entryList);
	filter->getButton(2).onClick(&PokemonEntryList::setSortState, &PokemonEntryList::setSortDirection,
		LEXOGRAPHIC, ASCENDING, *entryList);
	filter->getButton(3).onClick(&PokemonEntryList::setSortState, &PokemonEntryList::setSortDirection,
		LEXOGRAPHIC, DESCENDING, *entryList);
}
