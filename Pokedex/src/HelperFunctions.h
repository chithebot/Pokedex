#ifndef SFML_GUI_PROJECT_HELPER_FUNCTIONS_H
#define SFML_GUI_PROJECT_HELPER_FUNCTIONS_H

#include <vector>
#include <SFML\Graphics.hpp>

class HelperFunctions
{
public:
	template <typename T>
	static void drawVector(sf::RenderTarget& target, const std::vector<T>& drawableVector);
};

#include "HelperFunctions.cpp"

#endif // SFML_GUI_PROJECT_HELPER_FUNCTIONS_H
