// Mark Gomes
// CSC 310 - Dr. Digh
// 2/18/19
// Lab 3

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

void checkFile(ifstream &fp)
{
    if(!fp.is_open())
    {
        cout << "Error : File Name Not Found" << endl;
        exit(1);
    }
    char ch;
    fp.get(ch);
    if(!fp)
    {
        cout << "Error : Inputed File Is Directory" << endl;
        exit(1);
    }
    fp.seekg(0, ios::beg);
}

string charToOct(char c)
{
    int decNum = (int)c;
    int octNum[100]; 

    int i = 0; 
    while (decNum != 0) 
    { 
        octNum[i] = decNum % 8; 
        decNum = decNum / 8; 
        i++; 
    } 

    stringstream ss;
    //print in reverse order 
    for (int j = i - 1; j >= 0; j--) 
        ss << octNum[j];

    return ss.str();
}

int main(int argc, char *argv[])
{
    bool cflag = false, iflag = false, nflag = false;
    int ignNum = 0;

    if(argc >= 3 || argc <= 5)
    {
        //check additional flags
        for(int i = 1; i < argc-2; i++)
        {
            if(!nflag)
            {
                if(strcmp( argv[i], "-c" ) == 0)
                {
                    cflag = true;
                }
                else if(strcmp( argv[i], "-i" ) == 0)
                {
                    iflag = true;
                    nflag = true;
                }
                else
                {
                    cout << "Error : Illegal option for flags" << endl;
                    exit(1);
                }
            }
            else
            {
                ignNum = atoi(argv[i]);
                nflag = false;
            }
        }
    
        if(nflag)
        {
            cout << "Error : Illegal option for flags" << endl;
            exit(1);
        }
    }
    else
    {
        cout << "Error : Illegal number of command arguments" << endl;
        exit(1);
    }

    ifstream fileA(argv[argc-2]);        //open files and check if valid
    checkFile(fileA);

    ifstream fileB(argv[argc-1]);
    checkFile(fileB);

    char chA, chB; 
    int byteOS = 1, lineCount = 1;
    bool eflag = false;
    while(fileA.get(chA))     //go through fileA
    {
        fileB.get(chB);     //iterate by char

        if(fileB.eof())        //check for EOF for B file
        {
            cout << "cmp: EOF on " << argv[argc-1] << endl;
            eflag = true;
            break;
        }

        if(byteOS > ignNum || !iflag)       //handles -i flag
        {
            if(chA != chB)      //compare ch between both files
            {
                if(!cflag)                  //handles -c flag
                {
                    cout << argv[argc-2] << " " << argv[argc-1] << " differ: byte " << byteOS << ", Line " << lineCount << endl;
                }
                else
                {
                    cout << argv[argc-2] << " " << argv[argc-1] << " differ: char " << byteOS << ", Line " << lineCount 
                            << " is " << charToOct(chA) << " " << chA << " " << charToOct(chB) << " " << chB << endl;
                }

                eflag = true;
                break;
            }
        }

        if(chA == '\n')         //check for next line
            lineCount++;

        byteOS++;
    }

    if(eflag == false)      //check for EOF for A file
    {
        fileB.get(chB);
        if(!fileB.eof())
            cout << "cmp: EOF on " << argv[argc-2] << endl;
    }
}
