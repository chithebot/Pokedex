#include "ScrollableCustomSprite.h"

ScrollableCustomSprite::ScrollableCustomSprite() : CustomSprite(), scrollSpeed(40.f) { }

ScrollableCustomSprite::ScrollableCustomSprite(const sf::Texture& texture, float scrollSpeed)
	: CustomSprite(texture), initialPositionY(0.f), scrollSpeed(scrollSpeed) { }

float ScrollableCustomSprite::getInitialPosition() const { return initialPositionY; }

float ScrollableCustomSprite::getScrollSpeed() const { return scrollSpeed; }

void ScrollableCustomSprite::setScrollSpeed(float speed) { scrollSpeed = speed; }

void ScrollableCustomSprite::setPosition(const sf::Vector2f& position)
{
	CustomSprite::setPosition(position);
	initialPositionY = position.y;
}

void ScrollableCustomSprite::eventHandler(const sf::RenderWindow& window, sf::Event event)
{
	// Checks for mouse scrolling events
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		float offset = -1 * event.mouseWheelScroll.delta;
		move({ 0.f, offset * scrollSpeed });

		// Handles scrolling before initial position bounds
		if (getPosition().y < initialPositionY)
		{
			CustomSprite::setPosition({ getPosition().x, initialPositionY });
		}
	}
}
