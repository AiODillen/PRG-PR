#include <iostream>

using namespace std;

class GameofLife
{
  int width, length;
public:
  GameofLife();
  GameofLife(int, int);
  void print(int**);
  int **generate_2d_array();
};

GameofLife::GameofLife(int x, int y) {width = x; length = y;}
GameofLife::GameofLife() {width = 30; length = 30;}

int** GameofLife::generate_2d_array() {
    cout << "Matrix " << width << "x" << length << " was created:" << endl;
    int ** array2D;
    array2D = new int*[width];
    for (int i = 0; i < width; i++) {
        array2D[i]= new int[length];
        for (int j = 0; j < length; j++) {
            array2D[i][j] = 0;
        }
    }
    return array2D;
}

void GameofLife::print(int** array)
{
  cout << endl;
  for (int x=0; x<width; x++){
      for (int y=0; y<length; y++){
          cout << array[x][y] << " ";
      }
      cout << endl;
  }
  cout << endl;
}

int main()
{
  string i; cout << "Eigene Größe festlegen? >>  "; cin >> i;
  if (i=="N" || i=="n"){
    GameofLife feld;
    int** new_array = feld.generate_2d_array();
    new_array[4][4] = 1;
    feld.print(new_array);
  }
  else if (i=="Y" || i=="y"){
    int j, h; cout << endl; cout << "Länge? >>  "; cin >> j; cout << endl;
    cout << "Breite? >>  "; cin >> h; cout << endl;
    GameofLife feld (j, h);
    int** new_array = feld.generate_2d_array();
    new_array[4][4] = 1;
    feld.print(new_array);
  }
  return 0;
}
