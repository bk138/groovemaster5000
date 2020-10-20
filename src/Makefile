# 

CXXFLAGS = $(shell sdl-config --cflags) 
LIBS = $(shell sdl-config --libs) -lm
LIBS_STATIC= $(shell sdl-config --static-libs) -lm 

CXX = g++ -Wall -g -O2 


OUTDIR=./
OUTFILE=groovemaster5000


OBJS=main.o util.o Player.o Sound.o Notesheet.o Mixer.o MultModul.o NoiseGen.o PickedString.o Instrument.o



all: $(OUTFILE)

$(OUTFILE):	$(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(OUTDIR)$(OUTFILE) $(LIBS)

clean:
	$(RM) $(OUTFILE) $(OBJS) *~




Sound.o: Sound.h
Player.o: Player.h
Notesheet.o: Notesheet.h
Mixer.o: Mixer.h
MultModul.o: MultModul.h
NoiseGen.o: NoiseGen.h
PickedString.o: PickedString.h
Instrument.o: Instrument.h
util.o: util.h
