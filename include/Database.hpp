#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include <memory>
#include "Song.hpp"
#include <unordered_map>
#include <string>
#include <queue>

//for reading and writing objects


//removed structs
struct ByTimesListened{
    bool operator()(const Song* s1, const Song *s2) const;
};

class Database{
    static const std::string songs_file;
    static std::vector<std::unique_ptr<Song>> songs;
    static std::unordered_map<std::string, std::vector<Song*>> songs_by_artists;
    static std::unordered_map<std::string, std::vector<Song*>> songs_in_album;
    static std::priority_queue<Song*, std::vector<Song*>, ByTimesListened> top_songs;



    static bool artist_exists(const std::string& artist);
    static void make_artist(const std::string& artist);
    static void add_to_artist(const std::string& artist, Song *pSong);

    static bool album_exists(const std::string& album);
    static void make_album(const std::string& album);
    static void add_to_album(const std::string& album, Song *pSong);



public:
    

    Database();

    static void save_songs();

    static bool load_songs();

    static void add_song(std::unique_ptr<Song> song);

    static void remove_song(const Song& song);
    static std::vector<std::unique_ptr<Song>>& get_all_songs();

    static std::vector<Song*>& get_artist_songs(const std::string& artist);

    static std::vector<Song*>& get_album_songs(const std::string& artist,
                                                const std::string& album);


static std::vector<Song*> get_top_songs();

};

#endif