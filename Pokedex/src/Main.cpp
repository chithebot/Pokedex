#include "MusicPlaylist.h"
#include "Pokedex.h"

//#ifndef SFML_GUI_PROJECT_
//#define SFML_GUI_PROJECT_

//#endif // SFML_GUI_PROJECT_

int main()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	Pokedex p({ 1920, 1080 });
	p.run();
}
