#ifndef SFML_GUI_PROJECT_FONT_NOT_FOUND_EXCEPTION_H
#define SFML_GUI_PROJECT_FONT_NOT_FOUND_EXCEPTION_H

#include <exception>
#include <string>

class FontNotFoundException : public std::exception
{
public:
	FontNotFoundException();
	FontNotFoundException(const std::string& message);
	const char* what() noexcept;
private:
	std::string message;
};

#endif // SFML_GUI_PROJECT_FONT_NOT_FOUND_EXCEPTION_H
