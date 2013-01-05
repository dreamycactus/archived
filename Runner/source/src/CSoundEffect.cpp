#include "../include/CSoundEffect.h"

using std::string;

void CSoundEffect::Cleanup()
{
	Mix_FreeChunk(effect);
}

void CSoundEffect::SetVolume(int volume)
{
	Mix_VolumeChunk(effect, volume);
}

void CSoundEffect::Play(int loop)
{
	channel = Mix_PlayChannel(-1, effect, loop);
}
bool CSoundEffect::IsPlaying()
{
    return Mix_Playing(channel);
}
void CSoundEffect::load_sound(string file)
{
	effect = Mix_LoadWAV(file.c_str());
}

void CSoundEffect::Stop()
{
    Mix_HaltChannel(channel);
}

