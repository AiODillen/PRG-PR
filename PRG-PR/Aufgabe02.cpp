//Visuelle Kryptographie

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {

  char data[100];

  ifstream infile;
  infile.open("beispiel.txt");
  infile >> data;


  cout << data;
}
