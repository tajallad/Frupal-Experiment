#Makefile for group project experiment (experiment.cpp)
#Tareq Jallad 2020

CPP = g++
CPPFLAGS = -Wall -g -Werror

map: map.cpp
				$(CPP) $(CPPFLAGS) -o map map.cpp -lncurses

clean:
				-rm -f map
