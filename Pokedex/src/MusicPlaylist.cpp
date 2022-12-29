#include "MusicPlaylist.h"

MusicPlaylist::MusicPlaylist() noexcept : MusicPlaylist(std::string()) { }

MusicPlaylist::MusicPlaylist(const std::string& musicFolderPath) noexcept
	: musicFolderPath(musicFolderPath), currentSong(0) 
{
	music.setLoop(false);
}

const std::string& MusicPlaylist::getMusicFolderPath() const noexcept
{
	return musicFolderPath;
}

const std::string& MusicPlaylist::getCurrentSong() const noexcept(false)
{
	// Gets the current song if playlist not empty
	if (!musicPath.empty())
		return musicPath.at(currentSong);
	throw std::out_of_range("Song does not exist in playlist.");
}

void MusicPlaylist::setMusicFolderPath(const std::string& path) noexcept
{ 
	musicFolderPath = path; 
}

void MusicPlaylist::setCurrentSong(unsigned trackNumber) noexcept
{
	// Sets song to the current song
	if (trackNumber < musicPath.size())
	{
		music.stop();
		currentSong = trackNumber;
	}
}

void MusicPlaylist::load() noexcept
{ 
	music.openFromFile(musicFolderPath + musicPath.at(currentSong));
}

void MusicPlaylist::play() noexcept
{ 
	music.play();
}

void MusicPlaylist::pause() noexcept
{ 
	music.pause();
}

void MusicPlaylist::stop() noexcept
{ 
	music.stop();
}

void MusicPlaylist::pushTrack(const std::string& path) noexcept
{ 
	musicPath.push_back(path);
}

void MusicPlaylist::eraseTrack(const std::string& path) noexcept
{
	// Finds the track in the playlist
	std::vector<std::string>::iterator target = std::find(musicPath.begin(), musicPath.end(), path);

	// Removes if the track exists in the playlist
	if (target != musicPath.end())
		musicPath.erase(target);
}

void MusicPlaylist::popTrack() noexcept
{
	// Pops only if track list is non-empty
	if (!musicPath.empty())
		musicPath.pop_back();
}

void MusicPlaylist::setVolume(float volume) noexcept
{
	music.setVolume(volume);
}

void MusicPlaylist::eventHandler(const sf::RenderWindow& window, sf::Event event) noexcept
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
