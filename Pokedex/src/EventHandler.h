#ifndef SFML_GUI_PROJECT_EVENT_HANDLER_H
#define SFML_GUI_PROJECT_EVENT_HANDLER_H

#include <SFML\Graphics.hpp>

class EventHandler
{
public:
	virtual void eventHandler(const sf::RenderWindow& window, sf::Event event) = 0;
	virtual void update() = 0;
};

#endif // SFML_GUI_PROJECT_EVENT_HANDLER_H
