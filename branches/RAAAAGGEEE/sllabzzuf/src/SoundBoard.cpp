#import "SoundBoard.h"
#include <iostream>

SoundBoard::SoundBoard(){
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    dash = Mix_LoadWAV( "sound/dash.wav" );
}
SoundBoard::~SoundBoard(){
    if(dash!=NULL)
    Mix_FreeChunk( dash );
    Mix_CloseAudio();
}
void SoundBoard::playEffect(){
    std::cout << "playEffect called.\n";
 Mix_PlayChannel( -1, dash, 0 );
}
void SoundBoard::setMusic(int music){
    switch(music){
    default:
    break;
    }
}
