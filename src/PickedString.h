#ifndef PICKEDSTRING_H
#define PICKEDSTRING_H

#include "Notesheet.h"
#include "NoiseGen.h"
#include "MultModul.h"
#include "Mixer.h"




class PickedString
{
  // the inner devices
  NoiseGen noise;
  MultiModul delayline;  
  MultiModul lowpass;
  Mixer mix;

  unsigned long ticks;
  unsigned long samples;
  
  bool done;
  
 public:
  /*
    here you can turn the screws
  */
  // delay line
  vector<int>  delay_p; 
  vector<double> delay_w;

  // lowpass
  vector<int>  lowpass_p; 
  vector<double> lowpass_w;

  // mixer
  vector<double*>  mix_in;
  vector<double> mix_w;

  PickedString(const Note& n);

  double output;

  void tick();
  
  bool isDone();
};

extern "C" {
    void *new_pickedstring(Note *note);
    int pickedstring_is_done(void *pickedstring);
    void pickedstring_tick(void* pickedstring);
    double pickedstring_get_output(void* pickedstring);
}


#endif
