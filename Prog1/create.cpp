/*
 *Mark Gomes
 *CSC 310 - 1/15/19
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

typedef char String[25];

struct BookRec
{
    long int isbn;
    String name;
    String author;
    int onhand;
    float price;
    String type;
};


istream & operator >> (istream& is, BookRec& br)
{
    string isbn,name,author,onhand,price,type;
    if(getline(is, isbn, '|'))
    {
        br.isbn = stol(isbn, nullptr);  //check for dashes

        getline(is, name, '|');
        strcpy(br.name, name.c_str());

        getline(is, author, '|');
        strcpy(br.author, author.c_str());

        getline(is, onhand, '|');
        br.onhand = stoi(onhand);

        getline(is, price, '|');
        br.price = stof(price);

        getline(is, type, '\n');
        strcpy(br.type, type.c_str());
    }

    return is;
}

int main(int argc, char *argv[])
{
    fstream infile ("library.dat", ios::in);
    fstream outfile ("mark.out", ios::out | ios::binary);

    BookRec buffer;

    while (infile >> buffer)
    {   
        //check buffer for exceptions and print out errors before writing to file

        outfile.write((char *) &buffer, sizeof(BookRec) );
    }
    infile.close();
    outfile.close();

    fstream binfile ("mark.out", ios::in | ios::binary);
    while ( binfile.read ((char *) &buffer, sizeof(buffer)) )
    {
        cout << setw(12) << buffer.isbn << setw(22) << buffer.name 
             << setw(24) << buffer.author << setw(3) << buffer.onhand 
             << setw(7) << fixed << showpoint << setprecision(2) << buffer.price 
             << setw(9) << buffer.type << endl;
    }

    binfile.close();
   
    return 0;
}

