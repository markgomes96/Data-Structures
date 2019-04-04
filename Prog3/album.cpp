#ifndef ALBUM_CPP
#define ALBUM_CPP

#include <cstring>
#include <string>
#include <fstream>
using namespace std;

const int UpTo = 50;
typedef char String[UpTo];

// private vars - String UPC, Artist, Title

Album::Album ()
{ }

Album::Album (const Album& otherAlbum)
{
    UPC = otherAlbum.getUPC();
    Artist = otherAlbum.getArtist();
    Title = otherAlbum.getTitle();
}

Album::Album (String upc, String artist, String title)
{
    UPC = upc;
    Artist = artist;
    Title = title;
}

Album & operator = (const Album& otherAlbum)
{
    UPC = otherAlbum.getUPC();
    Artist = otherAlbum.getArtist();
    Title = otherAlbum.getTitle();
}

friend bool operator < (const Album& a, const Album& b)
{
    return a.UPC < b.UPC;
}

friend istream & operator >> (istream & stream, Album & C)
{
    stream >> C.UPC >> C.Artist >> C.Title;
    return is;
}

friend ostream & operator << (ostream & stream, Album & C)
{
    stream << "UPC : " << C.UPC << "\nArtist : " << c.Artist <<
            "\nTitle : " << C.Title;
    return stream;
}

string Album::getUPC ()
{
    return UPC;
}

string Album::getArtist ()
{
    return Artist;
}

string Album::getTitle ()
{
    return Title;
}

int Album::recordSize()
{
    return UpTo * 3;
}

#endif
