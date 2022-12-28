#ifndef SFML_GUI_PROJECT_MOUSE_EVENTS_H
#define SFML_GUI_PROJECT_MOUSE_EVENTS_H

#include <SFML\Graphics.hpp>

class MouseEvents
{
public:
	static bool mouseClicked(const sf::FloatRect& objRect, const sf::RenderWindow& window);
	static bool mouseClicked(const sf::RenderWindow& window, sf::Event event);
	static bool mouseClickedElsewhere(const sf::FloatRect& objRect, const sf::RenderWindow& window);
	static bool mouseHovered(const sf::FloatRect& objRect, const sf::RenderWindow& window);
};

#endif // SFML_GUI_PROJECT_MOUSE_EVENTS_H
