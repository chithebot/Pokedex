#ifndef SFML_GUI_PROJECT_IMAGE_NOT_FOUND_EXCEPTION_H
#define SFML_GUI_PROJECT_IMAGE_NOT_FOUND_EXCEPTION_H

#include <exception>
#include <string>

class ImageNotFoundException : public std::exception
{
public:
	ImageNotFoundException();
	ImageNotFoundException(const std::string& message);
	const char* what() noexcept;
private:
	std::string message;
};

#endif // SFML_GUI_PROJECT_IMAGE_NOT_FOUND_EXCEPTION_H
