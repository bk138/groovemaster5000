#include <iostream>

#include "util.h"



void error(const char* msg, const char* what)
{
  std::cerr << "ERROR: " << msg << " " << what << std::endl;
  exit(EXIT_FAILURE);
}



bool isBigEndian()
{
  short word =  0x0001;
  
  // look at first byte
  char *byte = reinterpret_cast<char*>(&word);

  return *byte ? false : true; 
}



short swapBytes2(short s)
{
  unsigned char tmp = s & 0xFF00;
  return (s << 8) + tmp;
}
