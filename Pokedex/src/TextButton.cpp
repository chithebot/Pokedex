#include "TextButton.h"

TextButton::TextButton() : TextButton({200.f, 100.f}, "Text") { }

TextButton::TextButton(const sf::Vector2f size)
	: TextButton(size, "") { }

TextButton::TextButton(const sf::Vector2f size, const sf::String& string)
	: Button(size), text(string, Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 24)
{
	Position::centerText(*this, text);
}

const sf::String& TextButton::getText() const { return text.getString(); }

const sf::Color& TextButton::getTextColor() const { return text.getFillColor(); }

unsigned TextButton::getCharacterSize() const { return text.getCharacterSize(); }

const sf::Font* TextButton::getFont() const { return text.getFont(); }

void TextButton::setSize(const sf::Vector2f& size)
{
	Button::setSize(size);
	Position::centerText(*this, text);
}

void TextButton::move(const sf::Vector2f& offset)
{
	Button::move(offset);
	Position::centerText(*this, text);
}

void TextButton::setPosition(const sf::Vector2f& position)
{
	Button::setPosition(position);
	Position::centerText(*this, text);
}

void TextButton::setText(const sf::String& string) 
{
	text.setString(string);
	Position::centerText(*this, text);
}

void TextButton::setTextColor(const sf::Color& color) { text.setFillColor(color); }

void TextButton::setCharacterSize(unsigned size) 
{
	text.setCharacterSize(size);
	Position::centerText(*this, text);
}

void TextButton::setFont(const sf::Font& font) 
{
	text.setFont(font);
	Position::centerText(*this, text);
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Button::draw(target, states);
	target.draw(text);
}
