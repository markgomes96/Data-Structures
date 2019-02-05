/*
*Developer : Mark Gomes
*02/04/19
*CSC 310
*Converts written date format to a numerical format
*/

#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int dateConverter(string date);
void fillMonths(map<string, int> &months);

int main(int argc, char *argv[])
{
    string date;
    if(argc > 1)
    {
        date = argv[1];
    }
    else
    {
        cout << "Please enter a date string" << endl;
        exit(0);
    }
    
    int numdate = 0;
    numdate = dateConverter(date);      //convert date to numerical format
    
    cout << endl << argv[1] << endl << endl << numdate << endl << endl;
}

int dateConverter(string date)
{
    map<string, int> months;
    fillMonths(months);              //fill map with month values

    date.erase(std::remove(date.begin(), date.end(), ','), date.end());    //remove comma
    stringstream ss;
    stringstream ss2;
    string word;
    int numdate = 0;
    ss << date;
    
    while(ss >> word)
    {
        if(months.find(word) != months.end())    //string is month
        {
            numdate += months[word];
        }
        else if(word.length() == 4)              //string is year
        {
            numdate += stoi(word);
        }
        else                                     //string is day     
        {
            ss2 << word << "0000";
            numdate += stoi(ss2.str());
            ss2.str("");
        }
    }
     
    return numdate; 
}

void fillMonths(map<string, int> &months)
{
    months["January"] = 1000000;   months["February"] = 2000000;   months["March"]     = 3000000;
    months["April"]   = 4000000;   months["May"]      = 5000000;   months["June"]      = 6000000;
    months["July"]    = 7000000;   months["August"]   = 8000000;   months["September"] = 9000000;
    months["October"] = 10000000;  months["November"] = 11000000;  months["December"]  = 12000000;
}