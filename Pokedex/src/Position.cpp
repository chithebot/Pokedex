#ifndef SFML_GUI_PROJECT_POSITION_CPP
#define SFML_GUI_PROJECT_POSITION_CPP

#include "Position.h"

template <typename T, typename S>
void Position::left(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left - obj2Rect.width - spacing, obj1Rect.top });
}

template <typename T, typename S>
void Position::right(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left + obj1Rect.width + spacing, obj1Rect.top });
}

template <typename T, typename S>
void Position::up(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left, obj1Rect.top - obj2Rect.height - spacing });
}

template <typename T, typename S>
void Position::down(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left, obj1Rect.top + obj1Rect.height + spacing });
}

template <typename T, typename S>
void Position::upperLeft(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left + spacing, obj1Rect.top + spacing });
}

template <typename T, typename S>
void Position::upperRight(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left + obj1Rect.width - obj2Rect.width - spacing, obj1Rect.top + spacing});
}

template <typename T, typename S>
void Position::bottomLeft(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left + spacing, obj1Rect.top + obj1Rect.height - obj2Rect.height - spacing });
}

template <typename T, typename S>
void Position::bottomRight(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left + obj1Rect.width - obj2Rect.width - spacing, obj1Rect.top + obj1Rect.height - obj2Rect.height - spacing });
}

template <typename T, typename S>
void Position::centerX(const T& obj1, S& obj2)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left + obj1Rect.width / 2 - obj2Rect.width / 2, obj2.getPosition().y });
}

template <typename T, typename S>
void Position::centerY(const T& obj1, S& obj2)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj2.getPosition().x, obj1Rect.top + obj1Rect.height / 2 - obj2Rect.height / 2 });
}

template <typename T, typename S>
void Position::centerObject(const T& obj1, S& obj2)
{
	Position::centerX(obj1, obj2);
	Position::centerY(obj1, obj2);
}

template<class T>
void Position::centerText(const T& obj, sf::Text& text)
{
	sf::FloatRect textRect = text.getGlobalBounds();
	sf::FloatRect objRect = obj.getGlobalBounds();
	sf::Vector2f center = { textRect.width / 2.f, textRect.height / 2.f };
	sf::Vector2f localBounds = { center.x + text.getLocalBounds().left, center.y + text.getLocalBounds().top };
	sf::Vector2f rounded = { std::round(localBounds.x), std::round(localBounds.y) };
	text.setOrigin(rounded);
	text.setPosition({ objRect.left + objRect.width / 2.f, objRect.top + objRect.height / 2.f });
}

template <typename T, typename S>
void Position::leftOnly(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left - obj2Rect.width - spacing, obj2.getPosition().y });
}

template <typename T, typename S>
void Position::rightOnly(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj1Rect.left + obj1Rect.width + spacing, obj2.getPosition().y });
}

template <typename T, typename S>
void Position::upOnly(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj2.getPosition().x, obj1Rect.top - obj2Rect.height - spacing});
}

template <typename T, typename S>
void Position::downOnly(const T& obj1, S& obj2, float spacing)
{
	sf::FloatRect obj1Rect = obj1.getGlobalBounds();
	sf::FloatRect obj2Rect = obj2.getGlobalBounds();
	obj2.setPosition({ obj2.getPosition().x, obj1Rect.top + obj1Rect.height + spacing });
}

#endif // SFML_GUI_PROJECT_POSITION_CPP
