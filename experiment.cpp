#include "color.h"

using namespace std;

int main()
{
  initscr();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  curs_set(0);

  initialize_color();
  setup_map();
  movearound();

  endwin();
  return 0;
}
