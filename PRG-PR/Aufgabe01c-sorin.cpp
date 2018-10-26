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
void GameofLife::set_live(int** myarray) {
    int n, m,l;
    cout << "Geben Sie Anzahl der lebende Zellen ein:";
    cin >> l;
    cout<<"Wo moechten Sie  das ein  Lebewesen gesetzt wird.";
    for (int i = 0; i < l; i++) {
        cout << "Geben Sie die Zeile ein";
        cin >> n;
        cout << "Geben Sie die Spalte ein";
        cin >> m;
        myarray[n-1][m-1]=1;
        cout<<"Es wurde " <<i+1<<" Zelle erstellt"<<endl;
    }

}

int main()
{
    string i; cout << "Eigene Größe festlegen? >>  "; cin >> i;
    if (i=="N" || i=="n"){
        GameofLife feld;
        int** new_array = feld.generate_2d_array();
        feld.set_live(new_array);
        feld.print(new_array);
    }
    else if (i=="Y" || i=="y"){
        int j, h; cout << endl; cout << "Länge? >>  "; cin >> j; cout << endl;
        cout << "Breite? >>  "; cin >> h; cout << endl;
        GameofLife feld (j, h);
        int** new_array = feld.generate_2d_array();
        feld.set_live(new_array);
        feld.print(new_array);
    }
    else{
        cout << "Leider werden nur Y - Yes und N - No akzeptiert\n";
        main();
    }
    return 0;
}
