#include "MultModul.h"
#include<iostream>
    
using namespace std;



void MultiModul::init(int buffl, vector<int>* picks, vector<double>* ws) {
	bufflength = buffl;
	length = buffl;
	buffer.resize(buffl);
	begin = 0;
	end = length-1;
	pointer =0;
	pickups = picks;  // Abtaststellen des Filters
	weights = ws;     // Gewichte der Abtastsellen
	pickuplength = (*picks).size();
	
}
void MultiModul::setInput(double* in) {
	input = in; 
}
/**
 * Diese Functtion verändert die Lenge und passt die pickups der Länge an 
 * geeignet für Delaylines nicht umbedingt für filter
 * 
 */
 
void MultiModul::resize(int newlength) {
	
	int diff = length -newlength;
	for(unsigned i=0; i<(*pickups).size();++i) {
		(*pickups)[i] -= diff;
	}
	setLength(newlength);
}
void MultiModul::setLength(int newlength) {
	 int i;
	if(newlength > bufflength) {
		
		if(end>=begin) {
			buffer.resize(newlength,0);
			bufflength = newlength;
		} else {
			
			vector<double>::iterator start = buffer.begin();
			vector<double>::iterator stop  = buffer.begin() + end +1;
		    vector<double> newbuffer(start,stop);
		    int diff = newlength -length;
		    newbuffer.resize(newlength,0);
		    //cout << "Kurz vor der Vorschleife";
		    for(i=begin;i < bufflength; ++i) {
		    	newbuffer[i+diff-1] = buffer[i];
		    }
		    // cout << "Kurz nach der Vorschleife";
			buffer = newbuffer;
			bufflength = newlength;
		}
	}
	if (newlength < length) { //endpositionierung versuch das verkürzen einer seite realistisch abzubilden
		end = pointer - (length -newlength); //pointer ist immer auf dem momentan ältesten Feld bei Verkürzung

		if(end < 0) {				//fallen die x-ältesten signale weg
			end = bufflength + end;
			cout << end;
		}
		begin = end - newlength+1;
		if (begin <0){	
			begin = bufflength +begin;
			
		}
		pointer = end; //setzen des pointers auf das aktuell letzte gültige Signal
		//setzte die nicht verwendeten Felder des Arrays auf null;
		if(end < begin) {
			for(i=end+1;i<begin;i++) {
				buffer[i] = 0;
			}
		} else {
			for(i=0;i<begin;i++) {
				buffer[i] = 0;
			}
			for(i=end+1;i<bufflength;i++) {
				buffer[i] = 0;
			}
		}
			
	}
	else { // newlength > length
		//setzen von end
		end = pointer+(newlength-length);
		if (end>=bufflength) {
			end = end -bufflength;
			//setzte nun alle Felder des Verlängerten Ringpuffers auf 0 für diesen Fall
			for(i=pointer+1; i<bufflength;i++) {
				buffer[i] = 0;
			}
			for(i=0;i<=end;i++) {
				buffer[i] = 0;
			}		
		} else {
			for(i=pointer+1;i<=end;i++) {
				buffer[i] = 0;
			}
		}
		begin = end - newlength;
		if(begin <0) {
			begin += bufflength+1;
		}
		//beginn muss nicht gesetzt werden da gesichert ist das es zu keiner überscheidnung von begin
		//und end kommt
		
		
	}
	length = newlength;

}
	
void MultiModul::next() {
	int pickpointer;
	pointer++;
	//cerr << pointer;
	//cerr << " ";
	if(end >= begin) {  //end liegt nach begin auf dem Array einfacher fall;
		if(pointer >end) {
			
			
			pointer = begin;
		}
	} else { //komplizierter Fall end liegt vor begin
		if(pointer <= begin && pointer > end) { //
			pointer = begin;
		} else {
			if(pointer >= bufflength)
				pointer=0; 
		}
	}
	//cerr << "\n Pointer";
	//cerr << pointer; 
	//cerr << "\n";
	
	output=0;
  
	for (int i=0; i<pickuplength;i++) {
		if((*pickups)[i] == 0) {
			output =output+ *input * (*weights)[i];
			
			
		} else {
			if((*pickups)[i] <= length) {
				//cerr << (*pickups)[i];
				//cerr << " pick\n";
				pickpointer = pointer-(*pickups)[i];
				if(end >= begin)  { //einfach Fall
					
					if(pickpointer < begin) {
						pickpointer +=  length;	
					}
				} else {
					if(pickpointer <0) {
						pickpointer = bufflength + pickpointer;
					}
				} 
				output = output + buffer[pickpointer] * (*weights)[i];
			}
		}
		
	//cerr << pickpointer;
	//cerr << "\n";

	}
	//output = buffer[pointer];
	buffer[pointer] = *input;		
}

void MultiModul::printBuffer() {
	cerr << "---------------PrintBuffer-------------------\n";
	for(int i=0;i <bufflength;++i) {
		
		cerr << buffer[i];
		cerr << " ";
	}
	cerr << "----------Bufferlength-";
	cerr << bufflength;
	cerr << "-------------------\n";
}


void *new_multimodul(int buflen, int pick1, int pick2, double ws1, double ws2) {
    MultiModul *mm = new MultiModul;
    vector<int> *mm_p = new vector<int>;
    mm_p->push_back(pick1);
    mm_p->push_back(pick2);
    vector<double> *mm_w = new vector<double>;
    mm_w->push_back(ws1);
    mm_w->push_back(ws2);
    mm->init(buflen, mm_p, mm_w);
    return mm;
}

double multimodul_next(void *multimodul, double in) {
    MultiModul *mm = static_cast<MultiModul*>(multimodul);
    mm->setInput(new double(in));
    mm->next();
    return mm->output;
}

