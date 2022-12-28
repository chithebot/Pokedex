#ifndef SFML_GUI_PROJECT_IMAGES_H
#define SFML_GUI_PROJECT_IMAGES_H

#include <string>
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include "ImageNotFoundException.h"

class Images
{
public:
	static sf::Texture& get(const std::string& imagePath) noexcept(false);
private:
	static void load(const std::string& imagePath) noexcept(false);
private:
	static std::unordered_map<std::string, sf::Texture*> images;
};

#endif // SFML_GUI_PROJECT_IMAGES_H
