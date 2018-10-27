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
    void set_live(int**);
    void set_dead(int**);
    int counter(int**,int,int);
    void check(int**,int**);
    void copy(int**,int**);
};

GameofLife::GameofLife(int x, int y) {width = x; length = y;}
GameofLife::GameofLife() {width = 30; length = 30;}

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
int main()
{
    cout << "               Wilkommen in THE GAME OF life - Implementation in C++" << endl;
    cout << "Deafult Größe ist 30x30.Möchten Sie eine eigene Größe festlegen(y/n)? >>  "<< endl;
    string i;cin >> i;
    if (i=="N" || i=="n"){
        GameofLife feld;
        int** old_array = feld.generate_2d_array();
        int** new_array = feld.generate_2d_array();
        cout << "Matrix 30x30 wurde erstellt:" << endl;
        int a=0;
        while (a==0) {
            cout << "Was möchten Sie jetzt tun:" << endl;
            cout << " Go    - Das Spiel starten/um eine Zeiteinheit" << endl;
            cout << "  1    - Lebende Zellen  setzen/?ndern" << endl;
            cout << "  2    - Tote Zellen  setzen/?ndern" << endl;
            cout << "  3    - Das Spiel neu starten" << endl;
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
            else if ((eingabe == "Exit") || (eingabe == "exit")) {
                a=1;
            }
            else {
                cout<<"Falsche Eingabe!" << endl;
            }
        }

    }
    else if (i=="Y" || i=="y"){
        int j, h; cout << "Länge und Breite in der Form ==> x y?  "; cin >>j>>h; cout << endl;
        GameofLife feld (j, h);
        int** old_array = feld.generate_2d_array();
        int** new_array = feld.generate_2d_array();
        cout << "Matrix "<<j<<"x"<<h<<" wurde erstellt" << endl;
        int a=0;
        while (a==0) {
            cout << "Was möchten Sie jetzt tun:" << endl;
            cout << " Go    - Das Spiel starten/um eine Zeiteinheit" << endl;
            cout << "  1    - Lebende Zellen  setzen/?ndern" << endl;
            cout << "  2    - Tote Zellen  setzen/?ndern" << endl;
            cout << "  3    - Das Spiel neu starten" << endl;
            cout << " Exit  - Das Spiel beenden" << endl;
            string eingabe;
            cin>>eingabe;
            if ((eingabe=="Go") || (eingabe == "go")) {
                feld.check(old_array, new_array);
                cout<<"Neuer Zustand";
                feld.print(new_array);
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
            else if ((eingabe == "Exit") || (eingabe == "exit")) {
                a=1;
            }
            else {
                cout<<"Falsche Eingabe!" << endl;
            }
        }
    }
    else{
        cout << "Falsche Eingabe!" << endl;
        cout << "Leider werden nur Y - Yes und N - No akzeptiert\n";
        main();
    }
    return 0;
}
