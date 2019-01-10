#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
struct WeatherRec
{
        float high, low;
        int day;
        char month[20];
};

int main()
{
        fstream infile ("weather.dat", ios::in);
        fstream outfile ("weather.out", ios::out | ios::binary);

        WeatherRec buffer; 

        while (infile >> buffer.high)
        {
                infile >> buffer.low >> buffer.day;
                infile.getline ( buffer.month, 20, '\n' );

                outfile.write((char *) &buffer, sizeof(WeatherRec) );
        }

        outfile.seekp ( 1 * sizeof(buffer) );
        outfile.write ( (char *) &buffer, sizeof(buffer) );
        outfile.close();

        fstream binfile ("weather.out", ios::in | ios::binary);
        while ( binfile.read ((char *) &buffer, sizeof(buffer)) )
                cout << buffer.high << " " << buffer.low << " "
                     << buffer.day << " " << buffer.month << endl;
          return 0;
}
