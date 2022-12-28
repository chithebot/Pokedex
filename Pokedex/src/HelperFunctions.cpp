#ifndef SFML_GUI_PROJECT_HELPER_FUNCTIONS_CPP
#define SFML_GUI_PROJECT_HELPER_FUNCTIONS_CPP

#include "HelperFunctions.h"

template <typename T>
void HelperFunctions::drawVector(sf::RenderTarget& target, const std::vector<T>& drawableVector)
{
	// Drawing each drawable object in the vector
	for (const T& drawable : drawableVector)
		target.draw(drawable);
}

#endif // SFML_GUI_PROJECT_HELPER_FUNCTIONS_CPP
