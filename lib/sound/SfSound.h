#ifndef SFSOUND_H
# define SFSOUND_H

# include <map>
# include <string>
# include <SFML/Audio.hpp>
# include "ISound.h"

class SfSound : public ISound
{
	public:
		SfSound();
		~SfSound();

		void			init() override;
		void			close() override;
		void			play(ISound::FX) override;
		void			pause(ISound::FX) override;
		void			stop(ISound::FX) override;

	private:
		std::map<ISound::FX, sf::SoundBuffer>	_SoundBuffers;
		sf::Music								_Music;
		std::map<ISound::FX, sf::Sound>			_Sounds;
		std::map<ISound::FX, std::string>		_SoundFiles;
		bool									_DisableMusic;
};

#endif
