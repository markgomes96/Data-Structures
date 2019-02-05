
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
        
        //char ch;

        fstream infile("test", ios::in);
        /*
        infile.seekg (-2, ios::end);
        infile.get(ch);
        cout << ch << endl;
        */

        char ch;
        bool flag;

        flag = false;
        while (infile.get(ch))
        {
            if(ch == ' ' ){
                cout << infile.tellg() << endl;
            }
        }

        return 0;
}
