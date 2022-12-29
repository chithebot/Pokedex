#include "CustomSprite.h"

CustomSprite::CustomSprite() : sprite() { }

CustomSprite::CustomSprite(const sf::Texture& texture) : sprite(texture) { }

const sf::Vector2f& CustomSprite::getPosition() const { return sprite.getPosition(); }

sf::Vector2f CustomSprite::getSize() const { return sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height); }

const sf::Texture* CustomSprite::getTexture() const { return sprite.getTexture(); }

sf::FloatRect CustomSprite::getGlobalBounds() const { return sprite.getGlobalBounds(); }

void CustomSprite::move(const sf::Vector2f& offset) { sprite.move(offset); }

void CustomSprite::setPosition(const sf::Vector2f& position) { sprite.setPosition(position); }

void CustomSprite::setSize(const sf::Vector2f& size)
{
	float x = size.x / getGlobalBounds().width;
	float y = size.y / getGlobalBounds().height;
	sprite.scale({ x, y });
}

void CustomSprite::setTexture(const sf::Texture& texture) { sprite.setTexture(texture); }

void CustomSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite); }
