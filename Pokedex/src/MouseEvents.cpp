#include "MouseEvents.h"

bool MouseEvents::mouseClicked(const sf::FloatRect& objRect, const sf::RenderWindow& window)
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseEvents::mouseHovered(objRect, window);
}

bool MouseEvents::mouseClicked(const sf::RenderWindow& window, sf::Event event)
{
	sf::Vector2f winPosition = (sf::Vector2f)(window.getPosition());
	sf::Vector2f winSize = (sf::Vector2f)(window.getSize());
	sf::FloatRect winRect(winPosition, winPosition + winSize);
	return mouseClicked(winRect, window);
}

bool MouseEvents::mouseClickedElsewhere(const sf::FloatRect& objRect, const sf::RenderWindow& window)
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left) && !MouseEvents::mouseHovered(objRect, window);
}

bool MouseEvents::mouseHovered(const sf::FloatRect& objRect, const sf::RenderWindow& window)
{
	sf::Vector2i mpos = sf::Mouse::getPosition(window);
	sf::Vector2f mposWorld = window.mapPixelToCoords(mpos);
	return objRect.contains(mposWorld);
}
