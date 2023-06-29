#ifndef SFML_GUI_PROJECT_POKEMON_ENTRY_H
#define SFML_GUI_PROJECT_POKEMON_ENTRY_H

#include "Entry.h"
#include "Thumbnail.h"
#include "CustomSprite.h"
#include "SpriteMatrix.h"

class PokemonEntry : public Entry
{
public:
	PokemonEntry();
	PokemonEntry(const sf::Texture& texture);
	PokemonEntry(const sf::Texture& texture, const sf::String& name);
	PokemonEntry(const sf::Texture& texture, const sf::String& name, const sf::String& number);
	PokemonEntry(const sf::Texture& texture, const sf::String& name, const sf::String& number,
		const std::vector<std::string>& data, float thumbnailPadding = 10.f, float textPadding = 10.f);

	const sf::String& getName() const;
	const sf::String& getNumber() const;
	const sf::Font* getFont() const;
	unsigned getCharacterSize() const;
	const sf::Texture* getThumbnail() const;
	float getThumbnailOutlineThickness() const;
	const sf::Color& getThumbnailOutlineColor() const;
	float getThumbnailPadding() const;
	float getTextPadding() const;
	const std::vector<std::string>& getTypeData() const;

	void move(const sf::Vector2f& offset);
	void setPosition(const sf::Vector2f& position);
	void setName(const sf::String& string);
	void setNumber(const sf::String& string);
	void setFont(const sf::Font& font);
	void setCharacterSize(unsigned size);
	void setSize(const sf::Vector2f& size);
	void setThumbnail(const sf::Texture& texture);
	void setThumbnailOutlineThickness(float thickness);
	void setThumbnailOutlineColor(const sf::Color& color);
	void setThumbnailPadding(float padding);
	void setTextPadding(float padding);
	void setTypeData(const std::vector<std::string>& data);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Vector2f getMinimumSize(const sf::Vector2f& size);
	void positionAll();
	void positionThumbnail();
	void positionText();
	void positionTypeSprite();
	void resizeThumbnail();
	void extractIntoSpriteVector(const std::string& folderPath);
private:
	Thumbnail thumbnail;
	sf::Text name;
	sf::Text number;
	float thumbnailPadding;
	float textPadding;
	std::vector<CustomSprite> types;
	std::vector<std::string> typeData;
};

#endif // SFML_GUI_PROJECT_POKEMON_ENTRY_H
