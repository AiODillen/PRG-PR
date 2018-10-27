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
    int counter(int**,int,int);
    void check(int**,int**);
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
    cout<<"Wo moechten Sie  das ein  Lebewesen gesetzt wird.";
    for (int i = 0; i < l; i++) {
        cout << "Geben Sie die Zeile ein";
        cin >> n;
        cout << "Geben Sie die Spalte ein";
        cin >> m;
        myarray[n-1][m-1]=1;
        cout<<"Es wurde/wurden " <<i+1<<" Zelle erstellt"<<endl;
    }
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



int main()
{
    string i; cout << "Eigene Größe festlegen? >>  "; cin >> i;
    if (i=="N" || i=="n"){
        GameofLife feld;
        int** old_array = feld.generate_2d_array();
        int** new_array = feld.generate_2d_array();
        cout << "Matrix 30x30 wurde erstellt:" << endl;
        feld.set_live(old_array);
        feld.print(old_array);
        feld.check(old_array,new_array);
        feld.print(new_array);

    }
    else if (i=="Y" || i=="y"){
        int j, h; cout << endl; cout << "Länge? >>  "; cin >> j; cout << endl;
        cout << "Breite? >>  "; cin >> h; cout << endl;
        GameofLife feld (j, h);
        int** old_array = feld.generate_2d_array();
        int** new_array = feld.generate_2d_array();
        cout << "Matrix " << j << "x" << h << " wurde erstellt:" << endl;
        feld.set_live(old_array);
        feld.print(old_array);
        feld.check(old_array,new_array);
        feld.print(new_array);
    }
    else{
        cout << "Leider werden nur Y - Yes und N - No akzeptiert\n";
        main();
    }
    return 0;
}
