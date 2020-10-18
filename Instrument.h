#ifndef INSTRUMENT_H
#define INSTRUMENT_H


#include <list>


#include "PickedString.h"




class Instrument: public std::list<PickedString*>
{
 public:
  double output;

  void add(PickedString* part);
  void tick();




};



#endif

