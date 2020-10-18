// das code-lager



  Sound snd1;
  for(int x=0; x< 44100*5; ++x)
    snd1.samples.push_back(sin((2* M_PI *x * 60)/44100.));
  snd1.normalize();





/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++
aufgabe 3
*/



Sound sweep;
  sweep.samples.push_back(0.);
  for(long double x = 0; x < log(22050); x += (log(22050)/(44100*30)))
    sweep.samples.push_back(sweep.samples.back() + 2 * M_PI * (exp(x)/44100.));
  for(snddata::iterator it = sweep.samples.begin(); it != sweep.samples.end(); ++it)
  *it =  0.7 * sin(*it);






/*
  aufgabe 4
  +++++++++++++++++++++++++++++++++++++++++++
*/


double g2r(double f)
{
  double guete = 20; 
  double r = exp((-M_PI*f*(1./44100.))/guete); 
  cout << "R: " << r << endl; 
  return r;
}


Sound bandfilt(Sound& in, double f)
{
  double r = g2r(f);
  double omega = (2*M_PI* f) /44100;
  double norm = 1-r;

  // first, norm it
  Sound out = in * norm;
  
  // then filter
  //              c0*1           c2* -r
  out = out.filtX(0,1) + out.filtX(2,-r);
  
  //              d1 * 2*r*cos(omega), d2 * -r² 
  out = out.filtY(1, 2*r*cos(omega), 2, -(r*r));
  
 
  /*      
	  orig impl....
	  c0 c1 c2   d1              d2 
	  cband1.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  */

  out.normalize();
  return out;
}





  Sound carrier;
  double v = .5;
  int freq= 300;
  for(size_t x = 0; x < input.samples.size(); ++x)
    { 
      //sawtooth
      //carrier.samples.push_back((2*fmod(2*x*freq, SMPLRATE))-SMPLRATE);

      // rectangle
      if(x % ((int)SMPLRATE/(freq/2)) == 0)
	v = -v;
      carrier.samples.push_back(v);
      
     
      // white noise
      //carrier.samples.push_back( (2*(double)rand()/RAND_MAX)-1);
    }
  carrier.normalize();




  /*
    die filterbank
  */

  // 1
  Sound band1 = bandfilt(input,150);
  band1.saveFile("band1.aum");
  Sound cband1 = bandfilt(carrier,150);


  // 2  
  Sound band2 = bandfilt(input, 250);
  band2.saveFile("band2.aum");
  Sound cband2 = bandfilt(carrier,250);

  
  // 3
  Sound band3 = bandfilt(input, 450);
  band3.saveFile("band3.aum");
  Sound cband3 = bandfilt(carrier,450);

  // 4
  Sound band4 = bandfilt(input, 850);
  band4.saveFile("band4.aum");
  Sound cband4 = bandfilt(carrier,850);
  
  // 5
  Sound band5 = bandfilt(input, 1250);
  band5.saveFile("band5.aum");
  Sound cband5 = bandfilt(carrier, 1250);

  // 6
  Sound band6 = bandfilt(input, 1650);
  band6.saveFile("band6.aum");
  Sound cband6 = bandfilt(carrier, 1650);

  // 7
  Sound band7 = bandfilt(input, 2300);
  band7.saveFile("band7.aum");
  Sound cband7 = bandfilt(carrier, 2300);

  
  // 8
  Sound band8 = bandfilt(input, 3000);
  band8.saveFile("band8.aum");
  Sound cband8 = bandfilt(carrier, 3000);


  // 9
  Sound band9 = bandfilt(input, 3700);
  band9.saveFile("band9.aum");
  Sound cband9 = bandfilt(carrier, 3700);

  // 10
  Sound band10 = bandfilt(input, 4600);
  band10.saveFile("band10.aum");
  Sound cband10 = bandfilt(carrier, 4600);


  // 11
  Sound band11 = bandfilt(input, 5400);
  band11.saveFile("band11.aum");
  Sound cband11 = bandfilt(carrier, 5400);


  // 12
  Sound band12 = bandfilt(input, 6300);
  band12.saveFile("band12.aum");
  Sound cband12 = bandfilt(carrier, 6300);

  // 13
  Sound band13 = bandfilt(input, 7000);
  band13.saveFile("band13.aum");
  Sound cband13 = bandfilt(carrier, 7000);

  // 14
  Sound band14 = bandfilt(input, 7700);
  band14.saveFile("band14.aum");
  Sound cband14 = bandfilt(carrier, 7700);

  // 15
  Sound band15 = bandfilt(input, 8500);
  band15.saveFile("band15.aum");
  Sound cband15 = bandfilt(carrier, 8500);

  // 16
  Sound band16 = bandfilt(input, 9500);
  band16.saveFile("band16.aum");
  Sound cband16 = bandfilt(carrier, 9500);

  // 17
  Sound band17 = bandfilt(input, 10600);
  band17.saveFile("band17.aum");
  Sound cband17 = bandfilt(carrier, 10600);

  // 18
  Sound band18 = bandfilt(input, 11900);
  band18.saveFile("band18.aum");
  Sound cband18 = bandfilt(carrier, 11900);

  // 19
  Sound band19 = bandfilt(input, 13200);
  band19.saveFile("band19.aum");
  Sound cband19 = bandfilt(carrier, 13200);

  // 20
  Sound band20 = bandfilt(input, 14800);
  band20.saveFile("band20.aum");
  Sound cband20 = bandfilt(carrier, 14800);

  // 21
  Sound band21 = bandfilt(input, 16000);
  band21.saveFile("band21.aum");
  Sound cband21 = bandfilt(carrier, 16000);

  // 22
  Sound band22 = bandfilt(input, 17500);
  band22.saveFile("band22.aum");
  Sound cband22 = bandfilt(carrier, 17500);

  // 23
  Sound band23 = bandfilt(input, 19000);
  band23.saveFile("band23.aum");
  Sound cband23 = bandfilt(carrier, 19000);

  // 24
  Sound band24 = bandfilt(input, 21000);
  band24.saveFile("band24.aum");
  Sound cband24 = bandfilt(carrier, 21000);



  /*
    wieder zusammengesetzte baender
  */
  {
    Sound ass = band1;
    ass +=  band2;
    ass +=  band3;
    ass += band4;
    ass += band5;
    ass +=  band6;
    ass += band7;
    ass += band8;
    ass +=  band9;
    ass +=  band10;
    ass += band11;
    ass += band12;
    ass += band13;
    ass += band14;
    ass += band15;
    ass += band16;
    ass += band17;
    ass += band18;
    ass += band19;
    ass += band20;
    ass += band21;
    ass += band22;
    ass += band23;
    ass += band24;

    ass.normalize();
    ass.saveFile("re-assembled.aum");
  }

  /*
    rinks und lechts
  */
  {
    Sound left = band1;
    left += band3;
    left += band5;
    left += band7;
    left += band9;
    left += band11;
    left += band13;
    left += band15;
    left += band17;
    left += band19;
    left += band21;
    left += band23;
    left.normalize();

    Sound right = band2;
    right += band4;
    right += band6;
    right += band8;
    right += band10;
    right += band12;
    right += band14;
    right += band16;
    right += band18;
    right += band20;
    right += band22;
    right += band24;
    right.normalize();
  
    Sound stereo = mkStereo(left, right);
    stereo.saveFile("stereo.aum");


    /*
      mono-stereo-mono fade
    */
    Sound fade;
    fade.stereo = true;

    size_t size = min(left.samples.size(), right.samples.size());

    double pan = 0.5;
    double delta = 0.5 / (size/2);
    for(size_t  i=0; i < size; ++i)
      {
	//fade.samples.push_back(0);
	fade.samples.push_back(pan* left.samples[i] + (1-pan)*right.samples[i]);
	fade.samples.push_back((1-pan)* left.samples[i] + pan * right.samples[i]);
     
	if (i < size/2)
	  pan += delta;
	else
	  pan -= delta;
      }
    fade.saveFile("mono-stereo-fade.aum");
  }



  /*
    huellkurven der baender
  */

  Sound env1 = band1.envf();
  Sound env2 = band2.envf();
  Sound env3 = band3.envf();
  Sound env4 = band4.envf();
  Sound env5 = band5.envf();
  Sound env6 = band6.envf();
  Sound env7 = band7.envf();
  Sound env8 = band8.envf();
  Sound env9 = band9.envf();
  Sound env10 = band10.envf();
  Sound env11 = band11.envf();
  Sound env12 = band12.envf();
  Sound env13 = band13.envf();
  Sound env14 = band14.envf();
  Sound env15 = band15.envf();
  Sound env16 = band16.envf();
  Sound env17 = band17.envf();
  Sound env18 = band18.envf();
  Sound env19 = band19.envf();
  Sound env20 = band20.envf();
  Sound env21 = band21.envf();
  Sound env22 = band22.envf();
  Sound env23 = band23.envf();
  Sound env24 = band24.envf();


  // VCA
  cband1 *= env1;
  cband2 *= env2;
  cband3 *=  env3;
  cband4 *=  env4;
  cband5 *=  env5;
  cband6 *= env6;
  cband7 *=  env7;
  cband8 *=  env8;
  cband9 *=  env9;
  cband10 *=  env10;
  cband11 *= env11;
  cband12 *=  env12;
  cband13 *=  env13;
  cband14 *=  env14;
  cband15 *=  env15;
  cband16 *=  env16;
  cband17 *=  env17;
  cband18 *=  env18;
  cband19 *=  env19;
  cband20 *=  env20;
  cband21 *=  env21;
  cband22 *=  env22;
  cband23 *=  env23;
  cband24 *=  env24;


  // mixer
  Sound vocoded =  cband1;
  vocoded +=  cband2;
  vocoded +=  cband3;
  vocoded +=  cband4;
  vocoded +=  cband5;
  vocoded +=  cband6;
  vocoded +=  cband7;
  vocoded += cband8;
  vocoded +=  cband9;
  vocoded +=  cband10;
  vocoded += cband11;
  vocoded += cband12;
  vocoded += cband13;
  vocoded += cband14;
  vocoded += cband15;
  vocoded += cband16;
  vocoded += cband17;
  vocoded += cband18;
  vocoded += cband19;
  vocoded += cband20;
  vocoded += cband21;
  vocoded += cband22;
  vocoded += cband23;
  vocoded += cband24;

  vocoded.saveFile("vocoded.aum");







/*
aufgabe 5  
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

void kammFilt(Sound& s, int d, double delt)
{
  s = s.filtX(d, 1);
  s = s.filtY(0,1, d, -delt);
  s.normalize();
}


 // tiefpass
  Sound lowpassed = input.filtX(0, 0.3) + input.filtX(1 ,0.7);


  /*
    parameter... links, rechts, vorne, hinten, oben, unten
    raum... (laenge x breite x hoehe)
  */

  // bad (3 x 5 x 3m)
  int      d1=191,      d2=193,   d3=331,      d4=337,      d5=157,    d6=239;
  double dlt1=0.9158, dlt2=0.9149, dlt3=.8586, dlt4=.8562, dlt5=.9302, dlt6=.8957;

  // holzsarg (2,2 x 0,8 x 0,5m)
  //int      d1=53,      d2=59,   d3=139,      d4=149,      d5=31,     d6=37;
  //double dlt1=.9499, dlt2=.9444, dlt3=.8740, dlt4=.8656, dlt5=.9704, dlt6=.9648;

  // halle (30 x 50 x 10m)
  //int      d1=3251,   d2=3253,   d3=1951,      d4=1949,      d5=653,     d6=647;
  // double dlt1=.7303, dlt2=.7301, dlt3=.8281, dlt4=.8282, dlt5=.9388, dlt6=.9394;



  // halle 2
  //int      d1=6427,   d2=6661,   d3=3989,      d4=3853,      d5=1427,   d6=1297;
  //double dlt1=.5372, dlt2=.5252, dlt3=.6800, dlt4=.6890, dlt5=.8711, dlt6=.8821;




  // verzoegerung
  int m = min(min( min(d1,d2), min(d3,4)), min(d5,d6));
  lowpassed = lowpassed.filtX(m, 1);

  Sound kf1 = lowpassed;
  Sound kf2 = lowpassed;
  Sound kf3 = lowpassed;
  Sound kf4 = lowpassed;
  Sound kf5 = lowpassed;
  Sound kf6 = lowpassed;
 
  kammFilt(kf1, d1, dlt1);
  kammFilt(kf2, d2, dlt2);
  kammFilt(kf3, d3, dlt3);
  kammFilt(kf4, d4, dlt4);
  kammFilt(kf5, d5, dlt5);
  kammFilt(kf6, d6, dlt6);

  Sound links = kf1 + kf2 +kf3;
  Sound rechts = kf1 + kf2 +kf3;

  links.normalize();
  rechts.normalize();

  // allpass
  links = links.filtX(0, -0.7) + links.filtX(13, 1);
  links.filtY(13, 0.7, 0 , 0);

  rechts = rechts.filtX(0, -0.7) + rechts.filtX(14, 1);
  rechts.filtY(14, 0.7, 0 , 0);


  
  // wieder-zusammenfuehrung
  links =  input * 0.6 + links * 0.4;
  rechts =  input * 0.6 + rechts * 0.4;

  Sound output = mkStereo(links, rechts);
  output.normalize();








/*
  ++++++++++++++++++++++++++++++++
  4 mod
*/




  Sound carrier;
  for(size_t x = 0; x < input.samples.size(); ++x)
    carrier.samples.push_back(0.5 * ( (2*(double)rand()/RAND_MAX)-1) );

 
 


  /*
    die filterbank
  */

  double r, omega, norm;

  // 1
  r = 0.96;
  omega = (2*M_PI*150)/44100;
  norm = 0.963;

  Sound band1 = input;
  band1.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band1.normalize();
  band1.saveFile("band1.aum");

  Sound cband1 = carrier;
  cband1.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband1.normalize();
  


  // 2  
  norm= 0.96;
  omega = (2*M_PI*2500)/44100;

  Sound band2 = input;
  band2.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band2.normalize();
  band2.saveFile("band2.aum");
  
  Sound cband2 = carrier;
  cband2.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband2.normalize();

  
  // 3
  omega = (2*M_PI*4500)/44100;

  Sound band3 = input;
  band3.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band3.normalize();
  band3.saveFile("band3.aum");

   Sound cband3 = carrier;
  cband3.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband3.normalize();

  // 4
  omega = (2*M_PI*6500)/44100;

  Sound band4 = input;
  band4.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band4.normalize();
  band4.saveFile("band4.aum");

 Sound cband4 = carrier;
 cband4.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband4.normalize();  
  
  
  // 5
  omega = (2*M_PI*8500)/44100;

  Sound band5 = input;
  band5.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band5.normalize();   
  band5.saveFile("band5.aum");
  
  Sound cband5 = carrier;
  cband5.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband5.normalize(); 



  // 6
  omega = (2*M_PI*10500)/44100;

  Sound band6 = input;
  band6.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band6.normalize();
  band6.saveFile("band6.aum");

  Sound cband6 = carrier;
  cband6.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband6.normalize(); 


  // 7
  omega = (2*M_PI*12500)/44100;

  Sound band7 = input;
  band7.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band7.normalize();
  band7.saveFile("band7.aum");
  
  Sound cband7 = carrier;
  cband7.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband7.normalize();

  
  // 8
  omega = (2*M_PI*14500)/44100;

  Sound band8 = input;
  band8.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band8.normalize();   
  band8.saveFile("band8.aum");
  
 Sound cband8 = carrier;
  cband8.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband8.normalize();


  // 9
  omega = (2*M_PI*16500)/44100;

  Sound band9 = input;
  band9.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band9.normalize();  
  band9.saveFile("band9.aum");

 Sound cband9 = carrier;
  cband9.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband9.normalize();  


  // 10
  omega = (2*M_PI*18500)/44100;

  Sound band10 = input;
  band10.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band10.normalize();   
  band10.saveFile("band10.aum");

   Sound cband10 = carrier;
  cband10.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband10.normalize();



  // 11
  omega = (2*M_PI*20500)/44100;

  Sound band11 = input;
  band11.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band11.normalize(); 
  band11.saveFile("band11.aum");

 Sound cband11 = carrier;
  cband11.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband11.normalize();  


  // 12
  r = 0.96;
  omega = (2*M_PI*22050)/44100;
  norm = 0.9645;
  
  Sound band12 = input;
  band12.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  band12.normalize();
  band12.saveFile("band12.aum");

  Sound cband12 = carrier;
  cband12.iirFilt2(norm, 1, 0, -r, 2*r*cos(omega), -(r*r));  
  cband12.normalize();



  /*
    wieder zusammengesetzte baender
  */
  Sound ass = band1 +  band2 + band3 + band4 + band5 + band6
    + band7 +band8 + band9 + band10 +band11 +band12;
  ass.normalize();
  ass.saveFile("re-assembled.aum");


  /*
    rinks und lechts
  */
  Sound left = band1 +band2 +band3 +band4 +band5 +band6;
  left.normalize();

  Sound right = band7 + band8 +band9 +band10 +band11 +band12;
  right.normalize();
  
  Sound stereo = mkStereo(left, right);
  stereo.saveFile("stereo.aum");


  /*
    mono-stereo-mono fade
  */
  Sound fade;
  fade.stereo = true;

  size_t size = min(left.samples.size(), right.samples.size());

  double pan = 0.5;
  double delta = 0.5 / (size/2);
  for(size_t  i=0; i < size; ++i)
    {
      //fade.samples.push_back(0);
      fade.samples.push_back(pan* left.samples[i] + (1-pan)*right.samples[i]);
      fade.samples.push_back((1-pan)* left.samples[i] + pan * right.samples[i]);
     
      if (i < size/2)
	pan += delta;
      else
	pan -= delta;
    }
  fade.saveFile("mono-stereo-fade.aum");
  



  /*
    huellkurven der baender
  */

  Sound env1 = band1;
  env1.envf();

  Sound env2 = band2;
  env2.envf();

  Sound env3 = band3;
  env3.envf();

  Sound env4 = band4;
  env4.envf();

  Sound env5 = band5;
  env5.envf();

 Sound env6 = band6;
  env6.envf();

 Sound env7 = band7;
  env7.envf();

 Sound env8 = band8;
  env8.envf();

 Sound env9 = band9;
  env9.envf();

  Sound env10 = band10;
  env10.envf();

 Sound env11 = band11;
  env11.envf();

 Sound env12 = band12;
  env12.envf();

  // VCA
  cband1 = cband1 * env1;
  cband2 = cband2 * env2;
  cband3 = cband3 * env3;
  cband4 = cband4 * env4;
  cband5 = cband5 * env5;
  cband6 = cband6 * env6;
  cband7 = cband7 * env7;
  cband8 = cband8 * env8;
  cband9 = cband9 * env9;
  cband10 = cband10 * env10;
  cband11 = cband11 * env11;
  cband12 = cband12 * env12;

  // mixer
  Sound vocoded =  cband1 +  cband2 + cband3 + cband4 + cband5 + cband6
    + cband7 +cband8 + cband9 + cband10 +cband11 +cband12;


  vocoded.saveFile("vocoded.aum");
