#include "Mixer.h"

using namespace std;




void Mixer::init(std::vector<double*> *inp, std::vector<double> *w)
{
  inputs = inp;
  weights = w;
}


void Mixer::next() 
{
  output = 0;
  for (size_t i = 0; i < (*inputs).size(); ++i) 
    output +=  *((*inputs)[i]) * (*weights)[i];
}

