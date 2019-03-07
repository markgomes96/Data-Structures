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
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "file.h"

using namespace std;

// Command Line Handling
void readInArguments(int argc, char *argv[], bool &cf, bool &tf, bool &xf, bool &help);

// Main Functionality
void createTarFile(int argc, char *argv[]);
    void createFileList(int argc, char *argv[], vector<File> &fl);
    void updateFileInfo(File &fo);
    void writeFLToBin(vector<File> &fl, string fileName);
void listOutTarFile(string fileName);
void reviveTarFile(string fileName);
void displayHelp();

// Utility Functions
bool isFile(string dn);
string executeCmd(const char* cmd);

int main(int argc, char *argv[])
{
    bool cf = false, tf = false, xf = false, help = false;
    
    readInArguments(argc, argv, cf, tf, xf, help);
    
    if(cf == true)
        createTarFile(argc, argv);
    if(tf == true)
        listOutTarFile(argv[2]);
    if(xf == true)
        reviveTarFile(argv[2]);
    if(help == true)
        displayHelp();
          
    return 0;
}

void createTarFile(int argc, char *argv[])
{
    vector<File> fl;
    createFileList(argc, argv, fl);
    for(int i = 0; i < fl.size(); i++)
    {
        updateFileInfo(fl[i]);
    }
    writeFLToBin(fl, argv[2]);
}

void createFileList(int argc, char *argv[], vector<File> &fl)
{
    int fileNum = 0;
    string dirNames;
    for(int i = 3; i < argc; i++)              //create list of all directory names
        dirNames += string(argv[i]) + " ";
    replace( dirNames.begin(), dirNames.end(), '/', ' ');
    string str_cmd = "ls -R " + dirNames;		//convert string command to char array
    char char_cmd[ str_cmd.length()+1 ];
    strcpy(char_cmd, str_cmd.c_str());
    string output = executeCmd(char_cmd);
    
    istringstream ss(output);
    string line, path;
    File tmp;
    size_t found;
    bool swaped = false;
    while(ss >> line)        // iterate through list of files
    {
        found = line.find(":");        // checks if file is directory
        if(found != string::npos)
        {
            replace( line.begin(), line.end(), ':', '/');
            tmp = File(line.c_str(), "\0", "\0", "\0");
            tmp.flagAsDir();
            path = line;          // record path for files in directory
            
            for(int i = 0; i < fl.size(); i++)      // check prev file objects (not prev dir) for repeats
            {
                found = tmp.getName().find(fl[i].getName());
                if(found != string::npos && !fl[i].isADir())          // changes repeats to directory
                {
                    fl[i] = tmp;
                    swaped = true;
                }
            }
        }
        else                          // normal file
        {
            line = path + line;
            tmp = File(line.c_str(), "\0", "\0", "\0");    // create file obj with file name
        }
        
        if(!swaped)          // add new files to the list
        {
            fl.push_back(tmp);
        }
        swaped = false;
    }
}

void updateFileInfo(File &fo)
{
    // get the protection mode
    string str_cmd = "stat -c \"0%a\" " + fo.getName();		//convert string command to char array
    char char_cmd[ str_cmd.length()+1 ];
    strcpy(char_cmd, str_cmd.c_str());
    string pmode = executeCmd(char_cmd);
    pmode = pmode.substr(0, 4);
    
    // get the file size
    str_cmd = "stat -c \"%s\" " + fo.getName();		//convert string command to char array
    char_cmd[ str_cmd.length()+1 ];
    strcpy(char_cmd, str_cmd.c_str());
    string size = executeCmd(char_cmd);
    size = size.substr(0, size.length()-1);
    
    // get the time stamp
    str_cmd = "stat -c \"%x\" " + fo.getName();		//convert string command to char array
    char_cmd[ str_cmd.length()+1 ];
    strcpy(char_cmd, str_cmd.c_str());
    string ts = executeCmd(char_cmd);
    string tstamp = ts.substr(0, 4) /*year*/ + ts.substr(5,2) /*month*/ + ts.substr(8,2) /*day*/ + 
                ts.substr(11,2) /*hour*/ + ts.substr(14,2) /*minute*/ + "." + ts.substr(17,2) /*second*/;
    
    // update File object with stats
    bool isDir = fo.isADir();
    File tmp = File(fo.getName().c_str(), pmode.c_str(), size.c_str(), tstamp.c_str());
    if(isDir)
        tmp.flagAsDir();
    fo = tmp;
}

void writeFLToBin(vector<File> &fl, string fileName)
{
    // open bin file to write to
    fstream jarfile (fileName.c_str(), ios::out | ios::binary);
    
    //write number of files at start
    int fileNum = fl.size();
    jarfile.write((char *) &fileNum, sizeof(int) );
    
    // write fileobjects to jar file
    for(int i = 0; i < fl.size(); i++)
    {
        jarfile.write((char *) &fl[i], sizeof(File) );
        
        //check if file -> write out file content
        if(!fl[i].isADir())
        {   
            ifstream file(fl[i].getName().c_str());
            char ch;
            while(file.get(ch))      // write file content char by char
            {
                jarfile.write((char *) &ch, sizeof(char) );
            }
        }
    }
}

void listOutTarFile(string fileName)
{
    fstream jarfile (fileName.c_str(), ios::in | ios::binary);
    File buffer;
    
    // move past number of files
    jarfile.seekg ( sizeof(int), ios::cur );
    
    // read in file objects
    int fileSize;
    while(jarfile.read ((char *) &buffer, sizeof(buffer)) )
    {
        cout << buffer.getName() << endl;
        
        if(!buffer.isADir())    // move past file object content
        {
            fileSize = stoi(buffer.getSize());
            jarfile.seekg ( fileSize*sizeof(char), ios::cur );
        }
    }
}

void reviveTarFile(string fileName)
{
    vector<File> fl;
    fstream jarfile (fileName.c_str(), ios::in | ios::binary);
    File buffer;
    
    // move past number of files
    jarfile.seekg ( sizeof(int), ios::cur );
    
    // read in file objects
    int fileSize;
    char ch;
    fstream file;
    string cmd;
    while(jarfile.read ((char *) &buffer, sizeof(buffer)) )
    {   
        if( !isFile(buffer.getName() ) )      // check if directory/file already exists
        {
            if(buffer.isADir())     // handle directory
            {
                // create directory
                cmd = "mkdir " + buffer.getName();
                system(cmd.c_str());
                
                // set protection mode
                cmd = "chmod " + buffer.getPmode() + " " + buffer.getName();
                system(cmd.c_str());
                
                // set time stamp
                cmd = "touch -a -t " + buffer.getStamp() + " " + buffer.getName();
                system(cmd.c_str());
            }
            else                    // handle file
            {
                // create directory
                cmd = "touch " + buffer.getName();
                system(cmd.c_str());
                
                // set protection mode
                cmd = "chmod " + buffer.getPmode() + " " + buffer.getName();
                system(cmd.c_str());
                
                // set time stamp
                cmd = "touch -a -t " + buffer.getStamp() + " " + buffer.getName();
                system(cmd.c_str());
            
                // open file to write in its contents
                file.open(buffer.getName());
                fileSize = stoi(buffer.getSize());
                for(int i = 0; i < fileSize; i++)
                {
                    jarfile.read ((char *) &ch, sizeof(char));
                    file << ch;
                }
                file.close();
            }
        }
        else
        {
            if(!buffer.isADir())    // move past file object content
            {
                fileSize = stoi(buffer.getSize());
                jarfile.seekg ( fileSize*sizeof(char), ios::cur );
            }
        }
    }
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
    bool dirFlag = false;

    if(argc >= 2)
    {
        if(strcmp(argv[1], "-cf") == 0)    // check for -cf flag
        {
            if(argc >= 4)
            {
                if(isFile(argv[3]) )
                {
                    for(int i = 3; i < argc; i++)
                    {
                        if(!isFile(argv[i]))
                            dirFlag = true;
                    }
                    if(!dirFlag)
                        cf = true;
                }
                else
                {
                    cout << "Error : File/Directoy Name Not Found" << endl;
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
                if( isFile(argv[2]) )
                {
                    tf = true;
                }
                else
                {
                    cout << "Error : File/Directoy Name Not Found" << endl;
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
                if( isFile(argv[2]) )
                {
                    xf = true;
                }
                else
                {
                    cout << "Error : File/Directoy Name Not Found" << endl;
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

bool isFile(string dn)
{
    ifstream fp(dn);
    if(!fp.is_open())
    {
        return false;
    }
    return true;
}

string executeCmd(const char* cmd)   // executes linux command and returns output
{
    array<char, 128> buffer;
    string output;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) { throw std::runtime_error("popen() failed!"); }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        output += buffer.data();
    return output;
}

#endif