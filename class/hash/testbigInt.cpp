#include <iostream>
#include "bigint.h"
using namespace std;

// program to test BigInt I/O (and string conversion)

int main()
{
    BigInt a;  BigInt sum = 0;   BigInt prod = 1;
    
    while (true)
    {
        cout << "enter a big integer : ";
        cin >> a;
        cout << "bigint = " << a << endl;
	sum += a;
	prod *= a;
	cout << "current sum = " << sum << endl;
	cout << "current product = " << prod << endl << endl;
    }
    return 0;
}
