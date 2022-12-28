#include "TextInput.h"

TextInput::TextInput() : padding(0.f) { }

TextInput::TextInput(const sf::Font& font, const sf::Texture& cursorTexture, float padding)
	: label("Label: ", font, 24), textField(font, cursorTexture, 24), padding(padding)
{
	label.setFillColor(sf::Color::Black);
	positionTextField();
}

const sf::String& TextInput::getLabel() const { return label.getString(); }

unsigned TextInput::getLabelCharacterSize() const { return label.getCharacterSize(); }

const sf::Color& TextInput::getLabelCharacterColor() const { return label.getFillColor(); }

const sf::Font& TextInput::getLabelCharacterFont() const { return *label.getFont(); }

const sf::String& TextInput::getInput() const { return textField.getInput(); }

unsigned TextInput::getCharacterSize() const { return textField.getCharacterSize(); }

const sf::Color& TextInput::getCharacterColor() const { return textField.getCharacterColor(); }

const sf::Font& TextInput::getCharacterFont() const { return textField.getFont(); }

const sf::Texture& TextInput::getCursorTexture() const { return textField.getCursorTexture(); }

unsigned TextInput::getLength() const { return textField.getLength(); }

sf::Vector2f TextInput::getSize() const { return sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height); }

const sf::Vector2f& TextInput::getPosition() const { return label.getPosition(); }

sf::FloatRect TextInput::getGlobalBounds() const
{
	sf::FloatRect labelRect = label.getGlobalBounds();
	sf::FloatRect textFieldRect = textField.getGlobalBounds();
	sf::FloatRect textInputRect;
	textInputRect.width = labelRect.width + padding + textFieldRect.width;
	textInputRect.height = std::max(labelRect.height, textFieldRect.height);
	textInputRect.top = std::min(labelRect.top, textFieldRect.top);
	textInputRect.left = labelRect.left;
	return textInputRect;
}

void TextInput::setLabel(const sf::String& labelName)
{
	// Handling case where user does not want a label
	if (labelName.isEmpty())
		label.setString(labelName);
	// Handles case where user wants a label
	else
		label.setString(labelName + ": ");
	positionTextField();
}

void TextInput::setLabelCharacterSize(unsigned size)
{
	label.setCharacterSize(size);
	positionTextField();
}

void TextInput::setLabelColor(const sf::Color& color) { label.setFillColor(color); }

void TextInput::setLabelFont(const sf::Font& font)
{
	label.setFont(font);
	positionTextField();
}

void TextInput::setCharacterSize(unsigned size)
{
	textField.setCharacterSize(size);
	positionTextField();
}

void TextInput::setCharacterColor(const sf::Color& color) { textField.setCharacterColor(color); }

void TextInput::setCharacterFont(const sf::Font& font)
{
	textField.setCharacterFont(font);
	positionTextField();
}

void TextInput::setCursorTexture(const sf::Texture& texture) { textField.setCursorTexture(texture); }

void TextInput::setLength(unsigned maxNumCharacter) { textField.setLength(maxNumCharacter); }

void TextInput::setPosition(const sf::Vector2f& position)
{
	label.setPosition(position);
	if (label.getString().isEmpty())
		textField.setPosition(position);
	else
		positionTextField();
}

void TextInput::setPosition(float x, float y) { setPosition({ x, y }); }

void TextInput::clear() { textField.clear(); }

void TextInput::eventHandler(const sf::RenderWindow& window, sf::Event event) { textField.eventHandler(window, event); }

void TextInput::update() { textField.update(); }

void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Drawing all assets
	target.draw(textField);
	target.draw(label);
}

void TextInput::positionTextField()
{
	Position::right(label, textField);
	Position::centerY(label, textField);
}
