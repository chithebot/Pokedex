#include "InputField.h"

InputField::InputField() : numberOfCharInView(0), verticalPadding(0.f), horizontalPadding(0.f) { }

InputField::InputField(const sf::Font& textFont, const sf::Texture& cursorTexture, unsigned characterSize)
	: numberOfCharInView(10)
{
	// Setting up text font and text cursor textures
	text.setFont(textFont);
	cursor.setTexture(cursorTexture);
	
	// Setting text attributes
	text.setCharacterSize(characterSize);
	text.setFillColor(sf::Color::Black);

	// Setting text field attributes
	textField.setFillColor(sf::Color::White);
	textField.setOutlineThickness(2.f);
	textField.setOutlineColor(sf::Color::Black);
	
	// Setting up sizing and position of the text field, text, and cursor
	resize();
}

unsigned InputField::getCharacterSize() const { return text.getCharacterSize(); }

const sf::Color& InputField::getCharacterColor() const { return text.getFillColor(); }

const sf::Font& InputField::getFont() const { return *(text.getFont()); }

const sf::Texture& InputField::getCursorTexture() const { return *(cursor.getTexture()); }

unsigned InputField::getLength() const { return numberOfCharInView; }

const sf::Vector2f& InputField::getSize() const { return textField.getSize(); }

const sf::Vector2f& InputField::getPosition() const { return textField.getPosition(); }

sf::FloatRect InputField::getGlobalBounds() const { return textField.getGlobalBounds(); }

const sf::String& InputField::getInput() const { return input; }

void InputField::setCharacterSize(unsigned size) 
{
	text.setCharacterSize(size);
	resize();
}

void InputField::setCharacterColor(const sf::Color& color) { text.setFillColor(color); }

void InputField::setCharacterFont(const sf::Font& font) { text.setFont(font); }

void InputField::setCursorTexture(const sf::Texture& texture) { cursor.setTexture(texture); }

void InputField::setLength(unsigned length)
{
	float maxCharWidth = getLargestCharacterRect(false).width;
	numberOfCharInView = length;
	textField.setSize({ maxCharWidth * numberOfCharInView + horizontalPadding * 2.f, textField.getSize().y });
}

void InputField::setPosition(const sf::Vector2f& position) 
{
	textField.setPosition(position);
	positionText();
	positionCursor();
}

void InputField::setPosition(float x, float y) { setPosition({x, y}); }

void InputField::clear()
{
	input.clear();
	text.setString(input);
}

void InputField::eventHandler(const sf::RenderWindow& window, sf::Event event)
{
	// Handle focusing event
	if (MouseEvents::mouseClicked(textField.getGlobalBounds(), window))
		enableState(FOCUS);

	// Handles unfocusing event
	if (MouseEvents::mouseClickedElsewhere(textField.getGlobalBounds(), window))
		disableState(FOCUS);
	
	// Handle events while object is focused
	if (checkState(FOCUS))
	{
		// Handles text being entered event
		if (!KeyShortcuts::ctrlPressed() && event.type == sf::Event::TextEntered)
		{
			updateText(event.text.unicode);
		}

		// Handles undo events
		if (KeyShortcuts::isUndo() && !History::emptyHistory() &&
			 this == History::topHistory().component && event.type == sf::Event::KeyPressed)
		{
			History::topHistory().component->applySnapshot(*(History::topHistory().snapshot));
			History::popHistory();
		}
		positionCursor();
	}
}

void InputField::update()
{
	// Updates objects on state of being focused and unfocused
	if (checkState(FOCUS))
	{
		textField.setOutlineColor(sf::Color::Blue);
		textField.setOutlineThickness(3.f);
		cursor.disableState(HIDDEN);
	}
	else
	{
		textField.setOutlineColor(sf::Color::Black);
		textField.setOutlineThickness(2.f);
		cursor.enableState(HIDDEN);
	}
	cursor.update();
}

Snapshot& InputField::getSnapshot() { return inputFieldSnapshot; }

void InputField::applySnapshot(const Snapshot& snapshot)
{
	// Applying snapshot to back end member variables
	const InputFieldSnapshot* ifs_ptr = static_cast<const InputFieldSnapshot*>(&snapshot);
	inputFieldSnapshot = *ifs_ptr;
	input = inputFieldSnapshot.input;
	text.setString(inputFieldSnapshot.viewed);
}

void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Drawing input field assets
	target.draw(textField);
	target.draw(text);
	target.draw(cursor);
}

void InputField::updateText(const sf::Uint32& unicode)
{
	// Handles case for backspace character being typed
	if ((unicode == '\b') && !text.getString().isEmpty())
	{
		pushSnapshotIntoHistory();
		backspaceEntered();
	}
	// Handles case for valid characters being typed
	else if (unicode >= 32 && unicode < 127)
	{
		pushSnapshotIntoHistory();
		validCharacterEntered(unicode);
	}
	inputFieldSnapshot.input = input;
	inputFieldSnapshot.viewed = text.getString();
}

bool InputField::isNextCharOverBounds(const sf::Uint32& unicode)
{
	// Checking if this character being typed will result in going beyonds bounds of text field
	const sf::Glyph& glyph = text.getFont()->getGlyph(unicode, text.getCharacterSize(), false);
	sf::FloatRect textFieldRect = textField.getGlobalBounds();
	sf::FloatRect textRect = text.getGlobalBounds();

	float textRightBounds = textFieldRect.left + textFieldRect.width - horizontalPadding;
	float textRight = textRect.left + textRect.width;
	return (textRight + glyph.advance > textRightBounds);
}

void InputField::backspaceEntered()
{
	// Deleting last character
	sf::String string = text.getString();	// Tracks the viewable text
	input.erase(input.getSize() - 1);
	string.erase(string.getSize() - 1);

	// Pushes text that has been hidden into display
	if (input.getSize() > string.getSize())
		string = input[input.getSize() - string.getSize() - 1] + string;
	text.setString(string);
}

void InputField::validCharacterEntered(const sf::Uint32& unicode)
{
	// Adding character that was entered
	sf::String string = text.getString();	// Tracks the viewable text
	input = input + sf::String(unicode);
	string = string + sf::String(unicode);

	// Erases first two characters from view if character typed passes bounds
	if (isNextCharOverBounds(unicode))
		string.erase(0, 2);
	text.setString(string);
}

void InputField::pushSnapshotIntoHistory()
{
	// Creating a snapshot of input field's current state, in heap, and pushing to history
	InputFieldSnapshot* ifs_ptr = new InputFieldSnapshot(inputFieldSnapshot);
	History::pushHistory(ifs_ptr, this);
}

sf::FloatRect InputField::getLargestCharacterRect(bool tallest) const
{
	sf::FloatRect largestRect;

	// Finding character with largest bounding rectangle
	for (sf::Uint32 unicode = 32; unicode < 127; ++unicode)
	{
		const sf::Glyph& glyph = text.getFont()->getGlyph(unicode, text.getCharacterSize(), false);
		sf::FloatRect glyphRect = glyph.bounds;
		
		// Looks for tallest character
		if (tallest)
		{
			if (glyphRect.height > largestRect.height)
				largestRect = glyphRect;
		}
		// Looks for widest character
		else
		{
			if (glyphRect.width > largestRect.width)
				largestRect = glyphRect;
		}
	}
	return largestRect;
}

void InputField::scaleCursor()
{
	// Scaling cursor to text field size
	sf::FloatRect cursorRect = cursor.getLocalBounds();
	sf::FloatRect textFieldRect = textField.getGlobalBounds();
	float horizontalScalar = 0.01f;
	float verticalScalar = std::min(cursorRect.height, textFieldRect.height) / std::max(cursorRect.height, textFieldRect.height);
	cursor.setScale({ horizontalScalar, verticalScalar });
}

void InputField::positionCursor()
{
	// Positions cursor at beginning of text field if text is empty
	if (text.getString().isEmpty())
	{
		sf::FloatRect textFieldRect = textField.getGlobalBounds();
		cursor.setPosition(textFieldRect.left + horizontalPadding, textFieldRect.top);
	}
	// Positions cursor at end of any existing text
	else
	{
		sf::FloatRect textRect = text.getGlobalBounds();
		cursor.setPosition(textRect.left + textRect.width, cursor.getPosition().y);
	}
}

void InputField::positionText()
{
	// Positioning text inside text field
	sf::FloatRect textFieldRect = textField.getGlobalBounds();
	text.setPosition({ textFieldRect.left + horizontalPadding, textFieldRect.top });
}

void InputField::resize()
{
	// Resize text field based on character size and vertical padding
	float maxCharHeight = getLargestCharacterRect(true).height;
	float maxCharWidth = getLargestCharacterRect(false).width;
	verticalPadding = maxCharHeight / 5.f;
	horizontalPadding = maxCharWidth / 2.f ;
	textField.setSize({ maxCharWidth * numberOfCharInView + horizontalPadding * 2.f, maxCharHeight + verticalPadding });

	// Resizing cursor based on text field size
	scaleCursor();

	// Repositioning text and cursor based on text field position
	positionText();
	positionCursor();
}
