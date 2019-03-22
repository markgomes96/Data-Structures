// Mark Gomes
// 03/21/19
// CSC 310 - Dr. Digh
// Lab 4

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string.h>
#include <algorithm>
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
    cout << "\t\t" << l.track << ".  " << l.title << " " << l.time/60 << ":";
    if ((l.time % 60) < 10) 
        cout << "0";
    cout << l.time % 60;
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
    int maxtrack;       // Largest track number

    bool operator < (Album another) const { return name < another.name;}
};

ostream & operator << (ostream &out, Album &l) 
{
    cout << "\t" << l.name << ": " << l.nsongs << ", " << l.time/60 << ":";
    if ((l.time % 60) < 10) 
        cout << "0";
    cout << l.time % 60;
}

class Artist 
{
  public :
    string name;    // Artist's name
    int time;       // Total time of all songs on all albums by this artist
    int nsongs;     // Total number of songs on all albums by this artist
    vector<Album> albums;

    bool operator < (Artist another) const { return name < another.name;}
};

ostream & operator << (ostream &out, Artist &l) 
{
    cout << l.name << ": " << l.nsongs << ", " << l.time/60 << ":";
    if ((l.time % 60) < 10)
        cout << "0";
    cout << l.time % 60;
}

int isArtistRecorded(vector<Artist> a, string b);
int isAlbumRecorded(vector<Artist> a, int i, string b);
int timeToInt(string a);

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
     
        replace( title.begin(), title.end(), '_', ' ');     // fix formating
        replace( artist.begin(), artist.end(), '_', ' ');
        replace( album.begin(), album.end(), '_', ' ');
        replace( genre.begin(), genre.end(), '_', ' ');
   
        //** handle artists **
        artInd = isArtistRecorded(artists, artist);

        if(artInd < 0)       // new artist found
        {
            Artist tmp_art;             // artist info
            tmp_art.name = artist;
            tmp_art.nsongs = 0;
            tmp_art.time = 0;

            int count = 0;
            bool placed = false;
            if(artists.size() == 0)
            {
                artists.push_back(tmp_art);
            }
            else    // insert artist in sorted spot
            {
                for(auto it = artists.begin(); it != artists.end(); ++it)
                {
                    if( tmp_art < *(it) )
                    {
                        it = artists.insert(it, tmp_art);
                        placed = true;
                        break;
                    }
                    count++;
                }
                if(!placed)     // handles elements sorted to end
                {
                    artists.insert(artists.end(), tmp_art);
                }
            }
            artInd = count;
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

            int count = 0;
            bool placed = false;
            if(artists[artInd].albums.size() == 0)
            {
                artists[artInd].albums.push_back(tmp_alb);
            }
            else        // insert album in sorted spot
            {
                for(auto it = artists[artInd].albums.begin(); it != artists[artInd].albums.end(); ++it)
                {
                    if( tmp_alb < *(it) )
                    {
                        it = artists[artInd].albums.insert(it, tmp_alb);
                        placed = false;
                        break;
                    }
                    count++;
                }
                if(!placed)     // handles elements sorted to end
                {
                    artists[artInd].albums.insert(artists[artInd].albums.end(), tmp_alb);
                }
            }
            albInd = count;
        }
        //**

        //** handle songs **
        int track_int = stoi(track);
        int time_val = timeToInt(time);
        Song tmp_song;                  // song info
        tmp_song.title = title;
        tmp_song.time = time_val;
        tmp_song.track = track_int;
        if(artists[artInd].albums[albInd].maxtrack < track_int)
            artists[artInd].albums[albInd].maxtrack = track_int;

        artists[artInd].albums[albInd].songs[track_int] = tmp_song;          // link song -> album
        //**

        //** update artists/albums **
        artists[artInd].albums[albInd].time += time_val;
        artists[artInd].albums[albInd].nsongs++;
        artists[artInd].time += time_val;
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

            for(int k = 0; k <= artists[i].albums[j].maxtrack; k++)    // print songs
            {
                // determine if track is recorded
                if(artists[i].albums[j].songs.find(k) != artists[i].albums[j].songs.end())
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
    return (min*60)+sec;
}
