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


#endif /*MIXER_H_*/
