
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string s = "our_program 0.01";
    char ch;
    istringstream is(s);
    is >> s >> ch;
    cout << s << " " << endl << ch  << endl;
    
   /*
        fstream outfile("mark.dat", ios::out | ios::ate);
        char outNum = 'X';

        outfile.seekp(4, ios::beg);
        outfile.write ( (const char *) &outNum, sizeof(char) );
        outfile.close();

        int inNum;
        fstream infile("out.bin", ios::in | ios::binary);

        infile.read( (char *) &inNum, sizeof (int) );
        int NumItems = infile.gcount() / sizeof(int);

        cout << "Num Read In Was : " << inNum << endl;
        cout << "Num Items Read In Was : " << NumItems << endl;
*/
        return 0;
}
