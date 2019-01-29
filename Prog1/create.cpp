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

//overload >> to handle reading in BookRec
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
    fstream outfile ("library.out", ios::out | ios::binary);

    BookRec buffer;
    long int previsbn = 0;
    int count = 0;
    bool errorFlag = false;

    while (infile >> buffer)
    {   
        count++;
        errorFlag = false;

        //check buffer for exceptions and print out errors before writing to file
        if(buffer.isbn < 1)
        {
            cerr << "Illegal [isbn] number encountered on line " << count << " of data file - record ignored." << endl;
            errorFlag = true;
        }
        if(buffer.isbn <= previsbn)
        {
            cerr << "[isbn] number out of sequence on line " << count << " of data file" << endl;
            errorFlag = true;
        }
        if(buffer.onhand < 0)
        {
            cerr << "Negative [onhand] value on line " << count << " of data file - record ignored." << endl;
            errorFlag = true;
        }
        if(buffer.price < 0)
        {
            cerr << "Negative [price] value on line " << count << " of data file - record ignored." << endl;
            errorFlag = true;
        }

        if(errorFlag)
        {
            cout << setfill('0') << setw(10) << buffer.isbn << setfill(' ');
            cout << setw(22) << buffer.name << setw(24) << buffer.author << setw(3) << buffer.onhand
                 << setw(7) << fixed << showpoint << setprecision(2) << buffer.price
                 << setw(9) << buffer.type << endl << endl;
        }
        else
        {
            previsbn = buffer.isbn;
            outfile.write((char *) &buffer, sizeof(BookRec) );
        }
    }
    infile.close();
    outfile.close();

    fstream binfile ("library.out", ios::in | ios::binary);
    while ( binfile.read ((char *) &buffer, sizeof(buffer)) )
    {
        cout << setfill ('0') << setw(10) << buffer.isbn << setfill(' ');
        cout << setw(22) << buffer.name << setw(24) << buffer.author << setw(3) << buffer.onhand 
             << setw(7) << fixed << showpoint << setprecision(2) << buffer.price 
             << setw(9) << buffer.type << endl;
    }

    binfile.close();
   
    return 0;
}

