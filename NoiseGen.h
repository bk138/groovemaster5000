#ifndef NOISEGEN_H_
#define NOISEGEN_H_



class NoiseGen
{
  int counter;

 public:
  double output;
    
  void init(int l);	

  void next(); 
};





#endif /*NOISEGEN_H_*/
