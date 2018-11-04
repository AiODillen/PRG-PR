//Visuelle Kryptographie

#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <sstream>

using namespace std;

class NBild {
    int width, length;
public:
    string** readAsArray();
    void writeAsArray(string**);
    void print(string**);
    void get_size();
    string read_index(string**,int ,int );
    string write_index(string**,int ,int,string );
};
void NBild::get_size()
{
    fstream file;
    file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/beispielbild_2.txt");
    if (!file) {
        cerr << "Unable to open file beispielbild_1";
        exit(1);   // call system to stop
    }
    string num;
    int rows=0,columns=0;
    while(file>>num){
        rows++;
        for (int n=0;n<num.size();n++) {
            columns=n+1;
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
string** NBild::readAsArray()
{
    fstream file;
    file.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/beispielbild_2.txt");
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
void NBild::writeAsArray(string** b)
{

    ofstream outfile;
    outfile.open("C:/Users/Sorin/CLionProjects/PRG-PR/PRG-PR/beispielbild_2.txt");
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
void interface() {
    string i;
    int a=0;
    NBild bild;
    bild.get_size();
    while (a==0){
        cout <<"Die möglichen Befehle sind:" << endl;
        cout << "Read" << endl;
        cout << "Change"<< endl;
        cout << "Exit" << endl;
        cin >> i;
        if ((i=="Read")||(i=="read")){
            string** b =bild.readAsArray();
            bild.writeAsArray(b);
            bild.print(b);
        }
        else if ((i=="change")||(i=="Change")){
            string** c =bild.readAsArray();
            int n,m;
            cout<<"Geben Sie Koordinaten:";
            cin>>n>>m;
            bild.write_index(c,n,m,"0");
            //bild.writeAsArray(c);
            bild.print(c); //Wenn man die  Datei printen moechte
        }
        else{
            a =1;
        }

    }
}

int main(){
    interface();
}
