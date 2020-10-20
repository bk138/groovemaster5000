#include <fstream>
#include <cmath>
#include <algorithm>

#include "Sound.h"
#include "util.h"

using namespace std;


int Sound::loadFile(const char* path)
{
  ifstream file(path);
  if(!file)
    return 0;

  // get length 
  file.seekg (0, ios::end);
  int length = file.tellg();
  file.seekg (0, ios::beg);

  char *buffer = new char[length];

  // read all at once
  file.read(buffer,length);

  // check endianess and convert to big endian if needed
  bool bigEndian = isBigEndian();

  samples.clear();
  for(int i = 0; i < length/2; ++i)
    if(bigEndian)
      samples.push_back(swapBytes2(reinterpret_cast<short*>(buffer)[i]));
    else
      samples.push_back(reinterpret_cast<short*>(buffer)[i]);
  
  // normalize
  for(snddata::iterator it = samples.begin(); it != samples.end(); ++it)
    *it /= 32768.;

  delete[] buffer;

  return 1;
}






int Sound::saveFile(const char* path)
{
  snddata tmp = samples;

  // de-normalize
  for(snddata::iterator it = tmp.begin(); it != tmp.end(); ++it)
    *it *= 32000;

  short *toBeSaved = new short[tmp.size()];

  // check endianess and convert to little endian if needed
  bool bigEndian = isBigEndian();

  for(size_t i = 0; i < tmp.size(); ++i)
    if(bigEndian)
      toBeSaved[i] = swapBytes2(static_cast<short>(tmp[i]));
    else
      toBeSaved[i] = static_cast<short>(tmp[i]);

  // stow it away
  ofstream file(path);
  if(!file)
    return 0;

  file.write(reinterpret_cast<char*>(toBeSaved), tmp.size() * 2);

  delete[] toBeSaved;

  return 1;
}




int Sound::dumpTxt(const char *path)
{
  ofstream file(path);
  if(!file)
    return 0;

  file << scientific; //one consistent format

  file << "# sample-nr  time  ampl  base-freq\n";

  long double stamp = 0;
  long double dur = 0;
  Ringbuf freqs(100);
  long long nr = 1;
  for(snddata::iterator it = samples.begin(); it != samples.end(); ++it, ++nr)
    {
      long double time_now = nr / SMPLRATE;
     
      if((*(it-1) < 0 && *it > 0)) // one oscillation (of a sine...)
	{
	  dur = time_now - stamp;// save the time it took
	  stamp = time_now;
	}
      
      if(dur)
	{
	  freqs.add(1./dur);

	  file << nr << " " << time_now << " " << *it << " " << 
	     freqs.getAvg() << "\n";
	  
	  dur = 0;
	}
      else
	file << nr << " " << time_now << " " << *it << "\n";
    }    
  return 1;
}




double Sound::getMaxAmp()
{
  double max = fabs(*max_element(samples.begin(), samples.end())); 
  double min = fabs(*min_element(samples.begin(), samples.end())); 
  return max > min ? max : min;
}



void Sound::normalize()
{
  double norm = getMaxAmp();

  // normalize
  for(snddata::iterator it = samples.begin(); it != samples.end(); ++it)
    *it /= norm;
}





void Sound::cutoff()
{
   for(snddata::iterator it = samples.begin(); it != samples.end(); ++it)
     {
       if(*it > 1)
	 *it = 1;
       if(*it < -1)
	 *it = -1;
     }
}






Sound Sound::filtX(int cpos, double cfact)
{
  Sound out;
  out.samples.assign(samples.size(), 0); // same size, all zero
  
  snddata::iterator in_it = samples.begin();
  snddata::iterator out_it = out.samples.begin();

  long s = 0;
  while(in_it != samples.end())
    {
      if(s >= cpos)
	*out_it += cfact * *(in_it-cpos);
      
      ++in_it;
      ++out_it;
      ++s;
    }
 
  return out;
}





Sound Sound::filtY(int d1pos, double d1fact, int d2pos, double d2fact)
{
  Sound out;
  out.samples = samples;
  
  snddata::iterator in_it = samples.begin();
  snddata::iterator out_it = out.samples.begin();

  long s = 0;
  while(in_it != samples.end())
    {
      if(s >= d1pos)
	*out_it += d1fact * *(out_it-d1pos);

      if(s >= d2pos)
	*out_it += d2fact * *(out_it-d2pos);
      
      ++in_it;
      ++out_it;
      ++s;
    }
 
  return out;
}




Sound Sound::envf()
{
  double b = 0.9997;

  Sound out(*this); // output signal
  
  snddata::iterator in_it = samples.begin();
  snddata::iterator out_it = out.samples.begin();

  // special case first sample
  *out_it = abs(*in_it);
  ++in_it;
  ++out_it;

  while(in_it != samples.end())
    {
      *out_it = max(abs(*in_it), b * *(out_it-1)); 
      ++in_it;
      ++out_it;
    }
 
  return out;
}


Sound& Sound::operator+=(const Sound& rhs)
{
  size_t sz = rhs.samples.size();

  if(samples.size() < sz)
    samples.resize(sz);

  for(size_t i = 0; i < sz; ++i)
    samples[i] += rhs.samples[i];

  return *this;
}




const Sound Sound::operator+(const Sound& rhs)
{
  return Sound(*this) += rhs;
}




Sound& Sound::operator*=(const Sound& rhs)
{
  size_t sz = min(samples.size(), rhs.samples.size());

  for(size_t i = 0; i < sz; ++i)
    samples[i] *= rhs.samples[i];

  return *this;
}


const Sound Sound::operator*(const Sound& rhs)
{
  return Sound(*this) *= rhs;
}



const Sound Sound::operator*(const double a)
{
  size_t sz = samples.size();

  Sound prod(sz);

  for(size_t i = 0; i < sz; ++i)
    prod.samples[i] = samples[i] * a;

  return prod;
}








Sound mkStereo(Sound left, Sound right)
{
  // the smaller one
  size_t size = left.samples.size() < right.samples.size() ? left.samples.size() : right.samples.size();

  Sound stereo;
  
  for(size_t i = 0; i < size; ++i)
    {
      stereo.samples.push_back(left.samples[i]);
      stereo.samples.push_back(right.samples[i]);
    }

  stereo.stereo = true;
  return stereo;
}

