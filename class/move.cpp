
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
        char ch;

        fstream infile("test", ios::in);
        infile.seekg (-2, ios::end);
        infile.get(ch);
        cout << ch << endl;

        return 0;
}
