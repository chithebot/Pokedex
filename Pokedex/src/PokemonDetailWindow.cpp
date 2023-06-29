#include "PokemonDetailWindow.h"

std::string PokemonDetailWindow::name;

std::string PokemonDetailWindow::number;

std::vector<std::string> PokemonDetailWindow::types;

std::vector<std::string> PokemonDetailWindow::weaknesses;

std::string PokemonDetailWindow::weight;

std::string PokemonDetailWindow::height;

float PokemonDetailWindow::padding = 25.f;

float PokemonDetailWindow::getPadding() { return padding; }

void PokemonDetailWindow::setPadding(float p) { padding = p; }

void PokemonDetailWindow::runDetailWindow(const std::string& data)
{
	// Getting data of pokemon
	extractData(data);

	// Setting up details window for the respective pokemon
	sf::RenderWindow window(sf::VideoMode(1300, 900, 32), name);
	sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

	// Setting up background elements
	CustomSprite background(Images::get("Assets/Textures/Images/detailed_window_bg.png"));
	sf::RectangleShape filter;
	initializeBackground(background, filter, window);
	sf::RectangleShape filter2(filter);

	// Setting up container
	Container left({ windowSize.x / 2.f - padding * 2, windowSize.y - padding * 2 });
	Container right(left);
	initializeContainer(background, left, right);

	// Setting up left container elements (name, number, image panel)
	CustomSprite image(Images::get("Assets/Textures/Images/Pokemon/" + name + ".png"));
	initializeImagePanel(image, left);

	// Setting up right container elements (information panel)
	sf::Text headerText(sf::String("INFORMATION"), Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 70);
	sf::Text tName(sf::String(capitalizedFirst(name)), Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 50);
	sf::Text tNumber;
	sf::Text tHeightHeader(sf::String("HEIGHT:"), Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 40);
	sf::Text tWeightHeader;
	sf::Text tHeight(sf::String(height + " ft"), Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 36);
	sf::Text tWeight;
	sf::Text typeHeader;
	sf::Text weaknessHeader;
	typeHeader.setString("TYPE");
	weaknessHeader.setString("WEAKNESS");

	std::vector<CustomSprite> sTypes;
	std::vector<CustomSprite> sWeaknesses;
	initializeSpriteVector(sTypes, types, "Assets/Textures/Images/Types/");
	initializeSpriteVector(sWeaknesses, weaknesses, "Assets/Textures/Images/Types/");
	SpriteMatrix typeMatrix(&sTypes);
	SpriteMatrix weaknessMatrix(&sWeaknesses);
	initializeInfoPanel(headerText, tName, tNumber, tHeightHeader, tWeightHeader,
		tHeight, tWeight, typeHeader, weaknessHeader, 
		typeMatrix, weaknessMatrix, right);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		window.draw(background);
		window.draw(filter);
		window.draw(filter2);
		window.draw(image);
		window.draw(right);
		window.draw(headerText);
		window.draw(tName);
		window.draw(tNumber);
		window.draw(tHeightHeader);
		window.draw(tWeightHeader);
		window.draw(tHeight);
		window.draw(tWeight);
		window.draw(typeHeader);
		window.draw(weaknessHeader);
		window.draw(typeMatrix);
		window.draw(weaknessMatrix);
		window.display();
	}
}

void PokemonDetailWindow::extractData(const std::string& data)
{
	// Clearing types and weaknesses vector for new data
	types.clear();
	weaknesses.clear();

	std::stringstream main_ss(data);

	// Extracting name
	main_ss >> name;
	main_ss >> number;

	// Extracting pokemon type
	std::string type_token;
	main_ss >> type_token;
	std::stringstream type_ss(type_token);

	while (std::getline(type_ss, type_token, ','))
		types.push_back(type_token);

	// Extracting pokemon weaknesses
	std::string weakness_token;
	main_ss >> weakness_token;
	std::stringstream weakness_ss(weakness_token);

	while (std::getline(weakness_ss, weakness_token, ','))
		weaknesses.push_back(weakness_token);

	// Extracting height and weight
	main_ss >> height;
	main_ss >> weight;
}

void PokemonDetailWindow::initializeBackground(CustomSprite& background, sf::RectangleShape& filter, sf::RenderWindow& window)
{
	// Setting up background
	background.setSize((sf::Vector2f)window.getSize());

	// Setting up filter
	filter.setFillColor(sf::Color(0, 0, 0, 99));
	filter.setSize(background.getSize());
}

void PokemonDetailWindow::initializeContainer(CustomSprite& background, Container& left, Container& right)
{
	right.setFillColor(sf::Color(255, 255, 255, 99));
	right.setOutlineColor(sf::Color(100, 100, 100));
	right.setOutlineThickness(3.f);
	Position::upperLeft(background, left, padding);
	Position::upperRight(background, right, padding);
}

void PokemonDetailWindow::initializeImagePanel(CustomSprite& image, Container& left)
{
	// Setting attribute of pokemon image
	image.setSize({ left.getSize().x - padding * 2, left.getSize().x - padding * 2 });

	// Positioning all elements in image panel
	Position::centerObject(left, image);
}

void PokemonDetailWindow::initializeSpriteVector(std::vector<CustomSprite>& sprites, const std::vector<std::string>& data, const std::string& folderPath)
{
	// Initializing sprite vector with given data
	for (const std::string& d : data)
		sprites.push_back(Images::get(folderPath + d + ".png"));
}

void PokemonDetailWindow::initializeInfoPanel(sf::Text& headerText, sf::Text& tName, 
	sf::Text& tNumber, sf::Text& heightHeader, sf::Text& weightHeader, sf::Text& tHeight, 
	sf::Text& tWeight, sf::Text& typeHeader, sf::Text& weaknessHeader, SpriteMatrix& typeMatrix, 
	SpriteMatrix& weaknessMatrix, Container& right)
{
	// Set attributes of header text
	headerText.setOutlineColor(sf::Color::Black);
	headerText.setOutlineThickness(1.f);

	// Set attributes of name
	tName.setFillColor(sf::Color::White);
	tName.setOutlineColor(sf::Color::Black);
	tName.setOutlineThickness(1.f);

	// Set attributes of number
	tNumber = tName;
	tNumber.setString(sf::String("#" + number));

	// Set attributes of height header
	heightHeader.setOutlineColor(sf::Color::Black);
	heightHeader.setOutlineThickness(1.f);

	// Set attributes of weight header
	weightHeader = heightHeader;
	weightHeader.setString("WEIGHT:");

	// Set attributes of height and weight text
	tHeight.setFillColor(sf::Color::Black);
	tWeight = tHeight;
	tWeight.setString(sf::String(weight + " lbs"));

	// Set attributes of type and weakness header
	typeHeader = heightHeader;
	typeHeader.setString("TYPE");
	weaknessHeader = typeHeader;
	weaknessHeader.setString("WEAKNESS");

	// Setting attributes of sprite matrices
	typeMatrix.setContainerWidth(right.getSize().x / 2.f - padding * 2);
	weaknessMatrix.setContainerWidth(right.getSize().x / 2.f - padding * 2);
	typeMatrix.setColumns(3);
	weaknessMatrix.setColumns(3);

	// Positioning all elements in information panel
	Position::upperLeft(right, headerText, padding);
	Position::centerX(right, headerText);
	Position::down(headerText, tName, padding * 2);
	Position::centerX(headerText, tName);
	Position::down(tName, tNumber, padding);
	Position::centerX(tName, tNumber);
	Position::down(headerText, heightHeader);
	Position::downOnly(tNumber, heightHeader, padding * 2);
	Position::down(heightHeader, weightHeader, padding);
	Position::centerText(heightHeader, tHeight);
	Position::centerText(weightHeader, tWeight);
	Position::rightOnly(heightHeader, tHeight, padding + tHeight.getGlobalBounds().width / 2);
	Position::rightOnly(weightHeader, tWeight, padding + tWeight.getGlobalBounds().width / 2);
	Position::down(weightHeader, typeHeader, padding * 2);
	Position::down(typeHeader, typeMatrix, padding);
	Position::down(typeMatrix, weaknessHeader, padding);
	Position::down(weaknessHeader, weaknessMatrix, padding);
}

void PokemonDetailWindow::setSize(std::vector<CustomSprite>& sprites, const sf::Vector2f& size)
{
	// Setting size to the passed in size for all sprites in vector
	for (CustomSprite& sprite : sprites)
		sprite.setSize(size);
}

std::string PokemonDetailWindow::capitalizedFirst(const std::string& string)
{
	std::string capitalized = string;
	
	if (capitalized.size() > 0)
		capitalized.at(0) = std::toupper(capitalized.at(0));
	return capitalized;
}
