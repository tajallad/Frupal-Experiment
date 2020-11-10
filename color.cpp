#include "color.h"

using namespace std;

#define MEADOW_PAIR 1
#define SWAMP_PAIR 2
#define WATER_PAIR 3
#define WALL_PAIR 4
#define HERO_PAIR 5
#define DIAMOND_PAIR 6

void initialize_color() //set up the color pairs for the program (foreground and background)
{
  start_color();
  init_pair(MEADOW_PAIR, COLOR_BLACK, COLOR_GREEN);
  init_pair(SWAMP_PAIR, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(WATER_PAIR, COLOR_BLACK, COLOR_BLUE);
  init_pair(WALL_PAIR, COLOR_BLACK, COLOR_WHITE);
  init_pair(HERO_PAIR, COLOR_YELLOW, COLOR_RED);
  init_pair(DIAMOND_PAIR, COLOR_WHITE, COLOR_CYAN);
}

void setup_map()
{
  attron(COLOR_PAIR(MEADOW_PAIR)); //fill screen with green
  for(int y = 0; y < LINES; y++)
  {
    mvhline(y, 0, ' ', COLS);
  }
  attroff(COLOR_PAIR(MEADOW_PAIR));

  attron(COLOR_PAIR(SWAMP_PAIR)); //add square of swamp
  for(int y = 5; y < 11; y++)
  {
    mvhline (y, 5, ' ', 10);
  }
  attroff(COLOR_PAIR(SWAMP_PAIR));

  attron(COLOR_PAIR(WATER_PAIR)); //add sqaure of water
  for(int y = 15; y < 21; y++)
  {
    mvhline (y, 5, ' ', 10);
  }
  attroff(COLOR_PAIR(WATER_PAIR));

  attron(COLOR_PAIR(WALL_PAIR)); //add square of wall
  for(int y = 5; y < 11; y++)
  {
    mvhline (y, 30, ' ', 10);
  }
  attroff(COLOR_PAIR(WALL_PAIR));
  move(0,0);
  refresh();
}

int movecheck(int y, int x) //check what color square we are moving to
{
  //MEADOW = 256
  //SWAMP = 512
  //WATER = 768
  //WALL = 1024
  //check & A_COLOR = color pair field information
  int check;

  check = mvinch(y,x);
  switch(check & A_COLOR)
  {
    case(256):
      return MEADOW_PAIR;
    case(512):
      return SWAMP_PAIR;
    case(768):
      return WATER_PAIR;
    case(1024):
      return WALL_PAIR;
    default:
      return MEADOW_PAIR;
  }
}

void movearound()
{
  int keypress;
  int yaxis = 0;
  int xaxis = 0;
  int previouscolor = 1; //keep track of what we walked over

  //create hero at starting point
  attron(COLOR_PAIR(HERO_PAIR));
  addch('@');
  move(yaxis,xaxis);
  attroff(COLOR_PAIR(HERO_PAIR));

  bool again = 1;
  while(again)
  {
    keypress = getch();
    switch(keypress)
    {
      case KEY_LEFT:
        if(xaxis == 0)
          break;
        //make sure we do not move into wall or water
        if(movecheck(yaxis,xaxis-1) == 1 || movecheck(yaxis,xaxis-1) == 2)
        {
          //put back what we walked over, since we are moving off of it
          move(yaxis,xaxis);
          attron(COLOR_PAIR(previouscolor));
          addch(' ');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(previouscolor));
          xaxis--;
          //update new previouscolor, since we are walking over another square
          previouscolor = movecheck(yaxis,xaxis);
          move(yaxis, xaxis);
          //move hero to new square
          attron(COLOR_PAIR(HERO_PAIR));
          addch('@');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(HERO_PAIR));
          refresh();
        }
        move(yaxis,xaxis);
        break;

      case KEY_RIGHT:
        if(xaxis == COLS-1)
          break;
        //make sure we do not move into wall or water
        if(movecheck(yaxis,xaxis+1) == 1 || movecheck(yaxis,xaxis+1) == 2)
        {
          //put back what we walked over, since we are moving off of it
          move(yaxis,xaxis);
          attron(COLOR_PAIR(previouscolor));
          addch(' ');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(previouscolor));
          xaxis++;
          //update new previouscolor, since we are walking over another square
          previouscolor = movecheck(yaxis,xaxis);
          move(yaxis, xaxis);
          //move hero to new square
          attron(COLOR_PAIR(HERO_PAIR));
          addch('@');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(HERO_PAIR));
          refresh();
        }
        move(yaxis,xaxis);
        break;

      case KEY_DOWN:
        if(yaxis == LINES-1)
          break;
        //make sure we do not move into wall or water
        if(movecheck(yaxis+1,xaxis) == 1 || movecheck(yaxis+1,xaxis) == 2)
        {
          //put back what we walked over, since we are moving off of it
          move(yaxis,xaxis);
          attron(COLOR_PAIR(previouscolor));
          addch(' ');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(previouscolor));
          yaxis++;
          //update new previouscolor, since we are walking over another square
          previouscolor = movecheck(yaxis,xaxis);
          move(yaxis, xaxis);
          //move hero to new square
          attron(COLOR_PAIR(HERO_PAIR));
          addch('@');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(HERO_PAIR));
          refresh();
        }
        move(yaxis,xaxis);
        break;

      case KEY_UP:
        if(yaxis == 0)
          break;
        //make sure we do not move into wall or water
        if(movecheck(yaxis-1,xaxis) == 1 || movecheck(yaxis-1,xaxis) == 2)
        {
          //put back what we walked over, since we are moving off of it
          move(yaxis,xaxis);
          attron(COLOR_PAIR(previouscolor));
          addch(' ');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(previouscolor));
          yaxis--;
          //update new previouscolor, since we are walking over another square
          previouscolor = movecheck(yaxis,xaxis);
          move(yaxis, xaxis);
          //move hero to new square
          attron(COLOR_PAIR(HERO_PAIR));
          addch('@');
          move(yaxis,xaxis);
          attroff(COLOR_PAIR(HERO_PAIR));
          refresh();
        }
        move(yaxis,xaxis);
        break;

      default:
        again = 1;
        break;
    }
  }
}
