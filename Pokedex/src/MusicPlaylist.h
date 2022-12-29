#ifndef SFML_GUI_PROJECT_MUSIC_PLAYLIST_H
#define SFML_GUI_PROJECT_MUSIC_PLAYLIST_H

#include <SFML\Audio\Music.hpp>
#include <SFML\Graphics.hpp>
#include <algorithm>
#include <exception>
#include <vector>
#include <string>

class MusicPlaylist
{
public:
	MusicPlaylist() noexcept;
	MusicPlaylist(const std::string& musicFolderPath) noexcept;
	const std::string& getMusicFolderPath() const noexcept;
	const std::string& getCurrentSong() const noexcept(false);
	void setMusicFolderPath(const std::string& path) noexcept;
	void setCurrentSong(unsigned trackNumber)  noexcept;
	void load() noexcept;
	void play() noexcept;
	void pause() noexcept;
	void stop() noexcept;
	void pushTrack(const std::string& path) noexcept;
	void eraseTrack(const std::string& path) noexcept;
	void popTrack() noexcept;
	void setVolume(float volume) noexcept;
	void eventHandler(const sf::RenderWindow& window, sf::Event event) noexcept;
private:
	sf::Music music;
	std::vector<std::string> musicPath;
	std::string musicFolderPath;
	unsigned currentSong;
};

#endif // SFML_GUI_PROJECT_MUSIC_PLAYLIST_H
