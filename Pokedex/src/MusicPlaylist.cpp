#include "MusicPlaylist.h"

MusicPlaylist::MusicPlaylist() : MusicPlaylist(std::string()) { }

MusicPlaylist::MusicPlaylist(const std::string& musicFolderPath)
	: musicFolderPath(musicFolderPath), currentSong(0) 
{
	music.setLoop(false);
}

const std::string& MusicPlaylist::getMusicFolderPath() const { return musicFolderPath; }

const std::string& MusicPlaylist::getCurrentSong() const 
{
	// Gets the current song if playlist not empty
	if (!musicPath.empty())
		return musicPath.at(currentSong);
}

void MusicPlaylist::setMusicFolderPath(const std::string& path) { musicFolderPath = path; }

void MusicPlaylist::setCurrentSong(unsigned trackNumber)
{
	// Sets song to the current song
	if (trackNumber < musicPath.size())
	{
		music.stop();
		currentSong = trackNumber;
	}
}

void MusicPlaylist::load() { music.openFromFile(musicFolderPath + musicPath.at(currentSong)); }

void MusicPlaylist::play() { music.play(); }

void MusicPlaylist::pause() { music.pause(); }

void MusicPlaylist::stop() { music.stop(); }

void MusicPlaylist::pushTrack(const std::string& path) { musicPath.push_back(path); }

void MusicPlaylist::popTrack() { musicPath.pop_back(); }

void MusicPlaylist::setVolume(float volume) { music.setVolume(volume); }

void MusicPlaylist::eventHandler(const sf::RenderWindow& window, sf::Event event)
{
	if (music.getStatus() == sf::SoundSource::Stopped)
	{
		if (currentSong == musicPath.size() - 1)
			currentSong = 0;
		else
			++currentSong;
		load();
		play();
	}
}
