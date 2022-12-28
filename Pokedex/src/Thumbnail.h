#ifndef SFML_GUI_PROJECT_THUMBNAIL_H
#define SFML_GUI_PROJECT_THUMBNAIL_H

#include <SFML\Graphics.hpp>
#include "Container.h"
#include "Tools.h"

class Thumbnail : public Container
{
public:
	Thumbnail();
	Thumbnail(const sf::Texture& texture, float padding = 0.f);

	const sf::Texture* getThumbnail() const;
	float getPadding() const;

	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	void setThumbnail(const sf::Texture& texture);
	void setPadding(float p);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void resizeAndCenterThumbnail();
private:
	sf::Sprite thumbnail;
	float padding;
};

#endif // SFML_GUI_PROJECT_THUMBNAIL_H
