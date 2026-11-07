

#include "Database.hpp"
#include "Song.hpp"
#include <cstdlib>
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>


//for serializing
#include <fstream>


bool ByTimesListened::operator()(const Song* s1, const Song *s2) const{
       return s1->get_times_played() < s2->get_times_played();
   }


const std::string Database::songs_file = std::string(std::getenv("HOME")) + 
    "/Music/mp3ME/songs.bin";
std::vector<std::unique_ptr<Song>> Database::songs{};
std::unordered_map<std::string, std::vector<Song*>> Database::songs_by_artists{};
std::unordered_map<std::string, std::vector<Song*>> Database::songs_in_album{};
std::priority_queue<Song*, std::vector<Song*>, ByTimesListened> Database::top_songs{};




void Database::save_songs(){
   std::ofstream file(songs_file, std::ios::binary);
   if (!file.is_open()){
       std::cerr << "Error when trying to save songs.\n";
       return;
   }
  


   std::uint32_t songs_size = static_cast<std::uint32_t>(songs.size());
   file.write(reinterpret_cast<const char*>(&songs_size), sizeof(songs_size));
   for (const auto& song : songs){
       song->save(file);
   }


}




bool Database::load_songs(){
   std::ifstream file(songs_file, std::ios::binary);
  
   songs.clear();
   songs_by_artists.clear();
   songs_in_album.clear();


   if (!file.is_open()){
       std::cerr << "Could not load songs.\n";
       return false;
   }


   std::uint32_t songs_size = 0;
   file.read(reinterpret_cast<char *>(&songs_size), sizeof(songs_size));


   songs.reserve(songs_size);
   for (std::uint32_t x = 0; x < songs_size; ++x){
       Song song = Song::load(file);
       add_song(song);
   }
   return true;
}


Database::Database(){


}


bool Database::artist_exists(const std::string& artist){
   return songs_by_artists.find(artist) != songs_by_artists.end();
}


void Database::add_to_artist(const std::string& artist, Song *pSong){
   songs_by_artists.at(artist).push_back(pSong);
}


bool Database::album_exists(const std::string& album){
   return songs_in_album.find(album) != songs_in_album.end();
}


void Database::make_artist(const std::string& artist){
   std::vector<Song*> artist_songs {};
   songs_by_artists[artist] = artist_songs;
}


void Database::make_album(const std::string& album){
   std::vector<Song*> album_songs {};
   songs_in_album[album] = album_songs;
}


void Database::add_to_album(const std::string& album, Song *pSong){
   songs_in_album.at(album).push_back(pSong);
}






void Database::add_song(const Song& song){
   std::unique_ptr<Song> spSong = std::make_unique<Song>(song);
   Song *pSong = spSong.get();


   std::string artist = song.get_artist();
   std::string album_title = song.get_album();


   if (!artist_exists(artist)){
       make_artist(artist);
   }


   add_to_artist(artist, pSong);




   std::string album = artist + album_title;


   if (!album_exists(album)){
       make_album(album);
   }


   add_to_album(album, pSong);


   songs.push_back(std::move(spSong));
  
}






void Database::remove_song(const Song& song){


   std::string artist = song.get_artist();
   std::string album_title = song.get_album();
   std::string title = song.get_title();


   std::string album_key = artist + album_title;


   //remove by artist
   auto artistIt = songs_by_artists.find(artist);


   if(artistIt != songs_by_artists.end()) { //if found
       auto& vec = artistIt->second;


       vec.erase(
           std::remove_if(vec.begin(), vec.end(),
           [&](Song* s) { //return true if song matches the criterias to remove
               return s->get_title() == title
                      && s->get_artist() == artist
                      && s->get_album() == album_title;
                }
            ),
            vec.end()
       );


       if(vec.empty()){
           songs_by_artists.erase(artistIt);
       }
   }


   //remove by album
   auto albumIt = songs_in_album.find(album_key);
   if(albumIt != songs_in_album.end()){
       auto& vec = albumIt->second;


       vec.erase(
           std::remove_if(vec.begin(), vec.end(),
           [&](Song* s) {
               return s->get_title() == title
                      && s->get_artist() == artist
                      && s->get_album() == album_title;
                }
            ),
            vec.end()
       );


       if(vec.empty()){
           songs_in_album.erase(albumIt);
       }
   }


   //remove by songs
   songs.erase(
           std::remove_if(songs.begin(), songs.end(),
           [&](const std::unique_ptr<Song>& sp) {
               return sp->get_title() == title
                      && sp->get_artist() == artist
                      && sp->get_album() == album_title;
                }
            ),
            songs.end()
       );
}






std::vector<std::unique_ptr<Song>>& Database::get_all_songs(){return songs;}


std::vector<Song*>& Database::get_artist_songs(const std::string& artist){
   if (artist_exists(artist)){
       return songs_by_artists.at(artist);
   }


   throw std::out_of_range("Artist " + artist + " not found.\n");
}


std::vector<Song*>& Database::get_album_songs(const std::string& artist,
                                               const std::string& album){
   std::string art_alb = artist + album;
   if (album_exists(art_alb)){
       return songs_in_album.at(artist + album);
   }
  
   throw std::out_of_range("Album " + album + " by " +
                           artist + " not found.\n");


}




std::vector<Song*> Database::get_top_songs(){
   while (!top_songs.empty())
       top_songs.pop();


   for (const auto& song : songs){
       top_songs.push(song.get());
   }


   std::vector<Song*> top_songs_list{};
   int x = 0;
   while (!top_songs.empty() && x++ < 5){
       top_songs_list.push_back(top_songs.top());
       top_songs.pop();
   }


   return top_songs_list;


}
