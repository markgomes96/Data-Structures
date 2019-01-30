/*
 *Mark Gomes
 *CSC 310 - 1/15/19
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

typedef char String[25];
enum TransactionType {Add, Delete, ChangeOnhand, ChangePrice};

struct BookRec
{
    long int isbn;
    String name;
    String author;
    int onhand;
    float price;
    String type;
};

struct TransactionRec
{
    TransactionType ToDo;
    BookRec B;
};

//Tranaction Types
//0 - Add 1 records
//1 - Delete 1 records
//3 - Change 1 [on hand] amount record
//4 - Change 1 [price] amount record

//ERROR TYPES
//5 - Adding record, found duplicate isbn
//6 - Deleting record, non-existent isbn
//7 - Change onhand, create negative count
//8 - Change onhand, non-existent isbn
//9 - Change price, non-existent isnb

void addToTransFile(fstream& tranfile, BookRec& br, TransactionType type)
{
    TransactionRec tr;
    
    tr.ToDo = type;
    tr.B = br;

    tranfile.write((char *) &tr, sizeof(TransactionRec) );
}

int main(int argc, char *argv[])
{
    fstream tranfile ("test.out", ios::out | ios::binary | ios::trunc);
    fstream infile ("library.out", ios::in | ios::binary);
    BookRec br1;
    BookRec br2;
    BookRec br3;
    BookRec br4;
    BookRec br5;
    BookRec br6;
    BookRec br7;
    BookRec br8;
    BookRec br9;
    BookRec br10;
    
    infile.read ((char *) &br1, sizeof(br1));      //read in file to add
    infile.read ((char *) &br2, sizeof(br2));      //read in file to delete
    infile.read ((char *) &br3, sizeof(br3));      //read in file to change onhand; error 5
    infile.read ((char *) &br4, sizeof(br4));      //read in file to change price
    
    infile.read ((char *) &br5, sizeof(br5));      //error 6; error 8; error 10
    infile.read ((char *) &br6, sizeof(br6));      //error 7

    br1.isbn = 7777777777;
    br3.onhand = 2;
    br4.price = 3.33;
    br5.isbn = 8888888888;
    br6.onhand = -90;

    for(int i = 1; i < argc; i++)
    {
        switch(stoi(argv[i]))
        {
            case 0 :
                addToTransFile(tranfile, br1, Add);
                break;
                
            case 1 :
                addToTransFile(tranfile, br2, Delete);
                break;
                
            case 2 :
                addToTransFile(tranfile, br3, ChangeOnhand);
                break;
                
            case 3 :
                addToTransFile(tranfile, br4, ChangePrice);
                break;
                
            case 4 :
                addToTransFile(tranfile, br3, Add);
                break;
                
            case 5 :
                addToTransFile(tranfile, br5, Delete);
                break;
                
            case 6 :
                addToTransFile(tranfile, br6, ChangeOnhand);
                break;
                
            case 7 :
                addToTransFile(tranfile, br5, ChangeOnhand);
                break;
                
            case 8 :
                addToTransFile(tranfile, br5, ChangePrice);
                break;
                         
            default :
                break;             
            }
    }
    
    tranfile.close();
    infile.close();

    return 0;
}
