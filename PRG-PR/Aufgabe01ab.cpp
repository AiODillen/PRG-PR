#include <stdlib.h>     // enables RNG
#include <time.h>  //for better RNG based on time
#include <iostream>  //console in-/output
#include <cstring>      // for copying

using namespace std;  //standard namespace used

void copy(int arraya[][30], int arrayb[]);

void print_array1(int array[], int length);

void print_array2(int array[][30]);

void generate_2d_array();

void interface();

int main()
{
    srand(time(0));  //initializes the RNG
    interface();
    return 0;
}

void print_array1(int array[], int length)
//prints the 1D array
{
    cout << endl;
    int m=0;
    for (int n=0; n<length; n++){
        m+=1;
        cout << array[n] << " ";
        if (m==30){  //beginns new line after 30 characters to match the 2D array
            cout << endl;
            m=0;
        }
    }
    cout << endl;
}

void print_array2(int array[][30])
//prints 2D array
{
    cout << endl;
    for (int x=0; x<30; x++){
        for (int y=0; y<30; y++){
            cout << array[x][y] << " ";
        }
        cout << endl;  // new line after 30 chars to get matrix look
    }
    cout << endl;
}

void copy(int arraya[][30], int arrayb[])
//Takes the recieving array; the source array; the length times the data size
//in the recieving array
{
    memcpy(arrayb, arraya, 900*sizeof(int));
}

void generate_2d_array(int array[][30])
//fills 2D array with random digits from 0-9
{
    for (int x=0; x<30; x++){
        for (int y=0; y<30; y++){
            array[x][y] = rand()%10;  //mod10 to only get 0-9
        }
    }
}
void interface()
{
    int array2d [30][30]; int* array1d = new int [900];  //initializes arrays
    string i; cout << "(Für eine Liste an Befehlen (? oder help) eingeben." << endl;
    while (true){
        cout << "Welche Aktion ausführen? >>"; cin >> i;
        if (i=="?" || i=="help"){
            cout << endl << "2D Array generieren:  generate2D" << endl;
            cout << "2D in 1D kopieren:  copy2D" << endl << "2D Array ausgeben:  print2D" << endl;
            cout << "1D array ausgeben:  print1D" << endl << "Zum beenden des Programms:  exit" << endl << endl;
        }
        else if (i=="generate2D"){
            generate_2d_array(array2d);
        }
        else if (i=="copy2D"){
            copy(array2d, array1d);
        }
        else if (i== "print2D"){
            print_array2(array2d);
        }
        else if (i=="print1D"){
            print_array1(array1d, 900);
        }
        else if (i=="exit"){
            break;
        }
        else{
            cout << "Falsche Eingabe!" << endl << endl;
            return interface();
        }
    }
}
