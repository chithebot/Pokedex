#include "Cursor.h"

sf::Cursor Cursor::cursor;

const sf::Cursor& Cursor::getCursor() { return cursor; }

bool Cursor::loadFromPixels(const sf::Uint8* pixels, const sf::Vector2u& size, const sf::Vector2u& hotspot) { return cursor.loadFromPixels(pixels, size, hotspot); }

bool Cursor::loadFromSystem(sf::Cursor::Type type) { return cursor.loadFromSystem(type); }
