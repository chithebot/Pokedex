#include "KeyShortcuts.h"

bool KeyShortcuts::ctrlPressed() 
{
	bool leftCtrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
	bool rightCtrl = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
	bool leftSys = sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem);
	bool rightSys = sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem);
	return (leftCtrl || rightCtrl || leftSys || rightSys);
}

bool KeyShortcuts::isUndo()
{
	return KeyShortcuts::ctrlPressed() && sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
}
