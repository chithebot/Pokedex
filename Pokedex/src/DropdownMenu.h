#ifndef SFML_GUI_PROJECT_DROPDOWN_MENU_H
#define SFML_GUI_PROJECT_DROPDOWN_MENU_H

#include <vector>
#include <algorithm>
#include <cassert>
#include "TextButton.h"

class DropdownMenu : public sf::Drawable, public EventHandler, public States
{
public:
	DropdownMenu();
	DropdownMenu(const sf::Vector2f& buttonSize);

	float getPadding() const;
	const sf::Vector2f& getContainerSize() const;
	const sf::Color& getContainerOutlineColor() const;
	const float getContainerOutlineThickness() const;

	const sf::Vector2f& getCurrentItemSize() const;
	const sf::Color& getCurrentItemFillColor() const;
	const sf::Color& getCurrentItemHoverColor() const;
	const sf::Color& getCurrentItemTextColor() const;
	unsigned getCurrentItemTextSize() const;
	const sf::String& getCurrentItemText() const;
	const sf::Color& getCurrentItemOutlineColor() const;
	float getCurrentItemOutlineThickness() const;

	const sf::Vector2f& getButtonSize() const;
	sf::Color getButtonFillColor() const;
	sf::Color getButtonHoverColor() const;
	sf::Color getButtonTextColor() const;
	unsigned getButtonTextSize() const;

	const sf::Font* getFont() const;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	unsigned getNumItems() const;

	void setPadding(float padding);
	void setContainerOutlineColor(const sf::Color& color);
	void setContainerOutlineThickness(float thickness);

	void setFont(const sf::Font& font);

	void setCurrentItemSize(const sf::Vector2f& size);
	void setCurrentItemFillColor(const sf::Color& color);
	void setCurrentItemHoverColor(const sf::Color& color);
	void setCurrentItemTextColor(const sf::Color& color);
	void setCurrentItemTextSize(unsigned size);
	void setCurrentItemText(const sf::String& text);
	void setCurrentItemOutlineColor(const sf::Color& color);
	void setCurrentItemOutlineThickness(float thickness);

	void setButtonSize(const sf::Vector2f& size);
	void setButtonFillColor(const sf::Color& color);
	void setButtonHoverColor(const sf::Color& color);
	void setButtonTextColor(const sf::Color& color);
	void setButtonTextSize(unsigned size);

	void setPosition(const sf::Vector2f& position);
	TextButton& getButton(unsigned position);

	void addMenuItem(const sf::String& menuItem);
	void removeMenuItem(const sf::String& menuItem);
	void swapMenuItem(const sf::String& menuItem, unsigned targetPosition);

	void eventHandler(const sf::RenderWindow& window, sf::Event event) override;
	void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void resizeContainer();
	void resizeButton();
	void positionContainer();
	void positionButtons();
	std::vector<TextButton>::iterator find(const sf::String& menuItem);
	std::vector<TextButton>::iterator getTargetPosition(unsigned target);
private:
	TextButton currentItem;
	sf::RectangleShape dropdownContainer;
	std::vector<TextButton> menuItems;
	sf::Vector2f buttonSize;
	float currentItemDropdownPadding;
};

#endif // SFML_GUI_PROJECT_DROPDOWN_MENU_H
