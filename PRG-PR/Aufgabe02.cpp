//Visuelle Kryptographie

#include <fstream>
#include <iostream>
#include <cstdlib>     /* srand, rand */


using namespace std;


class NBild {
    int width, length;
public:
    string** readAsArray(const string &);
    void print(string**);//print Befehl,kann man spater loschen
    void get_size(const string &);
    void create_key();
    void code(string**,string**);
    void decode(string**,string**);
    string read_index(string**,int ,int );//fur die Aufgabestellung notwendig
    string write_index(string**,int ,int,string );//fur die Aufgabestellung notwendig

};
void NBild::get_size(const string &i)
{
    fstream file;
    file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/"+i+".txt");
    if (!file) {
        cerr << "Unable to open file "+i+".txt";
        exit(1);   // call system to stop
    }
    string num;
    int rows=0,columns=0;
    while(file>>num){
        rows++;
        for (int n=0;n<num.size();n++) {
            columns=n;
        }
    }
    width = rows; length = columns;
}
void NBild::print(string** array)
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
void NBild::create_key()
{
    ofstream outfile;
    outfile.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/bild_key.txt");
    for (int x = 0; x < width; x++){
        for (int y = 0; y < length; y++){

            int a;
            a=rand()%2;
            if (a==1){
                outfile<<"1";
            }
            else{
                outfile<<"0";
            }
        }
        outfile<<endl;
    }
}
void NBild::code(string**a,string** b)
{
    ofstream outfile;
    outfile.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/bild_coded.txt");
    for (int x = 0; x < width; x++){
        for (int y = 0; y < length; y++){
            if (a[x][y]==b[x][y]){  //XOR Verfahren angewendet fur one time pad!
                outfile<<"0";
            }
            else{
                outfile<<"1";
            }
        }
        outfile<<endl;
    }
}
void NBild::decode(string**a,string** b)
{
    ofstream outfile;
    outfile.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/bild_decoded.txt");
    for (int x = 0; x < width; x++){
        for (int y = 0; y < length; y++){
            if (a[x][y]==b[x][y]){  //XOR Verfahren angewendet fur one time pad!
                outfile<<"0";
            }
            else{
                outfile<<"1";
            }
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
/*
class CBild:NBild {
public:
    string** block();
    void print_block(string**);
};
void CBild::print_block(string** b)
{
    for (int x=0; x<2; x++){
        for (int y=0; y<2; y++){
            cout << b[x][y] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
string** CBild::block(){
    string** matrix;
    matrix = new string*[2];
    for (int x = 0; x < 2; x++) {
        matrix[x]= new string[2];
        for (int y = 0; y < 2; y++) {
            if (y>0){
                if (matrix[x][y-1]=="0"){
                    matrix[x][y]="1";
                }
                else{
                    matrix[x][y]="0";
                }
            }
            else{
                if (x>0){
                    if (matrix[x-1][y]=="0"){
                        matrix[x][y]="1";
                    }
                    else{
                        matrix[x][y]="0";
                    }
                }
                else{
                    //srand(time(NULL));         //-- initializes random seed
                    int a = rand() % 2;//-- generate random integer between 0 and 1
                    if(a == 0){
                        cout<<"Block A wird erstellt";
                        matrix[x][y]='0';
                    }
                    else {
                        cout<<"Block B wird erstellt";
                        matrix[x][y]="1";
                    }
                }
            }

        }
    }
    return matrix;
}
*/
void interface() {
    string i;
    cout<<"Welche Datei moechten Sie einlesen?"<<endl;
    cin>>i;
    string c="bild_key";
    string d="bild_coded";
    string e="bild_decoded";
    int a=0;
    NBild bild{};
    bild.get_size(i);
    string** datei =bild.readAsArray(i);
    while (a==0){
        cout <<"Die möglichen Befehle sind:" << endl;
        cout << "1 --  Schlussel generieren" << endl;
        cout << "2 --  Datei verschlusseln"<< endl;
        cout << "3 --  Datei entsschlusseln"<< endl;
        cout << "Exit" << endl;
        cin >> i;
        if (i=="1"){
            bild.create_key();
            cout<<"Schlussel wurde generiert!"<<endl;
        }
        else if (i=="2"){
            string** key_matrix=bild.readAsArray(c);
            bild.code(datei,key_matrix);
            cout<<"Datei Bild_coded wurde  erstellt!"<<endl;
        }
        else if (i=="3"){
            string** key_matrix=bild.readAsArray(c);
            string** coded_datei = bild.readAsArray(d);
            bild.decode(coded_datei,key_matrix);
            cout<<"Datei Bild_decoded wurde  erstellt!"<<endl;
        }
        else{
            a =1;
        }

    }
}

int main(){
    interface();
}
