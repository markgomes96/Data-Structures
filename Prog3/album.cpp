#ifndef ALBUM_CPP
#define ALBUM_CPP

#include <cstring>
#include <string>
#include <fstream>

#include "album.h"

using namespace std;

// private vars - String UPC, Artist, Title

Album::Album ()
{ }

Album::Album (const Album& otherAlbum)
{
    strcpy( UPC,    otherAlbum.UPC);
    strcpy( Artist, otherAlbum.Artist);
    strcpy( Title,  otherAlbum.Title);
}

Album::Album (String upc, String artist, String title)
{
    strcpy( UPC,    upc);
    strcpy( Artist, artist);
    strcpy( Title,  title);
}

Album & Album::operator = (const Album& otherAlbum)
{
    strcpy( UPC,    otherAlbum.UPC);
    strcpy( Artist, otherAlbum.Artist);
    strcpy( Title,  otherAlbum.Title);
}

bool operator < (const Album& a, const Album& b)
{
    int cmp = strcmp(a.UPC, b.UPC);
    if(cmp < 0)
        return true;
    else
        return false;
}

istream & operator >> (istream & stream, Album & C)
{
    stream >> C.UPC >> C.Artist >> C.Title;
    return stream;
}

ostream & operator << (ostream & stream, Album & C)
{
    stream << "UPC : " << C.UPC << "\nArtist : " << C.Artist <<
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
