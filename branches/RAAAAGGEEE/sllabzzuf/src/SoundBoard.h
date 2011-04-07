#ifndef SOUNDBOARD_H_INCLUDED
#define SOUNDBOARD_H_INCLUDED

#include "SDL/SDL_mixer.h"

#define JUMP 0
#define DASH 1
#define GRAVITY 2

class SoundBoard{
private:
    Mix_Chunk *dash;

int current_music;
bool introfinished;

public:
SoundBoard();
~SoundBoard();
void playEffect();
void setMusic(int music);

};

#endif // SOUNDBOARD_H_INCLUDED
