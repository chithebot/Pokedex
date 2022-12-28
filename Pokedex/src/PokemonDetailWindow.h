#ifndef SFML_GUI_PROJECT_POKEMON_DETAIL_WINDOW_H
#define SFML_GUI_PROJECT_POKEMON_DETAIL_WINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "PokemonMap.h"
#include "Container.h"
#include "SpriteMatrix.h"
#include "Tools.h"

class PokemonDetailWindow
{
public:
	static float getPadding();
	static void setPadding(float p);
	static void runDetailWindow(const std::string& data);
private:
	static void extractData(const std::string& data);
	static void initializeBackground(CustomSprite& background, sf::RectangleShape& filter, sf::RenderWindow& window);
	static void initializeContainer(CustomSprite& background, Container& left, Container& right);
	static void initializeImagePanel(CustomSprite& image, Container& left);
	static void initializeSpriteVector(std::vector<CustomSprite>& sprites, const std::vector<std::string>& data, const std::string& folderPath);
	static void initializeInfoPanel(sf::Text& headerText, sf::Text& tName,
		sf::Text& tNumber, sf::Text& heightHeader, sf::Text& weightHeader, sf::Text& tHeight,
		sf::Text& tWeight, sf::Text& typeHeader, sf::Text& weaknessHeader, SpriteMatrix& typeMatrix,
		SpriteMatrix& weaknessMatrix, Container& right);
	static void setSize(std::vector<CustomSprite>& sprites, const sf::Vector2f& size);
	static std::string capitalizedFirst(const std::string& string);
private:
	static std::string name;
	static std::string number;
	static std::vector<std::string> types;
	static std::vector<std::string> weaknesses;
	static std::string weight;
	static std::string height;
	static float padding;
};

#endif // SFML_GUI_PROJECT_POKEMON_DETAIL_WINDOW_H
