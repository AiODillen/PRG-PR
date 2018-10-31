#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class GameofLife
{
    int width, length;
public:
    void print(int**);
    int **generate_2d_array();
    void set_live(int**);
    void set_dead(int**);
    int counter(int**,int,int);
    void check(int**,int**);
    void copy(int**,int**);
    void read_size();
    int** read_field();
    void output_field(int**);
    void set_size(int, int);
};

void GameofLife::set_size(int a, int b)
{
    width = a; length = b;
}

void GameofLife::output_field(int** field)
{
    ofstream exfile;
    exfile.open("output.txt");
    cout << endl;
    exfile << length << endl << width << endl;
    for (int x=0; x<width; x++){
        for (int y=0; y<length; y++){
            if (field[x][y]==0){
                exfile << 'o';
            }
            else if (field[x][y]==1){
                exfile << '*';
            }
        }
        exfile << endl;
    }
    cout << endl;

}
int** GameofLife::read_field()
{
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
                cout << c << " ";
                if (c=='o'){
                    array2D[i][j] = 0;
                }
                else if (c=='*'){
                    array2D[i][j] = 1;
                }
                j++;
            }
                }
            cout << endl;
        }
        return array2D;
    }


void GameofLife::read_size()
{
    int width_file, length_file;
    ifstream infile;
    infile.open("feld.txt");
    infile >> width_file;
    width = width_file;
    infile >> length_file;
    length = length_file;
}
int** GameofLife::generate_2d_array() {
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
void GameofLife::set_live(int** myarray)
{
    int n, m,l;
    cout << "Geben Sie Anzahl der lebende Zellen ein:";
    cin >> l;
    for (int i = 0; i < l; i++) {
        cout << "Geben Sie die Koordinaten  in der Form ein==>x y(wobei x Zeile und y Spalte entspricht)";
        cin >> n>> m;
        myarray[n-1][m-1]=1;
        cout<<"Es wurde lebende Zelle mit  Position("<<n<<","<<m<<" erstellt)"<<endl;
    }
    cout <<"Aktueller Zustand:";
    print(myarray);
}
void GameofLife::set_dead(int** myarray)
{
    int n, m,l;
    cout << "Geben Sie Anzahl der toten Zellen ein:";
    cin >> l;
    for (int i = 0; i < l; i++) {
        cout << "Geben Sie die Koordinaten  in der Form ein ==>x y(wobei x Zeile und y Spalte entspricht)";
        cin >> n>> m;
        myarray[n-1][m-1]=0;
        cout<<"Es wurde tote Zelle mit  Position("<<n<<","<<m<<" erstellt)"<<endl;
    }
    cout <<"Aktueller Zustand:";
    print(myarray);
}

int GameofLife::counter(int** myarray,int a,int b)
{
    int c=0;
    for (int i = a-1; i <= a+1; i++) {
        for (int j = b-1; j <= b+1; j++) {
            if ((myarray[(width+i)%width][(length+j)%length]==1)&&(i != a || j != b))
            {
                c+=1;
            }
            else{
                continue;
            }
        }
    }
    return c;
}

void GameofLife::check(int** myarray,int** myarray2)
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            int c=counter(myarray,i,j);
            if (myarray[i][j]==1){
                if ((c==3)||(c==2)){
                    myarray2[i][j]=1;
                }
                else if (c<2){
                    myarray2[i][j]=0;
                }
                else if (c>3){
                    myarray2[i][j]=0;
                }
                else{
                    continue;
                }
            }
            else  {
                if (c==3){
                    myarray2[i][j]=1;
                }
                else{
                    myarray2[i][j]=0;
                    continue;
                }
            }
        }
    }
}
void GameofLife::copy(int** myarray,int** myarray2)
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            myarray2[i][j] = myarray[i][j];
        }
    }
}

string input ()
{
    string inp; cin >> inp;
    if (inp=="Y" || inp=="y" || inp=="N" || inp=="n"){
        return inp;
    }
    else{
        cout << "Falsche Eingabe! Leider werden nur Y - Yes und N - No akzeptiert\n";
        return input();
    }
}

void read_file()
{
    GameofLife feld;
    feld.read_size();
    int** old_array = feld.read_field();
    int** new_array = feld.generate_2d_array();
    cout << "Matrix wurde erstellt:" << endl;
    feld.print(old_array);
    int a=0;
    while (a==0) {
        cout << "Was möchten Sie jetzt tun:" << endl;
        cout << " Go    - Das Spiel starten/um eine Zeiteinheit" << endl;
        cout << "  1    - Lebende Zellen  setzen/?ndern" << endl;
        cout << "  2    - Tote Zellen  setzen/?ndern" << endl;
        cout << " Exit  - Das Spiel beenden" << endl;
        string eingabe;
        cin>>eingabe;
        if ((eingabe=="Go") || (eingabe == "go")) {
            feld.check(old_array, new_array);
            feld.print(new_array);
            cout<<"Neuer Zustand";
            feld.copy(new_array,old_array);
        }
        else if (eingabe == "2") {
            feld.set_dead(old_array);
        }
        else  if (eingabe == "1") {
            feld.set_live(old_array);
        }
        else if ((eingabe == "Exit") || (eingabe == "exit")) {
            a=1;
        }
        else {
            cout<<"Falsche Eingabe!" << endl;
        }
    }
}

void read_input(int laenge, int weite)
{
    GameofLife feld;
    feld.set_size(laenge, weite);
    int** old_array = feld.generate_2d_array();
    int** new_array = feld.generate_2d_array();
    cout << "Matrix wurde erstellt:" << endl;
    feld.print(old_array);
    int a=0;
    while (a==0) {
        cout << "Was möchten Sie jetzt tun:" << endl;
        cout << " Go    - Das Spiel starten/um eine Zeiteinheit" << endl;
        cout << "  1    - Lebende Zellen  setzen/?ndern" << endl;
        cout << "  2    - Tote Zellen  setzen/?ndern" << endl;
        cout << " Exit  - Das Spiel beenden" << endl;
        string eingabe;
        cin>>eingabe;
        if ((eingabe=="Go") || (eingabe == "go")) {
            feld.check(old_array, new_array);
            feld.print(new_array);
            cout<<"Neuer Zustand";
            feld.copy(new_array,old_array);
        }
        else if (eingabe == "2") {
            feld.set_dead(old_array);
        }
        else  if (eingabe == "1") {
            feld.set_live(old_array);
        }
        else if ((eingabe == "Exit") || (eingabe == "exit")) {
            a=1;
        }
        else {
            cout<<"Falsche Eingabe!" << endl;
        }
    }
}

int main()
{
    cout << "Moechten sie aus einer Datei lesen? >>"; string i=input();
    if (i=="Y" || i=="y"){
        read_file();
    }
    else {
        cout << "Eigene Werte? >>"; string h=input();
        if (h=="Y" || h=="y"){
            int n, m; cout  << "x y"; cin >> n >> m;
            read_input(n, m);
        }
        else{
            read_input(30, 30);
        }


    }
    return 0;
}
