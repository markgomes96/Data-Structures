
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
        fstream outfile("out.bin", ios::out | ios::binary);
        int outNum = 250;

        outfile.write ( (const char *) &outNum, sizeof (int) );
        outfile.close();

        int inNum;
        fstream infile("out.bin", ios::in | ios::binary);

        infile.read( (char *) &inNum, sizeof (int) );
        int NumItems = infile.gcount() / sizeof(int);

        cout << "Num Read In Was : " << inNum << endl;
        cout << "Num Items Read In Was : " << NumItems << endl;
        return 0;
}
