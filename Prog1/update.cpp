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

struct TransactionRec
{
    TransactionType ToDo;
    BookRec B;
};

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
void loadTranToBook(TransactionRec &tr, BookRec &br)
{
    br.isbn = tr.B.isbn;
    strcpy(br.name, tr.B.name);
    strcpy(br.author, tr.B.author);
    br.onhand = tr.B.onhand;
    br.price = tr.B.price;
    strcpy(br.type, tr.B.type);
}

void addRecord(fstream& infile, TransactionRec& tr, BookRec& br, fstream& errorfile, int tranNum)
{
    if(searchFile(infile, tr.B.isbn) < 0)    //add record to end of file
    {
        infile.clear();
        infile.seekp ( 0, ios::end );    //move pointer to end of file
        loadTranToBook(tr, br);
        infile.write((char *) &br, sizeof(BookRec) );
    }
    else      //error - record alread exists
    {
        stringstream ss;
        ss << "Error in transaction number  " << tranNum << ": cannot add---duplicate key " << br.isbn << endl;
        errorfile << ss.str();
        ss.str("");
    }
}

void deleteRecord(fstream& infile, TransactionRec& tr, BookRec& br, fstream& errorfile, int tranNum)
{
    if(searchFile(infile, tr.B.isbn) > 0)       //delete record
    {   
        infile.read ((char *) &br, sizeof(BookRec));      //read in record to be deleted
        br.isbn = -1;                                    //mark record for deletion
        infile.seekp ( -sizeof(br), ios::cur );
        infile.write((char *) &br, sizeof(BookRec) );
    }
    else        //error - record doesn't exist
    {
        stringstream ss;
        ss << "Error in transaction number  " << tranNum << ": cannot delete---no such key " << br.isbn << endl;
        errorfile << ss.str();
        ss.str("");
    }
}

void changeOnHandAmount(fstream& infile, TransactionRec& tr, BookRec& br, fstream& errorfile, int tranNum)
{
    if(searchFile(infile, tr.B.isbn) > 0)       //delete record
    {
        infile.read((char *) &br, sizeof(BookRec));      //read in record to be changed
        infile.seekp ( -sizeof(br), ios::cur );
        br.onhand += tr.B.onhand;
        if(br.onhand >= 0)
        {
            infile.write((char *) &br, sizeof(BookRec) );      //rewrite record with record in transaction file
        }
        else
        {
            stringstream ss;
            ss << "Error in transaction number  " << tranNum << ": count = " << br.onhand << " for key " << br.isbn << endl;
            errorfile << ss.str();
            ss.str("");
        }
    }
    else        //error - isbn doesn't exist
    {
        stringstream ss;
        ss << "Error in transaction number  " << tranNum << ": cannot change count---no such key " << br.isbn << endl;
        errorfile << ss.str();
        ss.str("");
    }

}

void changePriceAmount(fstream& infile, TransactionRec& tr, BookRec& br, fstream& errorfile, int tranNum)
{
    if(searchFile(infile, tr.B.isbn) > 0)       //delete record
    {
        infile.read((char *) &br, sizeof(BookRec));      //read in record to be changed
        infile.seekp ( -sizeof(br), ios::cur );
        br.price = tr.B.price;
        infile.write((char *) &br, sizeof(BookRec) );      //rewrite record with record in transaction file
    }
    else        //error - isbn doesn't exist
    {
        stringstream ss;
        ss << "Error in transaction number  " << tranNum << ": cannot change price---no such key " << br.isbn << endl;
        errorfile << ss.str();
        ss.str("");
    }
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
    
    fstream infile;
    fstream tranfile (transact, ios::in | ios::binary);
    fstream errorfile ("ERRORS", ios::out);
    
    BookRec buffer;
    TransactionRec tranBuffer;
    int count = 0;
    
    //iterate and process all transactions in transaction file
    while( tranfile.read ((char *) &tranBuffer, sizeof(tranBuffer)) )
    {
        infile.open("copy.out", ios::in | ios::out | ios::binary);
    
        count++;
        if( tranBuffer.ToDo == Add)
        {
            addRecord(infile, tranBuffer, buffer, errorfile, count);
        }
        if( tranBuffer.ToDo == Delete)
        {
            deleteRecord(infile, tranBuffer, buffer, errorfile, count);
        }
        if( tranBuffer.ToDo == ChangeOnhand)
        {
            changeOnHandAmount(infile, tranBuffer, buffer, errorfile, count);
        }
        if( tranBuffer.ToDo == ChangePrice)
        {
            changePriceAmount(infile, tranBuffer, buffer, errorfile, count);
        }
        
        infile.close();
    }
    
    fstream cpfile ("copy.out", ios::in | ios::binary);
    
    fstream nmfile (newmaster, ios::out | ios::binary);          //write copy of master to new master
    while ( cpfile.read ((char *) &buffer, sizeof(buffer)) )
    {
        if(buffer.isbn > 0)        //check for deleted records
            nmfile.write((char *) &buffer, sizeof(BookRec) );
    }
    
    nmfile.close();
    errorfile.close();
    
    system("rm copy.out");                  //remove copy of master file
    
    fstream binfile ("update.out", ios::in | ios::binary);        //print out master file
    while ( binfile.read ((char *) &buffer, sizeof(buffer)) )
    {
        cout << setfill ('0') << setw(10) << buffer.isbn << setfill(' ');
        cout << setw(22) << buffer.name << setw(24) << buffer.author << setw(3) << buffer.onhand 
             << setw(7) << fixed << showpoint << setprecision(2) << buffer.price 
             << setw(9) << buffer.type << endl;
    }
    
    cpfile.close();
    binfile.close();
    
    return 0;
}
