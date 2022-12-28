#include "Container.h"

Container::Container() : Container({200, 50}) { }

Container::Container(const sf::Vector2f& size)
{
	// Setting background attributes
	background.setSize(size);
	background.setFillColor(sf::Color::Blue);
}

const sf::Vector2f& Container::getSize() const { return background.getSize(); }

const sf::Vector2f& Container::getPosition() const { return background.getPosition(); }

const sf::Color& Container::getFillColor() const { return background.getFillColor(); }

sf::FloatRect Container::getGlobalBounds() const { return background.getGlobalBounds(); }

const sf::Color& Container::getOutlineColor() const { return background.getOutlineColor(); }

float Container::getOutlineThickness() const { return background.getOutlineThickness(); }

void Container::setSize(const sf::Vector2f size) { background.setSize(size); }

void Container::move(const sf::Vector2f& offset) { background.move(offset); }

void Container::setPosition(const sf::Vector2f& position) { background.setPosition(position); }

void Container::setFillColor(const sf::Color& color) { background.setFillColor(color); }

void Container::setOutlineThickness(float thickness) { background.setOutlineThickness(thickness); }

void Container::setOutlineColor(const sf::Color& color) { background.setOutlineColor(color); }

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(background); }
