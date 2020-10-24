#include <cmath>
#include "Sound.h"
#include "PickedString.h"

#include <iostream>


PickedString::PickedString(const Note& n)
{
  done = false;
  ticks = 0;
  output = 0;
  samples = n.length_sample;

  int delaylength = (int) (SMPLRATE / n.freq);
  double delayrem = fmod(SMPLRATE, n.freq) / n.freq;
  double damp = 0.0015 * (1 / n.length_time);


  // noise
  noise.init(delaylength);

  // delay line
  delay_p.push_back(delaylength-1); 
  delay_p.push_back(delaylength-2);

  delay_w.push_back(delayrem);
  delay_w.push_back(1 - delayrem);

  delayline.init(delaylength, &delay_p, &delay_w);

  // lowpass
  lowpass_p.push_back(0);
  lowpass_p.push_back(1);

  lowpass_w.push_back(0.5 - damp);
  lowpass_w.push_back(0.5);
  lowpass.init(1, &lowpass_p, &lowpass_w);
  

  // mixer
  mix_in.push_back( &noise.output);
  mix_in.push_back( &lowpass.output);

  mix_w.push_back(1);
  mix_w.push_back(0.999);
  
  mix.init(&mix_in, &mix_w);

   
 
  delayline.setInput(&mix.output);
  lowpass.setInput(&delayline.output);

}




void PickedString::tick()
{
  ++ticks;

  if(ticks > samples)
    done = true;

  noise.next();
  mix.next();
  delayline.next();
  lowpass.next();

  output = delayline.output;
}



bool PickedString::isDone()
{
  return done;
}

void *new_pickedstring(Note *note) {
    return new PickedString(*note);
}

int pickedstring_is_done(void *pickedstring) {
    PickedString *ps = static_cast<PickedString*>(pickedstring);
    return ps->isDone();
}

void pickedstring_tick(void *pickedstring) {
    PickedString *ps = static_cast<PickedString*>(pickedstring);
    ps->tick();
}

double pickedstring_get_output(void *pickedstring) {
    PickedString *ps = static_cast<PickedString*>(pickedstring);
    return ps->output;
}
