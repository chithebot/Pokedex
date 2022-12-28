#include "Button.h"

Button::Button() : Button({200.f, 100.f}) { }

Button::Button(const sf::Vector2f& size) : Container(size)
{
	setFillColor(sf::Color::Blue);
	restStateColor = getFillColor();
	hoverStateColor = getFillColor();
}

const sf::Color& Button::getHoverColor() const { return hoverStateColor; }

void Button::setFillColor(const sf::Color& color) 
{
	Container::setFillColor(color);
	restStateColor = color;
}

void Button::setHoverColor(const sf::Color& color) { hoverStateColor = color; }

void Button::eventHandler(const sf::RenderWindow& window, sf::Event event)
{
	// Handles hover events
	if (MouseEvents::mouseHovered(getGlobalBounds(), window))
		enableState(HOVER);
	else
		disableState(HOVER);

	// Handles click events
	if (MouseEvents::mouseClicked(getGlobalBounds(), window))
	{
		enableState(PRESSED);
		setFillColor(restStateColor);
	}
}

void Button::update()
{
	// Updates hover events
	if (checkState(HOVER))
		Container::setFillColor(hoverStateColor);
	else
		Container::setFillColor(restStateColor);
}

void Button::onClick(void(*f)())
{
	if (checkState(PRESSED))
		(*f)();
}
