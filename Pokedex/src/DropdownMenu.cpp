#include "DropdownMenu.h"

DropdownMenu::DropdownMenu() : DropdownMenu({200.f, 50.f}) { }

DropdownMenu::DropdownMenu(const sf::Vector2f& buttonSize) : currentItem(buttonSize, "-Select-"), dropdownContainer({ 0.f, 0.f }), currentItemDropdownPadding(0.f), buttonSize(buttonSize)
{
	enableState(HIDDEN);
	currentItem.setCharacterSize(24);
	currentItem.setTextColor(sf::Color::White);
	dropdownContainer.setFillColor(sf::Color::Transparent);
	positionContainer();
}

float DropdownMenu::getPadding() const { return currentItemDropdownPadding; }

const sf::Vector2f& DropdownMenu::getContainerSize() const { return dropdownContainer.getSize(); }

const sf::Color& DropdownMenu::getContainerOutlineColor() const { return dropdownContainer.getOutlineColor(); }

const float DropdownMenu::getContainerOutlineThickness() const { return dropdownContainer.getOutlineThickness(); }

const sf::Vector2f& DropdownMenu::getCurrentItemSize() const { return currentItem.getSize(); }

const sf::Color& DropdownMenu::getCurrentItemFillColor() const { return currentItem.getFillColor(); }

const sf::Color& DropdownMenu::getCurrentItemHoverColor() const { return currentItem.getHoverColor(); }

const sf::Color& DropdownMenu::getCurrentItemTextColor() const { return currentItem.getTextColor(); }

unsigned DropdownMenu::getCurrentItemTextSize() const { return currentItem.getCharacterSize(); }

const sf::String& DropdownMenu::getCurrentItemText() const { return currentItem.getText(); }

const sf::Color& DropdownMenu::getCurrentItemOutlineColor() const { return currentItem.getOutlineColor(); }

float DropdownMenu::getCurrentItemOutlineThickness() const { return currentItem.getOutlineThickness(); }

const sf::Vector2f& DropdownMenu::getButtonSize() const { return currentItem.getSize(); }

sf::Color DropdownMenu::getButtonFillColor() const
{
	// Handles case where menu item is empty
	if (menuItems.empty())
		return sf::Color::Transparent;
	else
		return menuItems.at(0).getFillColor();
}

sf::Color DropdownMenu::getButtonHoverColor() const
{
	// Handles case where menu item is empty
	if (menuItems.empty())
		return sf::Color::Transparent;
	else
		return menuItems.at(0).getHoverColor();
}

sf::Color DropdownMenu::getButtonTextColor() const
{
	// Handles case where menu item is empty
	if (menuItems.empty())
		return sf::Color::Transparent;
	else
		return menuItems.at(0).getFillColor();
}

unsigned DropdownMenu::getButtonTextSize() const
{
	// Handles case where menu item is empty
	if (menuItems.empty())
		return 0;
	else
		return menuItems.at(0).getCharacterSize();
}

const sf::Font* DropdownMenu::getFont() const { return currentItem.getFont(); }

const sf::Vector2f& DropdownMenu::getPosition() const { return currentItem.getPosition(); }

sf::FloatRect DropdownMenu::getGlobalBounds() const { return currentItem.getGlobalBounds(); }

unsigned DropdownMenu::getNumItems() const { return menuItems.size(); }

void DropdownMenu::setPadding(float padding) { currentItemDropdownPadding = padding; }

void DropdownMenu::setContainerOutlineColor(const sf::Color& color) { dropdownContainer.setOutlineColor(color); }

void DropdownMenu::setContainerOutlineThickness(float thickness) { dropdownContainer.setOutlineThickness(thickness); }

void DropdownMenu::setFont(const sf::Font& font)
{
	// Set font for every button
	currentItem.setFont(font);
	for (TextButton& b : menuItems)
		b.setFont(font);
}

void DropdownMenu::setCurrentItemSize(const sf::Vector2f& size)
{
	currentItem.setSize(size);
	positionContainer();
	positionButtons();
}

void DropdownMenu::setCurrentItemFillColor(const sf::Color& color) { currentItem.setFillColor(color); }

void DropdownMenu::setCurrentItemHoverColor(const sf::Color& color) { currentItem.setHoverColor(color); }

void DropdownMenu::setCurrentItemTextColor(const sf::Color& color) { currentItem.setTextColor(color); }

void DropdownMenu::setCurrentItemTextSize(unsigned size) { currentItem.setCharacterSize(size); }

void DropdownMenu::setCurrentItemText(const sf::String& text) { currentItem.setText(text); }

void DropdownMenu::setCurrentItemOutlineColor(const sf::Color& color) { currentItem.setOutlineColor(color); }

void DropdownMenu::setCurrentItemOutlineThickness(float thickness) { currentItem.setOutlineThickness(thickness); }

void DropdownMenu::setButtonSize(const sf::Vector2f& size)
{
	buttonSize = size;
	resizeButton();
}

void DropdownMenu::setButtonFillColor(const sf::Color& color)
{
	// Sets fill color for each button
	for (TextButton& b : menuItems)
		b.setFillColor(color);
}

void DropdownMenu::setButtonHoverColor(const sf::Color& color)
{
	// Sets hover color for each button
	for (TextButton& b : menuItems)
		b.setHoverColor(color);
}

void DropdownMenu::setButtonTextColor(const sf::Color& color)
{
	// Set color for every button
	for (TextButton& b : menuItems)
		b.setTextColor(color);
}

void DropdownMenu::setButtonTextSize(unsigned size)
{
	// Set character size for text in every button
	for (TextButton& b : menuItems)
		b.setCharacterSize(size);
}

void DropdownMenu::setPosition(const sf::Vector2f& position)
{
	// Moving dropdown container then the items
	currentItem.setPosition(position);
	positionContainer();
	positionButtons();
}

TextButton& DropdownMenu::getButton(unsigned position)
{
	assert(position >= 0 && position < menuItems.size() && "Button does not exist.");
	return menuItems.at(position);
}

void DropdownMenu::addMenuItem(const sf::String& menuItem)
{
	menuItems.emplace_back(buttonSize, menuItem);

	// Setting font of added menu item
	if (menuItems.size() == 1)
		menuItems.at(menuItems.size() - 1).setFont(*currentItem.getFont());
	else
		menuItems.at(menuItems.size() - 1).setFont(*menuItems.at(0).getFont());
	resizeContainer();
	positionContainer();
	positionButtons();
}

void DropdownMenu::removeMenuItem(const sf::String& menuItem)
{
	std::vector<TextButton>::iterator it = find(menuItem);

	// Removes menu item if it exists
	if (it != menuItems.end())
	{
		menuItems.erase(it);
		resizeContainer();
	}
}

void DropdownMenu::swapMenuItem(const sf::String& menuItem, unsigned targetPosition)
{
	// Checks if target position of swap is valid
	if (targetPosition < 0 || targetPosition >= menuItems.size())
		return;

	std::vector<TextButton>::iterator it = find(menuItem);

	// Swaps target menu item if it exists
	if (it != menuItems.end())
		std::swap(*it, *getTargetPosition(targetPosition));
}

void DropdownMenu::eventHandler(const sf::RenderWindow& window, sf::Event event)
{
	currentItem.eventHandler(window, event);

	// Handles button events only if dropdown menu is visible
	if (!checkState(HIDDEN))
	{
		// Handling events for all buttons
		for (TextButton& b : menuItems)
			b.eventHandler(window, event);
	}

	// Handles dropping down the menu
	if (MouseEvents::mouseClicked(currentItem.getGlobalBounds(), window))
		toggleState(HIDDEN);
	else if (MouseEvents::mouseClickedElsewhere(currentItem.getGlobalBounds(), window))
		enableState(HIDDEN);
}

void DropdownMenu::update()
{
	currentItem.update();

	// Handles updating buttons only if dropdown menu is visible
	if (!checkState(HIDDEN))
	{
		// Handling events for all buttons
		for (TextButton& b : menuItems)
			b.update();
	}

	// Handles updating dropdown menu if any buttons were pressed
	for (TextButton& item : menuItems)
	{
		if (item.checkState(PRESSED))
		{
			setCurrentItemText(item.getText());
			item.disableState(PRESSED);
		}
	}
}

void DropdownMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(currentItem);
	if (!checkState(HIDDEN))
	{
		target.draw(dropdownContainer);
		HelperFunctions::drawVector(target, menuItems);
	}
}

void DropdownMenu::resizeButton()
{
	// Resizing each button then the container
	currentItem.setSize(buttonSize);
	for (TextButton& b : menuItems)
		b.setSize(buttonSize);
	resizeContainer();
}

void DropdownMenu::resizeContainer()
{
	// Resizes dropdown menu container to be able to contain the number of menu items
	dropdownContainer.setSize({ buttonSize.x, buttonSize.y * menuItems.size() });
	positionContainer();
	positionButtons();
}

void DropdownMenu::positionButtons()
{
	// Handles case where no menu items exist
	if (!menuItems.empty())
	{
		// Position first menu item into container
		menuItems.at(0).setPosition(dropdownContainer.getPosition());

		// Positioning menu items inside dropdown container
		for (unsigned i = 1; i < menuItems.size(); ++i)
			Position::down(menuItems.at(i - 1), menuItems.at(i));
	}
}

void DropdownMenu::positionContainer() 
{
	Position::down(currentItem, dropdownContainer, currentItemDropdownPadding);
	Position::centerX(currentItem, dropdownContainer);
}

std::vector<TextButton>::iterator DropdownMenu::find(const sf::String& menuItem)
{
	// Linear search through menuItems for the given menu item
	std::vector<TextButton>::iterator it = menuItems.begin();
	while (it != menuItems.end())
	{
		// Returns iterator to the menu item if it exists
		if ((*it).getText() == menuItem)
			break;
		++it;
	}
	return it;
}

std::vector<TextButton>::iterator DropdownMenu::getTargetPosition(unsigned target)
{
	// Moving iterator to target position
	std::vector<TextButton>::iterator it = menuItems.begin();
	for (unsigned i = 0; i < target; ++i)
		++it;
	return it;
}
