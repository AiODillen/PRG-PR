//Visuelle Kryptographie

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


class NBild {
public:
    int width, length;
    int get_width(const string &);
    int get_length(const string &);
    string** readAsArray(const string &);
    void writeAsArray(string**, const string &i);//fur die Aufgabeteil a
    string read_index(string**,int ,int );//fur die Aufgabeteil a
    string write_index(string**,int ,int,string );//fur die Aufgabeteil a


};
int NBild::get_width(const string &i)
{
    fstream file;
    file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+i+".txt");
    string num;
    int rows=0;
    while(file>>num){
        rows++;
    }
    width = rows;
    return width;
}
int NBild::get_length(const string &i)
{
    fstream file;
    file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+i+".txt");
    string num;
    int columns=0;
    while(file>>num){
        for (int n=0;n<=num.size();n++) {
            columns=n;
        }
    }
    length = columns;
    return length;
}
string** NBild::readAsArray(const string &file_name)
{
    ifstream file;
    file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+file_name+".txt");
    string num;
    string ** array2D;
    array2D = new string*[width];
    for (int i = 0; i < width; i++){
        file>>num;
        array2D[i]= new string[length];
        for (int j = 0; j < length; j++) {
            array2D[i][j]= num[j];
        }
    }
    return array2D;
}
void  NBild::writeAsArray(string** b, const string &i)
{
    ofstream outfile;
    outfile.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+i+".txt");
    for (int x = 0; x < width; x++){
        for (int y = 0; y < length; y++){
            outfile<<b[x][y];
        }
        outfile<<endl;
    }
}
string NBild::read_index(string** array,int a,int b)
{
    string value= array[a-1][b-1];;
    return value;
}
string NBild::write_index(string** array,int a,int b,string value)
{
    array[a][b]= value;
    return value;
}

class CBild {
public:
    int rows,columns;
    void get_size(int,int);
    string** create_matrix_key();
    void create_block_key(string**);
    void  writeAsArray(string**, const string &);
    void code(string**,string**,string**);
    void decode(string**,string**,string**);

};
void CBild::get_size(int a,int b)
{
    rows = a*2;
    columns = b*2;
}
string** CBild::create_matrix_key()
{
    string** array2D;
    array2D = new string*[rows];
    for (int i = 0; i < rows; i++) {
        array2D[i]= new string[columns];
        for (int j = 0; j < columns; j++) {
            array2D[i][j]="0";
        }
    }
    return array2D;
}
void CBild::create_block_key(string** key)
{
    for (int x = 0; x < rows; x+= 2) {
        for (int y = 0; y < columns; y+= 2){
            int random = rand() % 2;
            if (random==0){
                key[x][y]="0";
                key[x][y+1]="1";
                key[x+1][y]="1";
                key[x+1][y+1]="0";
            }
            else{
                key[x][y]="1";
                key[x][y+1]="0";
                key[x+1][y]="0";
                key[x+1][y+1]="1";
            }
        }
    }
}
void  CBild::writeAsArray(string** b, const string &i)
{
    ofstream outfile;
    outfile.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+i+".txt");
    for (int x = 0; x < rows; x++){
        for (int y = 0; y < columns; y++){
            outfile<<b[x][y];
        }
        outfile<<endl;
    }
}
void CBild::code(string**a,string** b,string** c)
{
    int n=0,m=0;
    for (int x = 0; x < rows; x+=2){
        for (int y = 0; y < columns; y+=2){
            if (a[n][m]==b[x][y]){
                m +=1;
                c[x][y]="1";
                c[x][y+1]="0";
                c[x+1][y]="0";
                c[x+1][y+1]="1";
            }
            else{
                m +=1;
                c[x][y]="0";
                c[x][y+1]="1";
                c[x+1][y]="1";
                c[x+1][y+1]="0";
            }
        }
        n +=1;
        m=0;

    }
}
void CBild::decode(string**a,string** b,string** c)
{
    for (int x = 0; x < rows; x+=2){
        for (int y = 0; y < columns; y+=2){
            if (a[x][y]=="1" && b[x][y]=="1"){
                c[x][y]="1";
                c[x][y+1]="0";
                c[x+1][y]="0";
                c[x+1][y+1]="1";
            }
            else if (a[x][y]=="0" && b[x][y]=="0"){
                c[x][y]="0";
                c[x][y+1]="1";
                c[x+1][y]="1";
                c[x+1][y+1]="0";
            }
            else{
                c[x][y]="0";
                c[x][y+1]="0";
                c[x+1][y]="0";
                c[x+1][y+1]="0";
            }
        }
    }
}
void visualcrypt(string file_name)
{
    cout<<"Visualcrypt ist gestartet"<<endl;
    string i = file_name;
    string c=i+"_key";
    string d=i+"_coded";
    string e=i+"_decoded";
    int a=0;
    NBild bild{};
    CBild bild2{};
    int rows =bild.get_width(i);
    int columns =bild.get_length(i);
    bild2.get_size(rows,columns);
    string** datei =bild.readAsArray(i);
    string** key =bild2.create_matrix_key();
    string** datei_coded =bild2.create_matrix_key();
    while (a==0) {
        cout << "Die möglichen Befehle sind:" << endl;
        cout << "1 --  Schlussel generieren" << endl;
        cout << "2 --  Datei verschlusseln" << endl;
        cout << "3 --  Datei entsschlusseln" << endl;
        cout << "Exit" << endl;
        cin >> i;
        if (i == "1") {
            bild2.create_block_key(key);
            bild2.writeAsArray(key, c);
            cout << "Schlussel "+c+".txt wurde generiert!" << endl;

        } else if (i == "2") {
            bild2.code(datei, key, datei_coded);
            bild2.writeAsArray(datei_coded, d);
            cout << "Datei "+d+".txt wurde  erstellt!" << endl;
        } else if (i == "3") {
            string **datei_decoded = bild2.create_matrix_key();
            bild2.decode(datei_coded, key, datei_decoded);
            bild2.writeAsArray(datei_decoded, e);
            cout << "Datei "+e+".txt wurde  erstellt!" << endl;
        } else {
            a = 1;
        }
    }
}
string random_bild(int rows,int columns)
{
    cout<<"Geben sie einer Name fur  Bild: "<<endl;
    string a;
    cin>>a;
    ofstream outfile;
    outfile.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+a+".txt");
    string array2D[rows][columns];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int random = rand() % 2;
            if (random==0){
                array2D[i][j]="0";
                outfile<<array2D[i][j];
            }
            else{
                array2D[i][j]="1";
                outfile<<array2D[i][j];
            }

        }
        outfile<<endl;
    }
    return a;
}

int main()
{
    int i;
    cout<<"Was moechten Sie tun:"<<endl;
    cout<<"1 - Ein bild mit zufalliger Punkten erstellen"<<endl;
    cout<<"2 - Visualcrypt  mit eigenem Bild starten"<<endl;
    cin>>i;
    if (i == 1){
        int n,m;
        cout<<"Geben Sie die Anzahl des Zeilen und Spalten ind der Format =>x y ein: "<<endl;
        cin>>n>>m;
        int rows = n;int columns=m;//Aufgabenteil c
        string file_name = random_bild(rows,columns);// Aufgabenteil c
        visualcrypt(file_name);
    }
    else if (i==2){
        string file_name;
        int a = 0;
        while (a==0) {
            cout<<"Geben Sie der Name des Bildes ein:"<<endl;
            cin>>file_name;
            fstream file;
            file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/" + file_name + ".txt");
            if (!file) {
                cerr << "Leider existiert der  " + file_name + ".txt nicht";
                cout<<endl;
            }
            else{
                a=1;
                file.close();
                visualcrypt(file_name);
            }
        }
    }
    else{
        cout<<"Falsche Eingabe!"<<endl;
        main();
    }
}
