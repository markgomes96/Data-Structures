// A new header`
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char * argv[])
{
        string command = argv[1];
        command = "stat " + commomand + " > scratch";
        system(command.c_str());

        char ch;
        ifstream infile(argv[1]);
        infile.get(ch);
        if (!infile)
                cout << "File pointer dead -- it's a directory" << endl;
        else
                cout << "File pointer alive -- it's a file" << endl;

        return 0;
}

