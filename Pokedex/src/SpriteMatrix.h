#ifndef SFML_GUI_PROJECT_SPRITE_MATRIX_H
#define SFML_GUI_PROJECT_SPRITE_MATRIX_H

#include "Container.h"
#include "CustomSprite.h"
#include "Tools.h"

class SpriteMatrix : public sf::Drawable
{
public:
	SpriteMatrix();
	SpriteMatrix(std::vector<CustomSprite>* spritePtr, unsigned columns = 3, float padding = 10.f, bool centered = false);
	sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f& getSize() const;
	float getContainerWidth() const;
	unsigned getColumns() const;
	const sf::Vector2f& getPosition() const;
	bool getCentered() const;
	void setContainerWidth(float width);
	void setColumns(unsigned n);
	void setPosition(const sf::Vector2f& position);
	void setCentered(bool c);
	void resize();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void resizeAll();
	void resizeSprites();
	void resizeContainerHeight();
	void repositionSprites();
private:
	sf::RectangleShape container;
	std::vector<CustomSprite>* sprites;
	float padding;
	unsigned columns;
	bool centered;
};

#endif // SFML_GUI_PROJECT_SPRITE_MATRIX_H
