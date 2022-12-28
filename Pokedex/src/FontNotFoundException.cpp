#include "FontNotFoundException.h"

FontNotFoundException::FontNotFoundException() : FontNotFoundException("Could not load the font.") { }

FontNotFoundException::FontNotFoundException(const std::string& message) : message(message) { }

const char* FontNotFoundException::what() noexcept { return message.c_str(); }
