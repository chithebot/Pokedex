#ifndef SFML_GUI_PROJECT_CUSTOM_SPRITE_H
#define SFML_GUI_PROJECT_CUSTOM_SPRITE_H

#include <SFML\Graphics.hpp>
#include "GUIComponent.h"

class CustomSprite : public sf::Drawable
{
public:
	CustomSprite();
	CustomSprite(const sf::Texture& texture);
	const sf::Vector2f& getPosition() const;
	sf::Vector2f getSize() const;
	const sf::Texture* getTexture() const;
	sf::FloatRect getGlobalBounds() const;
	void move(const sf::Vector2f& offset);
	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	void setTexture(const sf::Texture& texture);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Sprite sprite;
};

#endif // SFML_GUI_PROJECT_CUSTOM_SPRITE_H
