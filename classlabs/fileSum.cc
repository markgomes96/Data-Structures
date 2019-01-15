/*
*Developer : Mark Gomes
*1/15/19
*CSC 310
*/

#include <istream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int SumNums(istream& NumS);

int main(int argc, char *argv[])
{
    string filename = argv[1];
    
    filebuf fb;
    fb.open(filename.c_str(), ios::in);
    istream infile(&fb);
    
    int sum;
    sum = SumNums(infile);
    
    cout << sum << endl;
    return 0;
}

int SumNums(istream& NumS)
{
    int sum = 0;
    int num;
    char ch;
    while ( NumS.good() )
    {
      	NumS >> num;
        
        if( NumS.fail() )
        {
            NumS.clear();
            NumS >> ch;
            if( !( ch == ',' ) )
            {
                sum = -1;
                break;
            }
        } 
        else
        {
      	    sum += num;
        }
    }
    
    NumS.clear();
    return sum;
}