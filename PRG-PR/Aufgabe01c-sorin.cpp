#include <iostream>

using namespace std;

class GameofLife
{
    int width,length;
public:
    void set_size();
    void set_size(int,int);
    int** generate_2d_array();
};

void GameofLife::set_size(int a , int b)
{
    width = a;
    length = b;
}
void GameofLife::set_size()
{
    width = 30;
    length = 30;
}
int** GameofLife::generate_2d_array() {
    cout << "Matrix " << width << "x" << length << " was created:" << "\n";
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


void print(int** myarray,int a,int b) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            cout << myarray[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    GameofLife table_no_size{};
    table_no_size.set_size();
    int** my2DArray_default = table_no_size.generate_2d_array();
    print(my2DArray_default,30,30);
    GameofLife table_with_size{};
    table_with_size.set_size(9,9);//naturlich hier  werden die Eingabewerten eingesetzt
    int** my2DArray_sized = table_with_size.generate_2d_array();
    print(my2DArray_sized,9,9);

    return 0;
}
