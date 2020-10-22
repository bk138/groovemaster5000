#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "Sound.h"
#include "Notesheet.h"


using namespace std;

const char COMMENT = ';';

int Notesheet::loadFile(const char* path)
{
  ifstream file(path);
 
  if(!file)
    return 0;

  string buf;
  Note n;
  
  // split into lines
  while(getline(file, buf))
  {
    // weed out comments
    stringstream tmp(buf);
    getline(tmp, buf, COMMENT);
  
    tmp.clear(); 
    tmp.str(buf);
	
    // extract values
    int val_nr = 0;
    while(tmp >> buf && val_nr < 4)
      {
	stringstream val(buf); //put it in here for easy conversion 
	switch(val_nr)
	  {
	  case 0:
	    val >> n.on_time;
	    break;
	  case 1:
	    val >> n.length_time;
	    break;
	  case 2:
	    val >> n.note;
	    break;
	  case 3:
	    val >> n.loudness;
	    break;
	  }

	++val_nr;
      }

    if(val_nr > 0 && val_nr < 4) // some, but not enough values
      return 0;

    if(val_nr >= 4)// all well
      {
	n.on_sample = (unsigned long) (n.on_time * SMPLRATE);
	n.length_sample = (unsigned int) (n.length_time * SMPLRATE);
	n.freq = pow(1.0594, n.note - 69)*440;
	push_back(n); 
      }
 }

  
  return 1;
}


void* new_notesheet() {
    return new Notesheet;
}

int notesheet_load_file(void *notesheet, const char *path) {
    Notesheet* ns = static_cast<Notesheet*>(notesheet);
    return ns->loadFile(path);
}
