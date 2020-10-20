#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <deque>

typedef std::vector<double> snddata;

const double SMPLRATE=44100;


class Sound
{
 public:
  snddata samples;
  bool stereo;

  Sound(size_t sz=0)
    {
      samples.resize(sz);
      stereo = false;
    }


  int loadFile(const char* path);
  int saveFile(const char* path);
  int dumpTxt(const char * path);


  void normalize();
  void cutoff();

  double getMaxAmp();
  

  Sound filtX(int cpos, double cfact);
  Sound filtY(int d1pos, double d1fact, int d2pos, double d2fact);

  Sound envf();


  Sound& operator+=(const Sound&);
  const Sound operator+(const Sound&);

  Sound& operator*=(const Sound&);
  const Sound operator*(const Sound&);
  const Sound operator*(const double a);

};




Sound mkStereo(Sound left, Sound right);





class Ringbuf : protected std::deque<double>
{
  size_t maxsize;
 
 public:
  Ringbuf(size_t sz)
    {
      maxsize = sz;
    }

  void add(double d)
    {
      if(size() < maxsize)
	 push_back(d);
      else
	{
	  pop_front();
	  push_back(d);
	}
    }

  double getAvg()
    {
      double sum = 0;
      for(std::deque<double>::iterator it = begin(); it != end(); ++ it)
	sum += *it;
      
      return size() ? sum/size() : 0;
    }

};


#endif
