#ifndef SFML_GUI_PROJECT_POKEMON_NOT_FOUND_EXCEPTION_H
#define SFML_GUI_PROJECT_POKEMON_NOT_FOUND_EXCEPTION_H

#include <exception>
#include <string>

class PokemonNotFoundException : public std::exception
{
public:
	PokemonNotFoundException();
	PokemonNotFoundException(const std::string& message);
	const char* what() noexcept;
private:
	std::string message;
};

#endif // SFML_GUI_PROJECT_POKEMON_NOT_FOUND_EXCEPTION_H
