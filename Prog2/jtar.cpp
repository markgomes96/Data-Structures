#ifndef JTAR_CPP
#define JTAR_CPP

// Mark Gomes
// CSC 310 - Dr. Digh
// 02/28/19
// Project 2 - tar command

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

// Command Line Handling
void readInArguments(int argc, char *argv[], bool &cf, bool &tf, bool &xf, bool &help);
bool isTarFile(string tfn);
bool isDirectory(string dn);

// Main Functionality
void createTarFile();
void listOutTarFile();
void reviveTarFile();
void displayHelp();

// Utility Functions

int main(int argc, char *argv[])
{
    bool cf = false, tf = false, xf = false, help = false;
    
    readInArguments(argc, argv, cf, tf, xf, help);
    
    if(cf == true)
        createTarFile();
    if(tf == true)
        listOutTarFile();
    if(xf == true)
        reviveTarFile();
    if(help == true)
        displayHelp();
}

void createTarFile()
{

}

void listOutTarFile()
{

}

void reviveTarFile()
{

}

void displayHelp()
{
    ifstream inFile;
    inFile.open("mhelp");
    string line;
    while(getline(inFile, line))
    {
        cout << line << endl;
    }
}

void readInArguments(int argc, char *argv[], bool &cf, bool &tf, bool &xf, bool &help)
{
    if(argc >= 2)
    {
        if(strcmp(argv[1], "-cf") == 0)    // check for -cf flag
        {
            if(argc >= 4)
            {
                if( isTarFile(argv[2]) && isDirectory(argv[3]) )
                {
                    cf = true;
                }
                else
                {
                    cout << "Error - Invalid argument types for -cf" << endl;
                }  
            }
            else
            {
                 cout << "Error - Not enough arguments for -cf" << endl;
            }
        }
        else if(strcmp(argv[1], "-tf") == 0)    // check for -tf flag
        {
            if(argc >= 3)
            {
                if( isTarFile(argv[2]) )
                {
                    tf = true;
                }
                else
                {
                    cout << "Error - Invalid argument types for -tf" << endl;
                }  
            }
            else
            {
                 cout << "Error - Not enough arguments for -tf" << endl;
            }
        }
        else if(strcmp(argv[1], "-xf") == 0)    // check for -xf flag
        {
            if(argc >= 3)
            {
                if( isTarFile(argv[2]) )
                {
                    xf = true;
                }
                else
                {
                    cout << "Error - Invalid argument types for -xf" << endl;
                }  
            }
            else
            {
                 cout << "Error - Not enough arguments for -xf" << endl;
            }
        }
        else if(strcmp(argv[1], "--help") == 0)    // check for -xf flag
        {
            help = true;
        }
        else
        {
            cout << "Error - No valid option found" << endl;
        }
    }
    else
    {
        cout << "Error - Not enough arguments" << endl;
    }
}

bool isTarFile(string tfn)
{
    return true;
}

bool isDirectory(string dn)
{
    return true;
}

#endif