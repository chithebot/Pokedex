#include "PokemonNotFoundException.h"

PokemonNotFoundException::PokemonNotFoundException() : PokemonNotFoundException("Pokemon does not exist.") { }

PokemonNotFoundException::PokemonNotFoundException(const std::string& message) : message(message) { }

const char* PokemonNotFoundException::what() noexcept { return message.c_str(); }
