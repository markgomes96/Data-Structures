/*
*Developer : Mark Gomes
*1/15/19
*CSC 310
*counts lines, words, bytes of a file
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>

using namespace std;

void HandleFlags(bool &bf, bool &lf, bool &wf, int argc, char* argv[]);
void CountFile(fstream &file, int &linecount, int &wordcount, int &bytecount);
void HandleOutput(bool bf, bool lf, bool wf, int linecount, int wordcount, int bytecount, string filename);

int main(int argc, char *argv[])
{
    //variables to store counts
    int linecount = 0, wordcount = 0, bytecount = 0;
    
    //bools to store flag settings
    bool bf = false, lf = false, wf = false;

    HandleFlags(bf, lf, wf, argc, argv);    //set flag settings

    string filename = argv[argc-1];          //read in file name
    fstream file (filename.c_str(), ios::in | ios::app);
    
    CountFile(file, linecount, wordcount, bytecount);    //go through file and count
       
    HandleOutput(bf, lf, wf, linecount, wordcount, bytecount, filename);    //print counts to screen
}

void HandleFlags(bool &bf, bool &lf, bool &wf, int argc, char* argv[])
{
    for(int i = 1; i < argc-1; i++)     //handles flags
    {
        if( strcmp( argv[i], "-c" ) == 0 )
            bf = true;
        else if( strcmp( argv[i] , "-l" ) == 0 )
            lf = true;
        else if( strcmp( argv[i] , "-w" ) == 0 )
            wf = true;
    }

    if(!bf && !lf && !wf)       //if no flags then display all counts
        bf = true, lf = true, wf = true;
}

void CountFile(fstream &file, int &linecount, int &wordcount, int &bytecount)
{
    char ch;
    char lastch = ' ';
    file.get(ch);
    while( file.good() )      //iterate through all lines
    {        
        if( ch == '\n' )        //check for next lines
        {
            linecount++;
            if(lastch != ' ')
            {
                wordcount++;
            }
        }
        else if ( ch == ' ' )       //check for spaces
        {
            if(lastch != ' ')
            {
                wordcount++;
            }
        }
        
        bytecount++;        //increment btye count for each char
        lastch = ch;        //store last ch
        file.get(ch);       //get next character in file
    }
}

void HandleOutput(bool bf, bool lf, bool wf, int linecount, int wordcount, int bytecount, string filename)
{
    string output;            //handle output based on counts and bools
    output = lf ? to_string(linecount) + "\t" : "";
    output += wf ? to_string(wordcount) + "\t" : "";
    output += bf ? to_string(bytecount) + "\t" : "";

    //print out output with filename
    cout << "\t" << output << filename << endl;
}
