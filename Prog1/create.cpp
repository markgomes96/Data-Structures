/*
 *Mark Gomes
 *CSC 310 - 1/15/19
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//typedef char String[25];

struct BookRec
{
    unsigned int isbn;
    string name;
    string author;
    int onhand;
    float price;
    string type;
};


istream & operator >> (istream& is, BookRec& br)
{
    string isbn, onhand, price;
    if(getline(is, isbn, '|'))
    {
        br.isbn = stoul(isbn, nullptr, 0);  //check for dashes
        getline(is, br.name, '|');
        getline(is, br.author, '|');
        getline(is, onhand, '|');
        br.onhand = stoi(onhand);
        getline(is, price, '|');
        br.price = stof(price);
        getline(is, br.type, '\n');

        //cout << isbn << " " << onhand << " " <<  price << endl;
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

        outfile.write((char *) &buffer, sizeof(BookRec) );
    }

/*
    outfile.seekp ( 1 * sizeof(buffer) );
    outfile.write ( (char *) &buffer, sizeof(buffer) );
    outfile.close();

    fstream binfile ("mark.out", ios::in | ios::binary);
    while ( binfile.read ((char *) &buffer, sizeof(buffer)) )
        cout << buffer.isbn << "\t" << buffer.name << "\t" << buffer.author
             << buffer.onhand << "\t" << buffer.price << "\t" << buffer.type << endl;

    infile.close();
    //outfile.close();
    binfile.close();
*/    
    return 0;
}

