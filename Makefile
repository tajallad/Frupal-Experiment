#Makefile for group project experiment (experiment.cpp)
#Tareq Jallad 2020

CPP = g++
CPPFLAGS = -Wall -g -Werror

experiment: experiment.cpp color.cpp
				$(CPP) $(CPPFLAGS) -o experiment experiment.cpp color.cpp -lncurses

clean:
				-rm -f experiment
