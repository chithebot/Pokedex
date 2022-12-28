#include <SFML\Audio\Music.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>

class MusicPlaylist
{
public:
	MusicPlaylist();
	MusicPlaylist(const std::string& musicFolderPath);
	const std::string& getMusicFolderPath() const;
	const std::string& getCurrentSong() const;
	void setMusicFolderPath(const std::string& path);
	void setCurrentSong(unsigned trackNumber);
	void load();
	void play();
	void pause();
	void stop();
	void pushTrack(const std::string& path);
	void popTrack();
	void setVolume(float volume);
	void eventHandler(const sf::RenderWindow& window, sf::Event event);
private:
	sf::Music music;
	std::vector<std::string> musicPath;
	std::string musicFolderPath;
	unsigned currentSong;
};

