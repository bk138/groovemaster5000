
#include "Instrument.h"


void Instrument::add(PickedString* part)
{
  push_back(part);
}


void Instrument::tick()
{
  output = 0;

  // first clean up
  Instrument::iterator c = begin();
  while(c != end())
    {
      if((**c).isDone())
	{
	  delete *c;
	  c = erase(c);
	}
      else
	++c;
    }
  
  // then play our parts
  for(Instrument::iterator it = begin(); it != end(); ++it)
    {
      (**it).tick(); 
      output += (**it).output;
     }

  output = output / size();
}
