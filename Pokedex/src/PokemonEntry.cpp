#include "PokemonEntry.h"

PokemonEntry::PokemonEntry() : PokemonEntry(sf::Texture()) { }

PokemonEntry::PokemonEntry(const sf::Texture& texture) : PokemonEntry(texture, "") { }

PokemonEntry::PokemonEntry(const sf::Texture& texture, const sf::String& name) : PokemonEntry(texture, name, "0") { }

PokemonEntry::PokemonEntry(const sf::Texture& texture, const sf::String& name, const sf::String& number)
	: PokemonEntry(texture, name, number, std::vector<std::string>()) { }

PokemonEntry::PokemonEntry(const sf::Texture& texture, const sf::String& name, const sf::String& number,
	const std::vector<std::string>& data, float thumbnailPadding, float textPadding)
	: thumbnail(texture), thumbnailPadding(thumbnailPadding), textPadding(textPadding),
	name(name, Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 16),
	number(number, Fonts::get("Assets/Fonts/OpenSans-Bold.ttf"), 16),
	typeData(data)
{
	setSize({ 150.f, 250.f });
	setOutlineThickness(2.f);
	setOutlineColor(sf::Color::Black);
	setFillColor(sf::Color(50, 50, 50));
	setHoverColor(sf::Color(25, 25, 25));
	extractIntoSpriteVector("Assets/Textures/Images/Types/");
	positionAll();
}

const sf::String& PokemonEntry::getName() const { return name.getString(); }

const sf::String& PokemonEntry::getNumber() const { return number.getString(); }

const sf::Font* PokemonEntry::getFont() const { return name.getFont(); }

unsigned PokemonEntry::getCharacterSize() const { return name.getCharacterSize(); }

const sf::Texture* PokemonEntry::getThumbnail() const { return thumbnail.getThumbnail(); }

float PokemonEntry::getThumbnailOutlineThickness() const { return thumbnail.getOutlineThickness(); }

const sf::Color& PokemonEntry::getThumbnailOutlineColor() const { return thumbnail.getOutlineColor(); }

float PokemonEntry::getThumbnailPadding() const { return thumbnailPadding; }

float PokemonEntry::getTextPadding() const { return textPadding; }

const std::vector<std::string>& PokemonEntry::getTypeData() const { return typeData; }

void PokemonEntry::move(const sf::Vector2f& offset)
{
	Button::move(offset);
	positionAll();
}

void PokemonEntry::setPosition(const sf::Vector2f& position)
{
	Button::setPosition(position);
	positionAll();
}

void PokemonEntry::setName(const sf::String& string)
{ 
	name.setString(string);
	positionAll();
}

void PokemonEntry::setNumber(const sf::String& string)
{ 
	number.setString(string);
	positionAll();
}

void PokemonEntry::setFont(const sf::Font& font)
{
	name.setFont(font);
	number.setFont(font);
	positionAll();
}

void PokemonEntry::setCharacterSize(unsigned size)
{
	name.setCharacterSize(size);
	number.setCharacterSize(size);
	positionAll();
}

void PokemonEntry::setSize(const sf::Vector2f& size)
{
	sf::Vector2f minimumSize = getMinimumSize(size);

	// Checks if the given size is at least the minimum size
	if (size.y < minimumSize.y)
		Button::setSize(minimumSize);
	else if (size.y >= minimumSize.y && size.y > size.x)
		Button::setSize(size);

	// Resizing thumbnail and repositioning all objects within PokemonEntry
	resizeThumbnail();
	positionAll();
}

void PokemonEntry::setThumbnail(const sf::Texture& texture)
{
	thumbnail.setThumbnail(texture);
	resizeThumbnail();
	positionAll();
}

void PokemonEntry::setThumbnailOutlineThickness(float thickness) { thumbnail.setOutlineThickness(thickness); }

void PokemonEntry::setThumbnailOutlineColor(const sf::Color& color) { thumbnail.setOutlineColor(color); }

void PokemonEntry::setThumbnailPadding(float padding)
{
	thumbnailPadding = padding;
	resizeThumbnail();
	positionAll();
}

void PokemonEntry::setTextPadding(float padding)
{
	textPadding = padding;
	positionAll();
}

void PokemonEntry::setTypeData(const std::vector<std::string>& data)
{
	typeData = data;
	extractIntoSpriteVector("Assets/Textures/Images/Types/");
	positionAll();
}

void PokemonEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Only draws entry if it is not in hidden state
	if (!checkState(HIDDEN))
	{
		Button::draw(target, states);
		target.draw(thumbnail);
		target.draw(name);
		target.draw(number);

		// Drawing type sprites
		for (const CustomSprite& sprite : types)
			target.draw(sprite);
	}
}

sf::Vector2f PokemonEntry::getMinimumSize(const sf::Vector2f& size)
{
	// Getting size of sprite matrix
	SpriteMatrix matrix(&types, 2);
	matrix.setContainerWidth(getSize().x - textPadding * 2);

	// Gets the minimum size (based on the passed in size) to fit all elements of PokemonEntry
	const sf::Font* f_ptr = getFont();
	float tallestCharacterHeight = f_ptr->getGlyph('j', getCharacterSize(), false).bounds.height;
	float tallestNumberHeight = f_ptr->getGlyph('9', getCharacterSize(), false).bounds.height;
	float y = size.x + textPadding * 3 + tallestCharacterHeight + tallestNumberHeight + matrix.getSize().y;
	return sf::Vector2f(size.x, y);
}

void PokemonEntry::positionAll()
{
	positionThumbnail();
	positionText();
	positionTypeSprite();
}

void PokemonEntry::positionThumbnail()
{
	Position::upperRight(*this, thumbnail, thumbnailPadding);
	Position::centerX(*this, thumbnail);
}

void PokemonEntry::positionText()
{
	Position::down(thumbnail, name, textPadding + thumbnailPadding);
	Position::down(name, number, textPadding);
	Position::centerX(thumbnail, name);
	Position::centerX(name, number);
}

void PokemonEntry::positionTypeSprite()
{
	// Creating SpriteMatrix to aid in positioning
	SpriteMatrix matrix(&types, 1);
	matrix.setContainerWidth(getSize().x / 2.5f);
	Position::down(number, matrix, textPadding);
	Position::centerX(number, matrix);
}

void PokemonEntry::resizeThumbnail()
{
	// Getting size thumbnail should be relative to entry container size
	float x = getSize().x - 2.f * thumbnailPadding;
	float y = x;
	thumbnail.setSize({ x, y });
}

void PokemonEntry::extractIntoSpriteVector(const std::string& folderPath)
{
	// Initializing sprite vector with given data
	for (const std::string& d : typeData)
		types.push_back(Images::get(folderPath + d + ".png"));
}