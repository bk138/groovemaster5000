#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "Sound.h"

class Player
{
  
  SDL_AudioSpec spec;
  int volume;

 public:
  Player(); 

  void operator<<(const Sound&);

};


#endif
