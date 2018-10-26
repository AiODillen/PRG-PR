#include <iostream>

using namespace std;

class GameofLife
{
  int width;
  int length;
  int feld[30][30];
public:
  void set_size(int a, int b);
};

void GameofLife::set_size(int a , int b)
{
  width = a;
  length = b;
}
int main()
{
  GameofLife feld;
  return 0;
}
