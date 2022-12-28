#include "ImageNotFoundException.h"

ImageNotFoundException::ImageNotFoundException() : ImageNotFoundException("Could not load the image.") { }

ImageNotFoundException::ImageNotFoundException(const std::string& message) : message(message) { }

const char* ImageNotFoundException::what() noexcept { return message.c_str(); }
