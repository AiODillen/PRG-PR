#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main()
{
    int width = 20;
    int length = 20;
    char trash[100];
    ifstream infile;
    infile.open("feld.txt");
    infile >> trash;
    infile >> trash;
    string str;
    int ** array2D;
    array2D = new int*[width];
        for (int i = 0; i < width; i++) {
            infile >> str;
            array2D[i]= new int[length];
            int j=0;
            while (j < length){
                for(char& c : str) {
                        if (c=='o'){
                            cout << "0 ";
                        }
                        else if (c=='*'){
                            cout << "1 ";
                        }
                        j++;
                }
            }
            cout << endl;
        }
}
