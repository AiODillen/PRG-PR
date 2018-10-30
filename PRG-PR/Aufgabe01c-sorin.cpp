#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class GameofLife
{
    int width, length;
public:
    GameofLife();
    GameofLife(int, int);
    void print(int**);
    int **generate_2d_array();
    void set_live(int**);
    void set_dead(int**);
    int counter(int**,int,int);
    void check(int**,int**);
    void copy(int**,int**);
    void read_size();
    int** read_field();
    void write_field(int**);
};

GameofLife::GameofLife(int x, int y) {width = x; length = y;}
GameofLife::GameofLife() {width = 30; length = 30;}

void GameofLife::write_field(int** field)
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
GameofLife size_quest()
{
    cout << "Deafult Größe ist 30x30.Möchten Sie eine eigene Größe festlegen(y/n)? >>  "<< endl;
    string i=input();
    if (i=="N" || i=="n"){
        GameofLife feld;
        return feld;
    }
    else if (i=="Y" || i=="y"){
        cout << "Aus Datei Lesen? >>"; string k=input();
        if  (k=="Y" || k=="y"){
            GameofLife feld; feld.read_size();
            return feld;
        }
        int j, h; cout << "Länge und Breite in der Form ==> x y?  "; cin >>j>>h; cout << endl;
        GameofLife feld (j, h);
        return feld;
    }
}
int** field_quest(GameofLife field)
{
    cout << "Feld aus Datei lesen? >>"; string i=input();
    if (i=="Y" || i=="y"){
        return field.read_field();
    }
    else{
        return field.generate_2d_array();
    }
}
int main()
{
    cout << "               Wilkommen in THE GAME OF life - Implementation in C++" << endl;
    GameofLife feld = size_quest();
    int** old_array = field_quest(feld);
    int** new_array = feld.generate_2d_array();
    cout << "Matrix wurde erstellt:" << endl;
    feld.print(old_array);
    int a=0;
    while (a==0) {
        cout << "Was möchten Sie jetzt tun:" << endl;
        cout << " Go    - Das Spiel starten/um eine Zeiteinheit" << endl;
        cout << "  1    - Lebende Zellen  setzen/?ndern" << endl;
        cout << "  2    - Tote Zellen  setzen/?ndern" << endl;
        cout << "  3    - Das Spiel neu starten" << endl;
        cout << "  4    - Das Feld in Datei ausgeben" << endl;
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
        else if (eingabe == "3") {
            main();
        }
        else if (eingabe == "4"){
            feld.write_field(old_array);
            feld.print(old_array);
        }
        else if ((eingabe == "Exit") || (eingabe == "exit")) {
            a=1;
        }
        else {
            cout<<"Falsche Eingabe!" << endl;
        }
    }
    return 0;
}
