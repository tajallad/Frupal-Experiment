#include <iostream>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

char map[128][128]; //**TESTING PURPOSES

//define names to the colorpair settings
#define MEADOW_PAIR 1
#define SWAMP_PAIR 2
#define WATER_PAIR 3
#define WALL_PAIR 4
#define HERO_PAIR 5
#define DIAMOND_PAIR 6

void initializeColor() //set up the color pairs for the program (foreground and background)
{
  start_color();
  init_pair(MEADOW_PAIR, COLOR_BLACK, COLOR_GREEN);
  init_pair(SWAMP_PAIR, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(WATER_PAIR, COLOR_BLACK, COLOR_BLUE);
  init_pair(WALL_PAIR, COLOR_BLACK, COLOR_WHITE);
  init_pair(HERO_PAIR, COLOR_YELLOW, COLOR_RED);
  init_pair(DIAMOND_PAIR, COLOR_WHITE, COLOR_CYAN);
}

//**ONLY FOR TESTING PURPOSES**
void initializeMap() //fills 2d map array with characters
{
  ifstream in;
  in.open("map.txt");
  for(int y = 0; y < 128; y++){
    for(int x = 0; x < 128; x++){
      in >> map[y][x];
    }
  }
  in.close();
}

//displays the current map frame, with the hero centered
void displayFrame(char map[128][128], int herox, int heroy)
{
  erase(); //clear screen to prevent out of bounds
  int viewport_width = COLS - 30;
  int viewport_height = LINES;
  int hero_xspot = floor(viewport_width/2);
  int hero_yspot = floor(viewport_height/2);

  int y_adder = 2;
  int ycheck = viewport_height;
  if(ycheck % 2 == 0)
    y_adder--;

  int x_adder = 3;
  int xcheck = viewport_width;
  if(xcheck % 2 == 0)
    x_adder = 1;

  mvvline(0, viewport_width+1, '#', viewport_height);

  for(int y = (heroy - (hero_yspot-1)), printy = 0; y < (heroy + hero_yspot + y_adder); y++) {
    if(y < 0 || y > 127) {
      printy++;
      continue;
    }
    for(int x = (herox - (hero_xspot-1)), printx = 0; x < (herox + hero_xspot + x_adder); x++) {
      if(x < 0 || x > 127) {
        printx++;
        continue;
      }
      switch(map[y][x]) {
        case 'm':
          attron(COLOR_PAIR(MEADOW_PAIR));
          mvaddch(printy,printx,' ');
          attroff(COLOR_PAIR(MEADOW_PAIR));
          break;
        case 'w':
          attron(COLOR_PAIR(WALL_PAIR));
          mvaddch(printy,printx,' ');
          attroff(COLOR_PAIR(WALL_PAIR));
          break;
        case 's':
          attron(COLOR_PAIR(SWAMP_PAIR));
          mvaddch(printy,printx,' ');
          attroff(COLOR_PAIR(SWAMP_PAIR));
          break;
        case 'b':
          attron(COLOR_PAIR(WATER_PAIR));
          mvaddch(printy,printx,' ');
          attroff(COLOR_PAIR(WATER_PAIR));
          break;
      }
      printx++;
    }
    printy++;
  }
  attron(COLOR_PAIR(HERO_PAIR));
  mvaddch(hero_yspot,hero_xspot,'@');
  attroff(COLOR_PAIR(HERO_PAIR));
  refresh();
}

int main()
{
  initscr();
  noecho();
  nodelay(stdscr,true);
  keypad(stdscr,true);
  curs_set(0);

  initializeMap();
  initializeColor();
  int xaxis = 0;
  int yaxis = 0;
  int keypress;
  displayFrame(map,xaxis,yaxis);
  while(1){
    keypress = getch();
    switch(keypress) {
      case KEY_LEFT:
        xaxis--;
        displayFrame(map,xaxis,yaxis);
        break;
      case KEY_RIGHT:
        xaxis++;
        displayFrame(map,xaxis,yaxis);
        break;
      case KEY_UP:
        yaxis--;
        displayFrame(map,xaxis,yaxis);
        break;
      case KEY_DOWN:
        yaxis++;
        displayFrame(map,xaxis,yaxis);
        break;
    }
  }

  endwin();
  return 0;
}
