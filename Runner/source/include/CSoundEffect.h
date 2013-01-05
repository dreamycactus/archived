#ifndef CSOUNDEFFECT_H
#define CSOUNDEFFECT_H

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

using std::string;

class CSoundEffect
{
public:
    CSoundEffect() { effect = 0; channel = 0; }
    CSoundEffect(string file) { load_sound(file); channel = 0; }
	void load_sound(string file);
	void Play(int loop = 0);
	void Stop();
	void Cleanup();//Be sure to run this before closing SDL
	void SetVolume(int volume);
	bool IsPlaying();

private:
	Mix_Chunk *effect;
	int channel;
};

#endif // CSOUNDEFFECT_H
