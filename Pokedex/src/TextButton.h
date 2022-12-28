#ifndef SFML_GUI_PROJECT_TEXT_BUTTON_H
#define SFML_GUI_PROJECT_TEXT_BUTTON_H

#include <iostream>
#include "Button.h"

class TextButton : public Button
{
public:
	TextButton();
	TextButton(const sf::Vector2f size);
	TextButton(const sf::Vector2f size, const sf::String& string);

	const sf::String& getText() const;
	const sf::Color& getTextColor() const;
	unsigned getCharacterSize() const;
	const sf::Font* getFont() const;

	void setSize(const sf::Vector2f& size);
	void move(const sf::Vector2f& offset);
	void setPosition(const sf::Vector2f& position);
	void setText(const sf::String& string);
	void setTextColor(const sf::Color& color);
	void setCharacterSize(unsigned size);
	void setFont(const sf::Font& font);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Text text;
};

#endif // SFML_GUI_PROJECT_TEXT_BUTTON_H
