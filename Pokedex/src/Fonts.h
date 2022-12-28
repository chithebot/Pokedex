#ifndef SFML_GUI_PROJECT_FONTS_H
#define SFML_GUI_PROJECT_FONTS_H

#include <string>
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include "FontNotFoundException.h"

class Fonts
{
public:
	static sf::Font& get(const std::string& fontPath) noexcept(false);
private:
	static void load(const std::string& fontPath) noexcept(false);
private:
	static std::unordered_map<std::string, sf::Font*> fonts;
};

#endif // SFML_GUI_PROJECT_FONTS_H
