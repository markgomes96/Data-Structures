/*
*Developer : Mark Gomes
*1/10/19
*CSC 310
*prints out last n lines of a file
*/

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void HandleFlags(int &numlines, int argc, char* argv[]);
void MoonWalkThroughFile(fstream &file, int numlines);
void PrintLastLines(fstream &file);

int main(int argc, char *argv[])
{
    int numlines;      //stores n lines
    
    HandleFlags(numlines, argc, argv);    //gets n lines from command flags

    string filename = argv[2];          //read in file name
    fstream file (filename.c_str(), ios::in | ios::app);

    MoonWalkThroughFile(file, numlines);      //go backwards through file till n line from end

    PrintLastLines(file);    //print last n lines of file
}

void HandleFlags(int &numlines, int argc, char* argv[])
{
    char* numflag = argv[1];        //read in n lines flag
    stringstream ss;
    ss << numflag[1];
    ss >> numlines;
}

void MoonWalkThroughFile(fstream &file, int numlines)
{
    char ch = ' ';
    file.seekg(0, ios::end);
    for(int i = 0; i < numlines; i++)      //place read head at start of last n lines
    {
        file.seekg(-2, ios::cur);
        while( ch != '\n' )     //iterate backwards to end of line
        {
            if( !file.good() )      //check if numlines is greater than total file lines
            {
                file.clear();
                file.seekg(0, ios::beg);
                goto end;
            }
            else
            {
                file.get(ch);                //get char at read heard
                file.seekg(-2, ios::cur);    //go back two spaces
            }
        }
        ch = ' ';
        file.seekg(2, ios::cur);
    }

    end:;
}

void PrintLastLines(fstream &file)
{
    char ch;
    file.get(ch);
    while( file.good() )    //print last n lines
    {
        cout << ch;
        file.get(ch);
    }

    file.clear();
}
