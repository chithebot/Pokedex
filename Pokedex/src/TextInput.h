#ifndef SFML_GUI_PROJECT_TEXT_INPUT_H
#define SFML_GUI_PROJECT_TEXT_INPUT_H

#include <cmath>
#include <cassert>
#include "InputField.h"

class TextInput : public sf::Drawable, public EventHandler
{
public:
	TextInput();
	TextInput(const sf::Font& font, const sf::Texture& cursorTexture, float padding = 10.f);

	const sf::String& getLabel() const;
	unsigned getLabelCharacterSize() const;
	const sf::Color& getLabelCharacterColor() const;
	const sf::Font& getLabelCharacterFont() const;
	const sf::String& getInput() const;
	unsigned getCharacterSize() const;
	const sf::Color& getCharacterColor() const;
	const sf::Font& getCharacterFont() const;
	const sf::Texture& getCursorTexture() const;
	sf::Vector2f getSize() const;
	unsigned getLength() const;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getGlobalBounds() const;

	void setLabel(const sf::String& labelName);
	void setLabelCharacterSize(unsigned size);
	void setLabelColor(const sf::Color& color);
	void setLabelFont(const sf::Font& font);

	void setCharacterSize(unsigned size);
	void setCharacterColor(const sf::Color& color);
	void setCharacterFont(const sf::Font& font);
	void setCursorTexture(const sf::Texture& texture);
	void setLength(unsigned maxNumCharacter);

	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);
	void clear();

	void eventHandler(const sf::RenderWindow& window, sf::Event event) override;
	void update() override;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void positionTextField();

private:
	InputField textField;
	sf::Text label;
	float padding;
};

#endif // SFML_GUI_PROJECT_TEXT_INPUT_H