#include "TextCursor.h"

TextCursor::TextCursor() { }

TextCursor::TextCursor(const sf::Texture& texture) { setTexture(texture); }

void TextCursor::setScale(const sf::Vector2f& scale)
{
	Sprite::setScale(scale);
	targetScale = scale;
}

void TextCursor::update()
{
	// Updates the cursor based on hidden state
	if (checkState(HIDDEN))
	{
		disableState(BLINK);
		Sprite::setScale({ 0.f, 0.f });
	}
	else
	{
		enableState(BLINK);
	}

	// Updates the cursor based on blink state
	if (checkState(BLINK))
	{
		if (clock.getElapsedTime().asMilliseconds() >= 500)
		{
			toggleState(BLINK_ON);
			clock.restart();
		}
	}
	else
	{
		disableState(BLINK_ON);
	}

	// Updates the cursor image to cause a blinking effect
	if (checkState(BLINK_ON))
		Sprite::setScale(targetScale);
	else
		Sprite::setScale({ 0.f, 0.f });
}
