#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Player.h"
#include "Sound.h"
#include "Notesheet.h"
#include "util.h"
#include "MultModul.h"
#include "Mixer.h"
#include "NoiseGen.h"
#include "PickedString.h"
#include "Instrument.h"

     

using namespace std;



int main(int argc, char* argv[])
{
  
  if(argc < 2)
    error("no infile!");  
  Player play;

 
  Notesheet notes;
  cout << "noten ok? " << notes.loadFile(argv[1]) << endl;
  sort(notes.begin(), notes.end(), Note::samplecmp);

  
 



  Sound output;


  /*
  Note a;
  a.freq = 440;
  a.length_time= 4;
  a.length_sample= 44100* a.length_time;
  PickedString ss(a);

  
  while(!ss.isDone())
    {
      ss.tick();
      output.samples.push_back(ss.output);
      
    }
  */



  
  
  Instrument guitar;
  
  Notesheet::iterator note_it = notes.begin();
  
  for (unsigned long sample_now = 0; sample_now < notes.back().on_sample; ++sample_now)
    {
      guitar.tick(); //play...
   
      //  we are not at the end yet
      if(note_it != notes.end())
	{
	  while((*note_it).on_sample == sample_now)//current note is NOW
	    {
	      PickedString *s = new PickedString(*note_it); // so add it to intrument
	      guitar.add(s);

	      ++note_it; // maybe another note NOW?
	    }
	}
	
      output.samples.push_back(guitar.output);
    }
  

  output.saveFile("out.aum");
 
  
  

  return EXIT_SUCCESS;
}     
  



