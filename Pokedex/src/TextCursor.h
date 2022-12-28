#ifndef SFML_GUI_PROJECT_TEXT_CURSOR_H
#define SFML_GUI_PROJECT_TEXT_CURSOR_H

#include <cassert>
#include <SFML\Graphics.hpp>
#include "States.h"
#include "EventHandler.h"

class TextCursor : public sf::Sprite, public States
{
public:
	TextCursor();
	TextCursor(const sf::Texture& texture);
	void setScale(const sf::Vector2f& scale);
	void update();
private:
	sf::Vector2f targetScale;
	sf::Clock clock;
};

#endif // SFML_GUI_PROJECT_TEXT_CURSOR_H
