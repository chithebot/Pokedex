#include "Images.h"

std::unordered_map<std::string, sf::Texture*> Images::images;

sf::Texture& Images::get(const std::string& imagePath) noexcept(false)
{
	load(imagePath);
	return *(images.at(imagePath));
}

void Images::load(const std::string& imagePath) noexcept(false)
{
	// Checking if path actually exists within map
	if (images.count(imagePath) == 0)
	{
		sf::Texture* t_ptr = new sf::Texture();

		// Loading image into a texture map
		if (!t_ptr->loadFromFile(imagePath))
		{
			delete t_ptr;
			throw ImageNotFoundException("Could not load " + imagePath);
		}
		else
		{
			images.insert({ imagePath, t_ptr });
		}
	}
}
