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


void *new_mixer() {
    Mixer *m = new Mixer();
    return m;
}

double mixer_next(void *mixer, double in1, double in2, double w1, double w2) {
    Mixer *m = static_cast<Mixer*>(mixer);

    vector<double*> *mix_in = new vector<double*>();
    mix_in->push_back(new double(in1));
    mix_in->push_back(new double(in2));
    vector<double> *mix_w = new vector<double>();
    mix_w->push_back(w1);
    mix_w->push_back(w2);
    m->init(mix_in, mix_w);

    m->next();
    return m->output;
}
