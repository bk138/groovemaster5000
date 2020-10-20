#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Player.h"



using namespace std;


long offset; 

static void audio_callback(void* userdata, Uint8* buffer, int len)
{
  Sint16* bufmask = reinterpret_cast<Sint16*>(buffer);
  double* mydata = static_cast<double*>(userdata);

  // shift data over to audio buffer
  for(int i = 0; i < len /2; i++)
    bufmask[i] = static_cast<Sint16>(mydata[i + offset]) ;
  
  offset += len/2; 
}



Player::Player()
{
  if(SDL_Init(SDL_INIT_AUDIO) == -1)
    {
      cerr << "error opening audio!\n";
      return;
    }
 
  atexit(SDL_Quit);

  spec.freq   = (int)SMPLRATE; // samplerate 
  spec.format = AUDIO_S16SYS;
  spec.samples = 8192; // buffersize 
  spec.callback = audio_callback;

}






void Player::operator<<(const Sound& snd)
{
  cout << "play started\n";

  offset = 0;
  long nr_samples = snd.samples.size();

  // erstma so
  double *data = new double[nr_samples];
  for(long i = 0; i < nr_samples; ++i)
    data[i] = snd.samples[i] * 32000;
  
  spec.userdata = data;

  if(snd.stereo)
    spec.channels = 2;
  else
    spec.channels = 1;

  SDL_OpenAudio(&spec, 0);
  SDL_PauseAudio(0);        

  SDL_Delay(((nr_samples/spec.channels) / (int)SMPLRATE) * 1000);

  SDL_PauseAudio(1);  
  SDL_CloseAudio();

  delete[] data;

  cout << "play ended\n";
}
