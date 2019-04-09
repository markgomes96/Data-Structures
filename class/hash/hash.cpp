// hash.cpp

#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include "bigint.h"
using namespace std;

typedef char String[20];
const int NumCities = 435;

struct Bucket
{
	int currSize;
	String key[3];
};

int hash (string key, int maxAddresses);
void numCollisions(int array[]);
void buildHashFile(Bucket mybucks[]);
void flushBuckets(Bucket mybucks[]);
void buildHashArray(fstream& infile, int array[], Bucket mybucks[]);
void printBuckets(Bucket mybucks[]);
int midSqHash (string key, int maxAddresses);   //Uses Big Int class & perfect hash, then extracts middle three digits

int main()
{
	
	fstream infile("cities.dat", ios::in);
	int array[300] = {0};
        Bucket mybucks[300];

	flushBuckets(mybucks);
	buildHashArray(infile, array, mybucks);
	numCollisions(array);
	printBuckets(mybucks);
	buildHashFile(mybucks);
        return 0;
}

void flushBuckets(Bucket mybucks[])
{
	for (int i = 0;  i < 300;  i++)
	{
		mybucks[i].currSize = 0;
		for (int j = 0;  j < 3;  j++)
			strcpy (mybucks[i].key[j], "///");
	}
}

void printBuckets(Bucket mybucks[])
{
	for (int i = 0;  i < 300;  i++)
	{
		cout << "i = " << i;
		cout << " size = " << mybucks[i].currSize << " "; 
		for (int j = 0;  j < 3;  j++)
			cout << mybucks[i].key[j] << " ";
		cout << endl;
	}
}

void buildHashArray(fstream& infile, int array[], Bucket mybucks[])
{
	string s;  int i, slot;

	getline (infile, s);
        while (infile)
        {
                //slot = hash(s, 300);
                slot = midSqHash(s, 300);
                array[slot] += 1;
                mybucks[slot].currSize += 1;
		i = 0;
                while(strcmp(mybucks[slot].key[i],"///") != 0)
                {
			i++;
			if (i == 3)
			{
			i = 0;
			slot++;
			if (slot > 299)
				slot = 0;
			}
		}
                strcpy(mybucks[slot].key[i], s.c_str());
                getline (infile, s);
        }
}

void buildHashFile(Bucket mybucks[])
{
	fstream outfile("hash.ind", ios::out | ios::binary);
	for (int i = 0;  i < 300;  i++)
		outfile.write((char *) &mybucks[i], sizeof(Bucket));
}

void numCollisions(int array[])
{
	int synonymns = 0;
	for (int j = 0;  j < 300;  j++)
	{
		if (array[j] > 1)
			synonymns += array[j] - 1;
		//cout << "j = " << j << " collisions = " << array[j] << endl;
	}
	cout << "Total Synonyms = " << synonymns << endl;

	cout.setf(ios::fixed, ios::floatfield);  cout.setf(ios::showpoint);
	for (int i=0;  i <= 8;  i++)
	{
		int count = 0;
		cout << "d(" << i << ") = ";
		for (int j = 0;  j < 300;  j++)
			if (array[j] == i)
				count++;
		cout << setprecision(2) << count << " " << float(count) / 300.0 << endl;
	}
}

int hash (string key, int maxAddresses)
{
  string temp = key;
  //convert to UPPER
  for (int i=0;temp[i]!=0;i++)
  	if(temp[i]<=122 && temp[i]>=97)
    		temp[i]-=32;

  if (temp.size() % 2 == 1) temp.append("Z");
  int sum = 0;
  for (int i = 0; i < temp.size()/2; i++) {
	sum += (int) temp[2*i]*100 + (int) temp[2*i+1];
  }
  return sum % 36373 % maxAddresses;

}

int midSqHash (string key, int maxAddresses)   //Uses Big Int class & perfect hash, then extracts middle three digits
{
        // "junk" = 'j' * 128^3 + 'u' * 128^2 + 'n' * 128^1 + 'k' * 128^0

        BigInt result(0);  
        int exp = 0;  // first power of 128 for char in key.length() - 1

        // Insert a for loop which starts at end of string and multiplies the ascii of each char times 128^exp
        // Add this value to result within loop
        exp = key.length()-1;
        for(int i = 0; i < key.length(); i++)
        {
            result += key[i] * pow(128, exp);
            exp--;
        }

        // Convert your result sum to a string using .ToString();
        string resultstr = result.ToString();

        // Calculuate k as the length of s divided by 3 
        int k = resultstr.length() / 3; 

        // Pull off the substring from k of length 3
        string chop = resultstr.substr(k, 3);

        // Calculate your mid-square by converting chop to an int and squaring
        int sqrnum = pow( stoi(chop), 2);

        // Return your num modulo maxAddresses
        return sqrnum % maxAddresses;
}
