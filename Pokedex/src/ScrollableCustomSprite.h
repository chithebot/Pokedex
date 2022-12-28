#ifndef SFML_GUI_PROJECT_SCROLLABLE_CUSTOM_SPRITE_H
#define SFML_GUI_PROJECT_SCROLLABLE_CUSTOM_SPRITE_H

#include <iostream>
#include "CustomSprite.h"

class ScrollableCustomSprite : public CustomSprite
{
public:
	ScrollableCustomSprite();
	ScrollableCustomSprite(const sf::Texture& texture, float scrollSpeed = 40.f);
	float getInitialPosition() const;
	float getScrollSpeed() const;
	void setPosition(const sf::Vector2f& position);
	void setScrollSpeed(float speed);
	void eventHandler(const sf::RenderWindow& window, sf::Event event);
private:
	float initialPositionY;
	float scrollSpeed;
};

#endif // SFML_GUI_PROJECT_CUSTOM_SPRITE_H

