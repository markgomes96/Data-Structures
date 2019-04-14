#ifndef CREATEBT_CPP
#define CREATEBT_CPP

#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "album.h"
#include "btree.h"

using namespace std;

/*
class Album;
const int ORDER = 5;
typedef Album keyType;
typedef int IndexArray[ORDER];
typedef keyType ValueArray[ORDER-1];

struct BTNode
{
    int currSize;
    ValueArray contents;
    IndexArray child;
};
*/

class Album;
typedef Album keyType;
BTree bt;

int main(int argc, char *argv[])
{
    // check arguments
    if(argc < 3)
    {
        cout << "Error : Please pass sequential and btree file" << endl;
        exit(0);
    }

    // open files and check access
    string sfname = argv[1];
    string bfname = argv[2];
    fstream seqfile(sfname.c_str());
    if(!seqfile)
    {
        cout << "sequential file failed to open" << endl;
        exit(0);
    }

    fstream btfile(bfname.c_str(), ios::out | ios::binary);
    if(!btfile)
    {
        cout << "btree file failed to open" << endl;
        exit(0);
    }
 
    // read in data from sequential file
    //BTNode buffer;
    string upc, artist, title;
    while(!seqfile.eof())
    {
        getline(seqfile, upc, '\n');
        if(seqfile.eof())
            break;
        getline(seqfile, artist, '\n');
        getline(seqfile, title, '\n');

        //cout << upc << " : " << artist << " : " << title << endl;

        // call btree object to insert key
        bt.insert(keyType(upc, artist, title));
    }
}

#endif
