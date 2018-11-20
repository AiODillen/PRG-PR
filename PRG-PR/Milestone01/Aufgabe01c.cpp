#include <iostream>  // for in-/output
#include <fstream>   // for opening files
//#include <string.h>  // for reading from file

using namespace std;  //only/standard namespace used

int check_int();

class GameofLife  // main class used for the game
{
    int width, length; // private variables used for the field size
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
// function to access and edit the private size variable
{
    width = a; length = b;
}

void GameofLife::output_field(int** field)
// prints the current field and dimensions to a textfile
{
    ofstream exfile;
    exfile.open("output.txt"); // opens the output file/creates it
    cout << endl;
    exfile << length << endl << width << endl; // writes dimensions in the first two lines
    for (int x=0; x<width; x++){
        for (int y=0; y<length; y++){
            if (field[x][y]==0){
                exfile << 'o';
            }
            else if (field[x][y]==1){
                exfile << '*';
            } //prints every point of the line to the file
        }
        exfile << endl;  //proceeds to the next line
    }
    cout << endl;

}
int** GameofLife::read_field()
//reads a given field with dimensions from a textfile
{
    char trash[100];
    ifstream infile;
    infile.open("feld.txt");
    infile >> trash;
    infile >> trash;  //cuts the dimension inputs from the file
    string str;
    int** array2D; //creates double-pointer to a new array
    array2D = new int*[width];  //creates first dimension
    for (int i = 0; i < width; i++) {
        infile >> str;
        array2D[i]= new int[length];  //creates second dimension
        int j=0;
        while (j < length){
            for(char& c : str) {
                if (c=='o'){
                    array2D[i][j] = 0;
                }
                else if (c=='*'){
                    array2D[i][j] = 1;
                }
                j++;
            } //filld array with data depending on input
                }
            cout << endl;
        }
        return array2D;
    }


void GameofLife::read_size()
//reads size of input files' field
{
    int width_file, length_file;
    ifstream infile;
    infile.open("feld.txt");
    infile >> width_file;
    width = width_file;
    infile >> length_file;
    length = length_file;
}
int** GameofLife::generate_2d_array()
//creates array with 0s depending on size
{
    int** array2D;
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
//prints current field in the console
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
//sets a given number of cells alive
{
    cout << "Geben Sie Anzahl der zu setzenden lebende Zellen ein >>";
    int l = check_int();
    for (int i = 0; i < l; i++) {
        cout << "Geben Sie die x-Koordinate ein >>"; int n = check_int();
        cout << "Geben sie die y-Koordinate ein >>"; int m = check_int();
        myarray[n-1][m-1]=1;  // sets n,m alive
        cout<<"Es wurde eine lebende Zellen an Position("<<n<<","<<m<<" erstellt)"<<endl;
    }
    cout <<"Aktueller Zustand:";
    print(myarray);
}
void GameofLife::set_dead(int** myarray)
//sets a given number of cells dead
{
    cout << "Geben Sie Anzahl der zu setzenden toten Zellen ein >>";
    int l = check_int();
    for (int i = 0; i < l; i++) {
        cout << "Geben Sie die x-Koordinate ein >>"; int n = check_int();
        cout << "Geben sie die y-Koordinate ein >>"; int m = check_int();
        myarray[n-1][m-1]=0;
        cout<<"Es wurde eine tote Zelle an Position("<<n<<","<<m<<" erstellt)"<<endl;
    }
    cout <<"Aktueller Zustand:";
    print(myarray);
}

int GameofLife::counter(int** myarray,int a,int b)
//counts the living neighbors of a cell
{
    int c=0;
    for (int i = a-1; i <= a+1; i++) {
        for (int j = b-1; j <= b+1; j++) {
            if ((myarray[(width+i)%width][(length+j)%length]==1)&&(i != a || j != b))
            //checks if there are neighbors; %length also checks on the opposing side
            //of the field if the target cell is on the edge of the fied
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
//checks the condition of a cell in the next step depending on number of neighbors
//in the first step and sets their value in the next step
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            int c=counter(myarray,i,j);  //counts the neighbors
            if (myarray[i][j]==1){  //changes cell depending on the counter
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
//copys the new array into the old one
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            myarray2[i][j] = myarray[i][j];
        }
    }
}
int check_int()
 {
   int x;
    cin >> x;
    while(cin.fail()) {  //checks for TypeError
        cout << "Kein Integer" << endl;
        cin.clear();
        cin.ignore(256,'\n');  // ignores TypeError
        cin >> x;
    }
    return x;
 }

string input ()
//checks for yes no input
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
//continues with the programm reading all data from a file
{
    GameofLife feld;  //create object
    feld.read_size();   //set the size of the field from file
    int** old_array = feld.read_field();  //sets field from file
    int** new_array = feld.generate_2d_array();  //empty array
    cout << "Feld wurde erstellt:" << endl;
    feld.print(old_array);  //prints current array
    int a=0;
    while (a==0) {  //starts interface
        cout << "Was moechten Sie jetzt tun? >>" << endl;
        cout << " Go    - Das Spiel starten/um eine Zeiteinheit" << endl;
        cout << "  1    - Lebende Zellen  setzen/?ndern" << endl;
        cout << "  2    - Tote Zellen  setzen/?ndern" << endl;
        cout << "  3    - Feld und Dimensionen in Datei ausgeben" << endl;
        cout << " Exit  - Das Spiel beenden" << endl;
        string eingabe;
        cin>>eingabe;  //continues with input command
        if ((eingabe=="Go") || (eingabe == "go")) {
            feld.check(old_array, new_array);  //calculates next step
            feld.print(new_array);  //output new field after step
            cout<<"Neuer Zustand:";
            feld.copy(new_array,old_array);  //sets the new array the current array
        }
        else if (eingabe== "3"){
            feld.output_field(old_array);  //prints data to file
            cout << "Feld in Datei 'output.txt' gespeichert" << endl;
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
//starts the game with user input size and field
{
    GameofLife feld;  //initialize object
    feld.set_size(laenge, weite);  //set size by user input
    int** old_array = feld.generate_2d_array();
    int** new_array = feld.generate_2d_array();
    cout << "Feld wurde erstellt:" << endl;
    feld.print(old_array);
    int a=0;
    while (a==0) {
        cout << "Was moechten Sie jetzt tun? >>" << endl;
        cout << " Go    - Einen Zeitschritt durchfuehren" << endl;
        cout << "  1    - Lebende Zellen  setzen/aendern" << endl;
        cout << "  2    - Tote Zellen setzen/aendern" << endl;
        cout << "  3    - Feld und Dimensionen in Datei ausgeben" << endl;
        cout << " Exit  - Das Spiel beenden" << endl;
        string eingabe;
        cin>>eingabe;
        if ((eingabe=="Go") || (eingabe == "go")) {
            feld.check(old_array, new_array);
            feld.print(new_array);
            cout<<"Neuer Zustand";
            feld.copy(new_array,old_array);
        }
        else if (eingabe== "3"){
            feld.output_field(old_array);
            cout << "Feld in Datei 'output.txt' gespeichert" << endl;
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
        cout << "Eigene Werte fuer Groesse des Feldes angeben? >>"; string h=input();
        if (h=="Y" || h=="y"){
            cout << "Geben sie die Breite des Feldes als Integer an >>"; int n = check_int();
            cout << "Geben sie die Hoehe des Feldes als Integer an >>"; int m = check_int();
            read_input(n, m);
        }
        else{
            read_input(30, 30);  //sets size 30x30 by default
        }


    }
    return 0;
}
