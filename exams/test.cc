#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

enum Animals {RODENT, CAT, DOG, BIRD, REPTILE, HORSE, BOVINE, SHEEP};

int hexToDec(string countstr)
{
    return 3;
}

int totalCompressed(string compressed)
{
    stringstream ss(compressed);
    string word;
    string countstr;
    int charCount = 0;

    while(ss >> word)
    {
        if(strcmp(word.c_str(), "ff") == 0)
        {
            ss >> word;
            ss >> countstr;
            
            charCount += hexToDec(countstr);
        }
        else
        {
            charCount++;
        }
    }

    return charCount;
}

int main(int argc, char *argv[])
{
    /*
    Animals myAnimals;
    
    fstream zipFile("animal.zip", ios::out | ios::binary);

    char zippedAnimals;

    zippedAnimals = (char) SHEEP;

    zipFile.write((char *) &zippedAnimals, sizeof(char));
    */
    
    cout << totalCompressed("ff 93 04 92 91 91 ff 94 1a") << endl;
    
    return 0;
}
