#ifndef MULTMODUL_H_ 
#define MULTMODUL_H_
#include <vector>
using namespace std;
class MultiModul
{
public:
	void setLength(int newlength);
	void next();
	void init(int buffl, vector<int>* picks, vector<double>* ws);
	void setInput(double* in);
	void resize(int newlength);
	void printBuffer();
	
	double output;
private:
	double* input;
	int pointer;
	int length;
	int bufflength;
	int end;
	int begin;
	
	
	vector<double> buffer;
	vector<int>* pickups;
	vector<double> *weights;
	int pickuplength;
};


extern "C" {
    void *new_multimodul(int buflen, int pick1, int pick2, double ws1, double ws2);
    double multimodul_next(void* multimodul, double in);
}


#endif /*MULTMODUL_H_*/



