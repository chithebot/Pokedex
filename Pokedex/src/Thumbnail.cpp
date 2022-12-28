#include "Thumbnail.h"

Thumbnail::Thumbnail() : Thumbnail(sf::Texture(), 0.f) { }

Thumbnail::Thumbnail(const sf::Texture& texture, float padding) 
	: thumbnail(texture), padding(padding)
{
	setFillColor(sf::Color::Transparent);
	setSize({ 150.f, 150.f});
}

const sf::Texture* Thumbnail::getThumbnail() const { return thumbnail.getTexture(); }

float Thumbnail::getPadding() const { return padding; }

void Thumbnail::setPosition(const sf::Vector2f& position)
{
	Container::setPosition(position);
	Position::centerObject(*this, thumbnail);
}

void Thumbnail::setSize(const sf::Vector2f& size)
{
	Container::setSize(size);
	resizeAndCenterThumbnail();
}

void Thumbnail::setThumbnail(const sf::Texture& texture) 
{
	thumbnail.setTexture(texture);
	resizeAndCenterThumbnail();
}

void Thumbnail::setPadding(float p)
{
	padding = p;
	resizeAndCenterThumbnail();
}

void Thumbnail::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Container::draw(target, states);
	target.draw(thumbnail);
}

void Thumbnail::resizeAndCenterThumbnail()
{
	float x = (getSize().x - 2 * padding) / thumbnail.getGlobalBounds().width;
	float y = (getSize().y - 2 * padding) / thumbnail.getGlobalBounds().height;
	thumbnail.scale({ x, y });
	Position::centerObject(*this, thumbnail);
}
