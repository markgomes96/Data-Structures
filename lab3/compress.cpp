// Mark Gomes
// CSC 310
// 02/19/19
// Lab 3 - compress/uncompress

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;

string compress(string str)
{
    int count = 1;
    stringstream ss(str);
    stringstream out;
    string word;
    string temp;

    ss >> word;
    temp = word;

    while(ss >> word)       //go through all words
    {
        if(strcmp(word.c_str(), temp.c_str()) != 0)
        {
            if(count <= 3)      //if count is less than 3 just print series
            {
                for(int i = 0; i < count; i++)
                {
                    out << temp << " ";
                }
            }
            else                //greater than 3 then compress series
            {
                out << "ff " << temp << " " << setfill('0') << setw(2) << count << " ";
            }
    
            count = 0;
        }

        temp = word;

        count++;
    }

    if(count <= 3)          //count check for final series
    {
        for(int i = 0; i < count; i++)
        {
            out << temp << " ";
        }
    }
    else
    {
        out << "ff " << temp << " " << setfill('0') << setw(2) << count << " ";
    }

    return out.str();
}

string uncompress(string str)
{
    stringstream ss(str);
    stringstream out;
    string word;
    string countstr;
    int count;

    while(ss >> word)
    {
        if(strcmp(word.c_str(), "ff") == 0)     //compression found
        {
            ss >> word;         //get number to be repeated
            ss >> countstr;
            count = stoi(countstr);     //get count of number

            for(int i = 0; i < count; i++)
            {
                out << word << " ";
            }
        }
        else
        {
            out << word << " ";         //no compression
        }
    }

    return out.str();
}

int main(int argc, char* argv[])
{
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";

    string comInput = compress(myInput);

    cout << endl << comInput << endl;

    cout << endl << uncompress(comInput) << endl << endl;

    return 0;
}
