#include <iostream>
#include <fileref.h>
#include <tag.h>
#include "Song.hpp"

#include <filesystem>
#include <vector>
#include "Database.hpp"

using itr = std::filesystem::directory_iterator;


/*
int main(){
    std::string path = "songs";
    for (const auto& entry : itr(path)){
        Song s;
        std::string file_path = entry.path();
        TagLib::FileRef f(file_path.c_str());
        if (f.isNull() || !f.tag()){
            std::cout << "Error when trying to read song.\n";
            return 1;
        }
        TagLib::Tag *tag = f.tag();
        s.set_artist(tag->artist().to8Bit(true));
        s.set_title(tag->title().to8Bit(true));
        s.set_album(tag->album().to8Bit(true));
        s.set_year_rel(tag->year());

        Database::add_song(s);

    }


    

    
    for (const auto& song : Database::get_all_songs()){
        std::cout << "Title: " << song->get_title() << "\n";
        std::cout << "Artist: " << song->get_artist() << "\n";
        std::cout << "Album: " << song->get_album() << "\n";
        std::cout << "Year: " << song->get_year_rel() << "\n";
        std::cout << "\n\n";
    }
    

    return 0;
}

*/