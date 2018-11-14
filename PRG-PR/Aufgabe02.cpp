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
    string** overlay(string**, string**);
    void writeAsArray(string**, const string &i);//fur die Aufgabeteil a
    string read_index(string**,int ,int );//fur die Aufgabeteil a
    string write_index(string**,int ,int,string );//fur die Aufgabeteil a


};
int NBild::get_width(const string &i)
//get the number of rows
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
//get the number of  columns of array
{
    fstream file;
    file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+i+".txt");
    string num;
    int columns=0;
    while(file>>num){
        for (int n=0;n<=num.size();n++) { //go through all charcters of a row
            columns=n;
        }
    }
    length = columns;
    return length;
}
string** NBild::readAsArray(const string &file_name)
//save Adress of elements from  file in a 2-Dimensional Array
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
string** NBild::overlay(string** a,string** b)
//Overlay of elements from  2 different files  and  save them in 2D Array
{
    string** array2D;
    array2D = new string*[width];
    for (int i = 0; i < width; i++) {
        array2D[i]= new string[length];
        for (int j = 0; j < length; j++) {
            if ((a[i][j]==b[i][j])&&(a[i][j]=="0")){
                    array2D[i][j]="0";
            }
            else{
                array2D[i][j]="1";

            }
        }
    }
    return array2D;
}
void  NBild::writeAsArray(string** b, const string &i)
//Save elements of  an 2D array in a file
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
//read of a  value  on predefined position from an 2D array
{
    string value= array[a-1][b-1];;
    return value;
}
string NBild::write_index(string** array,int a,int b,string value)//change  a value  from a defined position in 2D array
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
//save new  values based on Dimension of normal file
{
    rows = a*2;
    columns = b*2;
}
string** CBild::create_matrix_key()
//create new 2D Array with rows and columns and default  value 0
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
//creates random key in the form of Blocks like A or B
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
//copy the values of 2D array in a txt file
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
//Decoding of Image  with Key
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
//Encoding of decoded Image and key
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
void visualcrypt(string i);
void visualcrypt_2files(string i,string g);
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
    cout<<"2 - Visualcrypt  mit einem Bild starten"<<endl;
    cout<<"3 - Visualcrypt  mit zwei Bilder  starten"<<endl;
    cout<<"4 - Programm Beenden"<<endl;
    cin>>i;
    if (i == 1){
        int n,m;
        cout<<"Geben Sie die Anzahl des Zeilen und Spalten ind der Format =>x y ein: "<<endl;
        cin>>n>>m;
        int rows = n;int columns=m;
        string file_name = random_bild(rows,columns);// creates a random Image file and get the  name of  created file
        visualcrypt(file_name);//starts Visualcrypt with random created Image
    }
    else if (i==2){
        string file_name;
        int a = 0;
        while (a==0) {//untill condition not fullfilled you get asked  to give an existing File Name!
            cout<<"Geben Sie der Name des Bildes ein:"<<endl;
            cin>>file_name;
            fstream file;
            file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/" + file_name + ".txt");
            if (!file) {//check if  File exists
                cerr << "Leider existiert der  " + file_name + ".txt nicht";
                cout<<endl;
            }
            else{
                a=1;
                file.close();
                visualcrypt(file_name);//starting Visualcrypt with a File
            }
        }
    }
    else if (i==3){
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
            }
        }
        string file_name2;
        int b = 0;
        while (b==0) {
            cout<<"Geben Sie der Name des zweiten  Bildes ein:"<<endl;
            cin>>file_name2;
            fstream file;
            file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/" + file_name2 + ".txt");
            if (!file) {
                cerr << "Leider existiert der  " + file_name2 + ".txt nicht";
                cout<<endl;
            }
            else{
                b=1;
                file.close();
            }
        }
        visualcrypt_2files(file_name,file_name2);//starting Visualcrypt for 2  Images
        main();

    }
    else if (i==4){
        exit(1);//Ends programm
    }
    else{
        cout<<"Falsche Eingabe!"<<endl;
        main();
    }
}
void visualcrypt(string i)
//Visualcrypt function for 1 File
{
    cout<<"Visualcrypt ist gestartet"<<endl;
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
        cout << "4 --  Gehe zu Hauptmenu" << endl;
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
            cout << "Datei " + e + ".txt wurde  erstellt!" << endl;
        }
        else if (i=="4"){
            a = 1;
        }
        else{
            cout<<"Falsche Eingabe";
        }
    }
    main();
}
void visualcrypt_2files(string i,string g)
//Visualcrypt function for 2 File
{

    NBild file;
    file.get_length(i);file.get_width(i);
    string** datei1 =file.readAsArray(i);
    string** datei2 =file.readAsArray(g);
    string** result = file.overlay(datei1,datei2);
    file.writeAsArray(result,"overlay_result");
    cout<<"Overlay wurde in overlay_result gespeichert"<<endl;
    main();

}
