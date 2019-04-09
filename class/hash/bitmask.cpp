
#include <iostream>
#include <cmath>
using namespace std;
unsigned int decToBinary (unsigned int num);

int main()
{
	unsigned int bitmask = 1 << 1;
	cout << "bitmask (1 << 1) = " << decToBinary(bitmask) << endl;
	cout << "bitmask & 3 = " << decToBinary(bitmask & 3) << endl;  
	cout << "bitmask & 4 = " << decToBinary(bitmask & 4) << endl;  
	cout << "bitmask | 3 = " << decToBinary(bitmask | 3) << endl;  
	cout << "bitmask | 4 = " << decToBinary(bitmask | 4) << endl;  
        return 0;
}

unsigned int decToBinary (unsigned int num)
{
   unsigned int temp = num, binary = 0, count = 0, remain;
   while (temp != 0) 
   {
  	remain = temp % 2; 
  	binary = binary + remain * int(pow(10, count)); 
  	temp = temp / 2; 
  	count = count + 1; 
   }
   return binary;
}
