#ifndef FILE_H
#define FILE_H

using namespace std;
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>

class File
{
   public :
        
        // Constructors
        File (const File& otherFile);
        File (const char name[], const char pmode[],
             const char size[], const char stamp[]);
        File ();

        // Operators
        File & operator = (const File& otherFile);

        // Functions
        string getSize() const;
        string getName() const;
        string getPmode() const;
        string getStamp() const;
        int recordSize() const;
        void flagAsDir();
        bool isADir() const;

   private :

        // Variables
        char name[81], pmode[5], size[7], stamp[16];
        bool ADir;
};

#endif