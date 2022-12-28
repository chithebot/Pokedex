#ifndef SFML_GUI_PROJECT_CONTAINER_H
#define SFML_GUI_PROJECT_CONTAINER_H

#include <SFML\Graphics.hpp>
#include "EventHandler.h"
#include "States.h"
#include "Tools.h"

class Container : public sf::Drawable
{
public:
	Container();
	Container(const sf::Vector2f& size);

	const sf::Vector2f& getSize() const;
	const sf::Vector2f& getPosition() const;
	const sf::Color& getFillColor() const;
	sf::FloatRect getGlobalBounds() const;
	const sf::Color& getOutlineColor() const;
	float getOutlineThickness() const;

	void setSize(const sf::Vector2f size);
	void move(const sf::Vector2f& offset);
	void setPosition(const sf::Vector2f& position);
	void setFillColor(const sf::Color& color);
	void setOutlineThickness(float thickness);
	void setOutlineColor(const sf::Color& color);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape background;
};

#endif // SFML_GUI_PROJECT_CONTAINER_H
