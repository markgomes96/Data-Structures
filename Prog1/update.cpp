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

struct TransationRec
{
    TransactionType ToDo;
    BookRec B;
};

void addRecord(fstream& infile, fstream& outfile, TransationRec& tr, BookRec& br, fstream& errorfile, int tranNum)
{
    if(searchFile(infile, tr.B.isbn) < 0)    //add record to end of file
    {
        outfile.seekp ( 0, ios::end );        //move ptr to end of file
        loadTranToBook(tr, br);
        outfile.write((char *) &br, sizeof(BookRec) );
    }
    else      //error - record alread exists
    {
        stringstream ss;
        ss << "Error in transaction number " << tranNum << ": cannot add-duplicate key " << buffer.isbn;
        errorfile.write(ss.str().c_str());
        ss.str("");
    }
}

void deleteRecord(fstream& infile, fstream& outfile, TransationRec& tr, BookRec& br, fstream& errorfile, int tranNum)
{
    if(searchFile(infile, tr.B.isbn) > 0)       //delete record
    {   
        outfile.seekp ( infile.tellg(), ios::beg );       //move ptr in outfile to same as infile
        infile.read ((char *) &br, sizeof(BookRec));      //read in record to be deleted
        br.isbn = -1;                                    //mark record for deletion
        outfile.write(char *) &br, sizeof(BookRec) );
    }
    else        //error - record doesn't exist
    {
        stringstream ss;
        ss << "Error in transaction number " << tranNum << ": cannot delete-no such key " << buffer.isbn;
        errorfile.write(ss.str().c_str());
        ss.str("");
    }
}

int searchFile(fstream& infile, long int isbn)
{
    BookRec buffer;
    bool found = false;
    while(infile.read ((char *) &buffer, sizeof(buffer)) )
    {
        if(buffer.isbn == isbn)
        {
            found = true;
            infile.seekp ( -sizeof(buffer), ios::cur );
            break;            //returns file pointing at found isbn location
        }
    }
    
    if(found)        //indicated if isbn number was found
        return 1;
    else
        return -1;
}

//copies TransationRec data struct to BookRec data struct
void loadTranToBook(TransationRec &tr, BookRec &br)
{
    br.isbn = tr.B.isbn;
    br.name = tr.B.name;
    br.author = tr.B.author;
    br.onhand = tr.B.onhand;
    br.price = tr.B.price;
    br.type = tr.B.type;
}

int main(int argc, char *argv[])
{
    String master, transact, newmaster;
    
    if(argc < 4)          //read in file names from command line
    {
        cout << "Not enough arguments... Goodbye" << endl;
        return 0;
    }
    else
    {
        strcpy(master, argv[1]);
        strcpy(transact, argv[2]);
        strcpy(newmaster, argv[3]);
    }
    
    stringstream ss;
    ss << "cp " << master << " copy.out";
    system(ss.str().c_str());      //make copy of master file
    ss.str("");
    
    fstream infile ("copy.out", ios::in | ios::binary);
    fstream outfile ("copy.out", ios::out | ios::binary);
    fstream tranfile (transact, ios::in | ios::binary);
    fstream errorfile ("ERRORS", ios::out);
    
    //***********************************************
    BookRec buffer;
    TransationRec tranBuffer;
    int count = 0;
    
    //iterate and process all transactions in transaction file
    while( tranfile.read ((char *) &tranBuffer, sizeof(tranBuffer)) )
    {
        count++;
        if( tranBuffer.ToDo == ADD)
        {
            addRecord(infile, outfile, tranBuffer, buffer, errorfile, count);
        }
        if( tranBuffer.ToDo == Delete)
        {
            deleteRecord(infile, outfile, tranBuffer, buffer, errorfile, count);
        }
        if( tranBuffer.ToDo == ChangeOnhand)
        {
        
        }
        if( tranBuffer.ToDo == ChangePrice)
        {
        
        }
        
        infile.seekp ( 0, ios::beg );          //return pointers to beg
        outfile.seekp ( 0, ios::beg );
    }
    
    //**********************************************
    
    fstream nmfile (newmaster, ios::out | ios::binary);          //write copy of master to new master
    while ( infile.read ((char *) &buffer, sizeof(buffer)) )
    {
        if(buffer.isbn > 0)        //check for deleted records
            nmfile.write((char *) &buffer, sizeof(BookRec) );
    }
    infile.close();
    outfile.close();        //close open files
    nmfile.close();
    errorfile.close();
    
    system("rm copy.out");                  //remove copy of master file
    
    return 0;
}