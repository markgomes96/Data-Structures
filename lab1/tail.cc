/*
*Developer : Mark Gomes
*1/10/19
*CSC 310
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string filename = argv[1];
	fstream file (filename.c_str(), ios::in | ios::app);

	string line;
	file.seekg(-2, ios::end);
	while ( file.good() )
	{
		getline(file, line);
		cout << line << endl;
	}

	file.clear();
	 
	return 0;
}

/*
int main(int argc, char *argv[])
{
        string filename = argv[1];
        fstream inOut (filename.c_str(), ios::in | ios::app);
        int count = 0;
        char ch;

        inOut.seekg(0);
        while ( inOut.get(ch) )
        {
                cout.put(ch);
                count++;
                if (ch == '\n')
                {
                        long mark = inOut.tellg();
                        inOut << count << ' ';
                        inOut.seekg(mark);
                }
        }
        inOut.clear();
        inOut << count << endl;

        cout << "[ " << count << " ]" << endl;
}
*/
