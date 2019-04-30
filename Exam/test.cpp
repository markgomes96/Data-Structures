#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

bool isFile(string dn);

int main(int argc, char *argv[])
{
    /*
    if(isFile(argv[1]))
        cout << "True" << endl;
    else
        cout << "False" << endl;
    */

    char* s = new char[25];
    char* sp = s;
    string line = ""; int i, j;
    cin >> j;
    strcpy(s, "0123456789");
    for(i = 0; i < j; i++)
    {
        *s = ('0' + i%10);
        line += *s;
        s++;
    }

    cout << "s = " << s << "\nsp = " << sp << "\nline = " << line << endl;
    return 0;
}

bool isFile(string dn)
{
    ifstream fp(dn);
    if(!fp.is_open())
    {
        return false;
    }
    return true;
}
