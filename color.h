#include <iostream>
#include <curses.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <unistd.h>

void initialize_color();
void setup_map();
void movearound();
int movecheck(int y, int x);
