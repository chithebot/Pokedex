#include "SpriteMatrix.h"

SpriteMatrix::SpriteMatrix() : SpriteMatrix(nullptr) { }

SpriteMatrix::SpriteMatrix(std::vector<CustomSprite>* spritePtr, unsigned columns, float padding)
	: sprites(spritePtr), columns(columns), padding(padding)
{
	container.setFillColor(sf::Color::Transparent);
	setContainerWidth(300.f);
}

sf::FloatRect SpriteMatrix::getGlobalBounds() const { return container.getGlobalBounds(); }

const sf::Vector2f& SpriteMatrix::getSize() const { return container.getSize(); }

float SpriteMatrix::getContainerWidth() const { return container.getSize().x; }

unsigned SpriteMatrix::getColumns() const { return columns; }

const sf::Vector2f& SpriteMatrix::getPosition() const { return container.getPosition(); }

void SpriteMatrix::setContainerWidth(float width)
{
	container.setSize({ width, container.getSize().y });
	resizeAll();
	repositionSprites();
}

void SpriteMatrix::setColumns(unsigned n)
{
	columns = n;
	resizeAll();
	repositionSprites();
}

void SpriteMatrix::setPosition(const sf::Vector2f& position)
{
	container.setPosition(position);
	repositionSprites();
}

void SpriteMatrix::resize()
{
	resizeAll();
	repositionSprites();
}

void SpriteMatrix::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(container);
	for (CustomSprite& sprite : *sprites)
		target.draw(sprite);
}

void SpriteMatrix::resizeAll()
{
	resizeSprites();
	resizeContainerHeight();
}

void SpriteMatrix::resizeSprites()
{
	// Resizing sprites to be fitted into container while retaining similar resolution if there are any
	if (sprites->size() > 0)
	{
		float heightToWidthRatio = sprites->at(0).getSize().y / sprites->at(0).getSize().x;
		float widthPerSprite = (container.getSize().x - padding * (columns + 1)) / columns;

		// Resizing all sprites
		for (CustomSprite& sprite : *sprites)
			sprite.setSize({ widthPerSprite, widthPerSprite * heightToWidthRatio });
	}
}

void SpriteMatrix::resizeContainerHeight()
{
	// Resizes container height according to height of sprite
	if (sprites->size() > 0)
	{
		unsigned row = (sprites->size() / columns) + (sprites->size() % columns > 0);
		float spriteHeight = sprites->at(0).getSize().y;
		float newContainerHeight = (spriteHeight * row) + (padding * (row + 1));
		container.setSize({ container.getSize().x, newContainerHeight });
	}
}

void SpriteMatrix::repositionSprites()
{
	float initialX = container.getPosition().x;
	float y = container.getPosition().y + padding;

	// Handles centering of a matrix containing only one sprite
	if (sprites->size() == 1)
	{
		Position::centerObject(container, sprites->at(0));
	}
	// Handles positioning of sprites in matrix which contains more than one sprite
	else if (sprites->size() > 1)
	{
		// Positioning each sprite in rows
		for (unsigned i = 0; i < sprites->size(); ++i)
		{
			CustomSprite& current = sprites->at(i);

			// Handles the first column sprites (except the first)
			if (i % columns == 0)
			{
				if (i != 0)
				{
					y = y + padding + current.getSize().y;
				}
				current.setPosition({ initialX, y });

				// Handles centering for case of 1 column per row
				if (columns == 1)
					Position::centerX(container, current);
			}
			// Handles sprites at columns other than first
			else
			{
				CustomSprite& previous = sprites->at(i - 1);
				Position::rightOnly(previous, current, padding);
				current.setPosition({ current.getPosition().x, y });
			}
		}
	}
}