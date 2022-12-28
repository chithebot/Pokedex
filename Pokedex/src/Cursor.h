#ifndef SFML_GUI_PROJECT_CURSOR_H
#define SFML_GUI_PROJECT_CURSOR_H

#include <SFML\Graphics.hpp>

class Cursor
{
public:
	static const sf::Cursor& getCursor();
	static bool loadFromPixels(const sf::Uint8* pixels, const sf::Vector2u& size, const sf::Vector2u& hotspot);
	static bool loadFromSystem(sf::Cursor::Type type);
private:
	static sf::Cursor cursor;
};

#endif // SFML_GUI_PROJECT_CURSOR_H
