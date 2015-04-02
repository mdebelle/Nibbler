#include "SfSound.h"
#include <iostream>

SfSound::SfSound() : _DisableMusic(false)
{
	_SoundFiles[ISound::FRUIT1] = "lib/sound/fruit.flac";
	_SoundFiles[ISound::FRUIT2] = "lib/sound/fruit2.wav";
	_SoundFiles[ISound::FRUIT3] = "lib/sound/fruit3.wav";
	_SoundFiles[ISound::FRUIT4] = "lib/sound/fruit4.wav";
	_SoundFiles[ISound::MUSIC] = "lib/sound/music.wav";
	_SoundFiles[ISound::GAMEOVER] = "lib/sound/gameover.wav";
	_SoundFiles[ISound::LEVELUP] = "lib/sound/levelup.wav";
	return ;
}

SfSound::~SfSound()
{
	return ;
}

void	SfSound::init()
{
	for (const auto& sound : _SoundFiles)
	{
		if (sound.first != ISound::MUSIC && _SoundBuffers[sound.first].loadFromFile(sound.second))
			_Sounds[sound.first].setBuffer(_SoundBuffers[sound.first]);
	}
	if (!_Music.openFromFile(_SoundFiles[ISound::MUSIC]))
		_DisableMusic = true;
	else
	{
		_Music.setLoop(true);
		_Music.setVolume(10);
	}
	try { _Sounds.at(ISound::GAMEOVER).setVolume(40); }
	catch(std::exception& ex) {}
	try { _Sounds.at(ISound::LEVELUP).setVolume(50); }
	catch(std::exception& ex) {}
	try { _Sounds.at(ISound::FRUIT2).setVolume(50); }
	catch(std::exception& ex) {}
	try { _Sounds.at(ISound::FRUIT3).setVolume(50); }
	catch(std::exception& ex) {}
}

void	SfSound::close()
{}

void	SfSound::play(ISound::FX snd)
{
	if (snd == ISound::MUSIC && !_DisableMusic)
	{
		_Music.play();
	}
	else
	{
		try { _Sounds.at(snd).play(); }
		catch(std::exception& ex) {
			std::cerr << "Failed to play sound " << _SoundFiles[snd] << std::endl;
		}
	}
}

void	SfSound::pause(ISound::FX snd)
{
	if (snd == ISound::MUSIC && !_DisableMusic)
		_Music.pause();
	else
	{
		try { _Sounds.at(snd).pause(); }
		catch(std::exception& ex) {
		
		}
	}
}

void	SfSound::stop(ISound::FX snd)
{
	if (snd == ISound::MUSIC && !_DisableMusic)
		_Music.stop();
	else
	{
		try { _Sounds.at(snd).stop(); }
		catch(std::exception& ex) {
		
		}
	}
}
