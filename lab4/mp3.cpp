// Mark Gomes
// 03/21/19
// CSC 310 - Dr. Digh
// Lab 4
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string.h>
using namespace std;

class Song 
{
  public:
    string title;
    int time;
    int track;      // Primary key
    bool operator < (Song another) const { return title < another.title;}
};

ostream & operator << (ostream &out, Song &l) 
{
    cout << "\t\t" << l.track << ".  " << l.title << " " << l.time/100 << ":";
    if ((l.time % 100) < 10) 
        cout << "0";
    cout << l.time % 100;
}

class Album 
{
  public :
    map<int, Song> songs;
    string name;    // Album's name
    //string artist;
    string genre;
    int time;       // Total time of all songs on album
    int nsongs;     // Total number of songs on album
};

ostream & operator << (ostream &out, Album &l) 
{
    cout << "\t" << l.name << ": " << l.nsongs << ", " << l.time/100 << ":";
    if ((l.time % 100) < 10) 
        cout << "0";
    cout << l.time % 100;
}

class Artist 
{
  public :
    string name;    // Artist's name
    int time;       // Total time of all songs on all albums by this artist
    int nsongs;     // Total number of songs on all albums by this artist
    bool operator < (Artist another) const { return name < another.name;}
    vector<Album> albums;
};

ostream & operator << (ostream &out, Artist &l) 
{
    cout << l.name << ": " << l.nsongs << ", " << l.time/100 << ":";
    if ((l.time % 100) < 10) 
        cout << "0";
    cout << l.time % 100;
}

int isArtistRecorded(vector<Artist> a, string b);
int isAlbumRecorded(vector<Artist> a, int i, string b);
int timeToInt(string a);
//void sortArtists(&vector<Artist> a);
//void sortAlbums(&vector<Album> a);

int main(int argc, char** argv)
{
    if(argc < 2)    // check if mp3 argument exist
    {
        cout << "mp3: missing filename 'mp3'" << endl;
        exit(0);
    }
    
    ifstream infile(argv[1]);
    if(!infile)
    {
        cout << "mp3 file failed to open" << endl;
        exit(0);
    }

    vector<Artist> artists;

    string line, title, time, artist, album, genre, track;
    int artInd, albInd;
    stringstream ss;
    while(getline(infile, line))
    {
        ss.str(line);           // load line from file into string stream
        ss >> title >> time >> artist >> album >> genre >> track;
        
        //** handle artists **
        artInd = isArtistRecorded(artists, artist);

        if(artInd < 0)       // new artist found
        {
            Artist tmp_art;             // artist info
            tmp_art.name = artist;
            tmp_art.nsongs = 0;
            tmp_art.time = 0;
            artists.push_back(tmp_art);

            artInd = artists.size() - 1;    // update artist index
        }
        //**

        //** handle albums **
        albInd = isAlbumRecorded(artists, artInd, album);
        
        if(albInd < 0)          // new album found
        {
            Album tmp_alb;              // album info
            tmp_alb.name = album;
            tmp_alb.genre = genre;
            tmp_alb.nsongs = 0;
            tmp_alb.time = 0;

            albInd = artists[artInd].albums.size() - 1;  // update album index
        }
        //**

        //** handle songs **
        Song tmp_song;                  // song info
        tmp_song.title = title;
        tmp_song.time = timeToInt(time);
        tmp_song.track = stoi(track);
        
        artists[artInd].albums[albInd].songs[stoi(track)] = tmp_song;          // link song -> album
        //**

        //** update artists/albums **
        artists[artInd].albums[albInd].time += artists[artInd].albums[albInd].time;
        artists[artInd].albums[albInd].nsongs++;
        artists[artInd].time += artists[artInd].albums[albInd].time;
        artists[artInd].nsongs++;
        //**

        ss.str("");             // clear out string stream
        ss.clear();
    }

    // Display output
    for(int i = 0; i < artists.size(); i++)     // print artists
    {
        cout << artists[i] << endl;

        for(int j = 0; j < artists[i].albums.size(); j++)   // print albums
        {
            cout << artists[i].albums[j] << endl;

            for(int k = 0; k < artists[i].albums[j].nsongs; k++)    // print songs
            {
                cout << artists[i].albums[j].songs[k] << endl;
            }
        }
    }
    return 0;
}

// -1 -> not found, [0-#] -> index of artist
int isArtistRecorded(vector<Artist> a, string b)
{
    for(int i = 0; i < a.size(); i++)
    {
        if(strcmp( a[i].name.c_str(), b.c_str() ) == 0)
            return i;
    }
    return -1;
}

int isAlbumRecorded(vector<Artist> a, int i, string b)
{
    for(int j = 0; j < a[i].albums.size(); j++)
    {
        if(strcmp( a[i].albums[j].name.c_str(), b.c_str() ) == 0)
            return j;
    }
    return -1;
}

int timeToInt(string a)
{
    int pos = a.find(":");
    int min = stoi( a.substr(0,pos) );
    int sec = stoi( a.substr(pos+1) );
    cout << (min*60)+sec << endl;
    return (min*60)+sec;
}

/*
void sortArtists(&vector<Artist> a)
{

}

void sortAlbums(&vector<Album> a)
{

}
*/
