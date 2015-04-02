#ifndef ISOUND_H
# define ISOUND_H

class ISound
{
	public:
		enum FX
		{
			FRUIT1, FRUIT2, FRUIT3, FRUIT4,	// Sound effects when eating fruits
			MUSIC,
			GAMEOVER,
			LEVELUP
		};

		virtual ~ISound() {};

		virtual void	init() = 0;
		virtual void	close() =0;
		virtual void	play(ISound::FX) =0;
		virtual void	pause(ISound::FX) =0;
		virtual void	stop(ISound::FX) =0;
};

#endif
