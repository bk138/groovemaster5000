#include <cstdlib>
#include "NoiseGen.h"
    
using namespace std;



void NoiseGen::init(int l)	
    {
      output = 0;
      counter = l;	
    }



void NoiseGen::next()
{
  if(counter == 0) 
    output = 0;
  else 
    {
      --counter;
      output = ( (double) (-32768+(rand() % ( 65536- 1+ 1 ))))/32768;
    }
}
	
