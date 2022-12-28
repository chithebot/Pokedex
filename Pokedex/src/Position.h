#ifndef SFML_GUI_PROJECT_POSITION_H
#define SFML_GUI_PROJECT_POSITION_H

#include <SFML\Graphics.hpp>
#include <cmath>

class Position
{
public:
	template <typename T, typename S>
	static void left(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void right(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void up(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void down(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void upperLeft(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void upperRight(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void bottomLeft(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void bottomRight(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void centerX(const T& obj1, S& obj2);

	template <typename T, typename S>
	static void centerY(const T& obj1, S& obj2);

	template <typename T, typename S>
	static void centerObject(const T& obj1, S& obj2);

	template <typename T>
	static void centerText(const T& obj, sf::Text& text);

	template <typename T, typename S>
	static void leftOnly(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void rightOnly(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void upOnly(const T& obj1, S& obj2, float spacing = 0.f);

	template <typename T, typename S>
	static void downOnly(const T& obj1, S& obj2, float spacing = 0.f);
};

#include "Position.cpp"

#endif // SFML_GUI_PROJECT_POSITION_H
