#ifndef SFML_GUI_PROJECT_INPUT_FIELD_H
#define SFML_GUI_PROJECT_INPUT_FIELD_H

#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>
#include "Tools.h"
#include "GUIComponent.h"
#include "TextCursor.h"
#include "History.h"
#include "InputFieldSnapshot.h"

class InputField : public GUIComponent
{
public:
	InputField();
	InputField(const sf::Font& textFont, const sf::Texture& cursorTexture, unsigned characterSize = 24);

	unsigned getCharacterSize() const;
	const sf::Color& getCharacterColor() const;
	const sf::Font& getFont() const;
	const sf::Texture& getCursorTexture() const;
	unsigned getLength() const;
	const sf::Vector2f& getSize() const;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	const sf::String& getInput() const;
	
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
	Snapshot& getSnapshot() override;
	void applySnapshot(const Snapshot& snapshot) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void updateText(const sf::Uint32& unicode);
	bool isNextCharOverBounds(const sf::Uint32& unicode);
	void backspaceEntered();
	void validCharacterEntered(const sf::Uint32& unicode);
	void pushSnapshotIntoHistory();
	sf::FloatRect getLargestCharacterRect(bool tallest = true) const;
	void scaleCursor();
	void positionCursor();
	void positionText();
	void resize();

private:
	// Frontend member variables
	sf::Text text;
	sf::RectangleShape textField;
	TextCursor cursor;

	// Backend member variables
	InputFieldSnapshot inputFieldSnapshot;
	sf::String input;
	unsigned numberOfCharInView;
	float verticalPadding;
	float horizontalPadding;
};

#endif // SFML_GUI_PROJECT_INPUT_FIELD_H