#ifndef MIXER_H_
#define MIXER_H_

#include <vector>
using namespace std;

class Mixer
{
  	std::vector<double*> *inputs;
	std::vector<double> *weights;
public:
	double output;

	void init(std::vector<double*> *inp, std::vector<double> *w);

	void next();
};

extern "C" {
    void *new_mixer(double *in1, double *in2, double w1, double w2);
    void mixer_next(void* mixer);
    double* mixer_get_output(void* mixer);
}


#endif /*MIXER_H_*/
