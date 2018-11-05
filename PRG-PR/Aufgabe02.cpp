//Visuelle Kryptographie

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class testing
{
public:
    void readFile();
    int** readAsArray();
    void interface();
    int** fileImport();

};

// void testing::readFile(){

//  char data[100];

//  ifstream infile;
//  infile.open("beispiel.txt");
//  infile >> data;


//  cout << data;
//  cout << data;
//}

int** testing::readAsArray(){
    char total[100000];
    ifstream infile;
    infile.open("beispiel.txt");
    string str;
    int ** picture;
    picture = new int*[89];
    for (int i = 0; i < 89; i++) {
        infile >> str;
        picture[i]= new int[304];
        int j=0;
        while (j < 304){
            for(char& c : str){
                cout << c << " ";
                if (c=='0'){
                    picture[i][j] = 0;
                }
                else if (c=='*'){
                    picture[i][j] = 1;
                }
                j++;
            }
        }
        cout << endl;
    }
    return picture;
}

void interface() {
    string i;
    while (true){
        cout << "Was möchten sie tun? Für alle Befehle geben Sie help ein: "; cin >> i;
        if (i=="help"){
            cout << endl << "Die möglichen Befehle sind:" << endl;
            cout << "qqq (beendet das Programm)" << endl;
            cout << "fileImport" << endl;
            cout << "readAsArray" << endl << endl;
        }
        else if (i=="readAsArray"){
            testing a;
            a.readAsArray();
        }
        else if (i=="fileImport"){
            testing a;
            a.fileImport();
        }
        else if (i=="qqq"){
            break;
        }
        else{
            cout << "Ihre Eingabe war ungenau oder fehlerhaft!" << endl << endl;
            return interface();
        }

    }
}

int** testing::fileImport(){
    ifstream infile;
    infile.open("charSwap.txt");
    int num;
    int ** pic;
    pic = new int*[89];
    for (int i = 0; i < 89; i++){
        infile >> num;
        pic[i]= new int[304];
        int j=0;
        while (j < 304){

            for(char& c : num){
                cout << c << "";
                break;
                if (c=='0'){
                    pic[i][j] = 0;
                }
                else if (c=='1'){
                    pic[i][j] = 1;
                }
                j++;
            }
        }
        cout << endl;
    }
    return pic;
}

int main(){
    interface();
}
