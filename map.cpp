#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

char map[128][128];

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

void printMapChar(int width, int height) //prints map characters, arguments are dimensions printed
{
  for(int y = 0; y < height; y++){
    cout <<  "\n";
    for(int x = 0; x < width; x++){
      cout << map[y][x];
    }
  }
  cout <<  "\n";
}




int main()
{
  initializeMap();
  printMapChar(128, 128);
  return 0;
}
