#ifndef NOTES_H
#define NOTES_H

#include <vector>


struct Note
{
  double on_time;
  unsigned long on_sample;
  double length_time;
  unsigned int length_sample;
  int note;
  double freq;
  double loudness;

  static bool samplecmp(Note a, Note b)
  {
    return a.on_sample < b.on_sample;
  }   
};

         


class Notesheet: public std::vector<Note>
{
 public:
  int loadFile(const char* path);

};




#endif
