

#include <cstdlib>
#include <string>
#include "Database.hpp"
#include "Song.hpp"
#include "tag.h"
#include "fileref.h"
#include <iostream>
#include <filesystem>

#include "MediaWindow.hpp"

using itr = std::filesystem::directory_iterator;


void load_new_songs(){
    std::string home = std::getenv("HOME");
    std::string path = home + "/Music/mp3ME";
    if (!std::filesystem::is_directory(path)){
        std::filesystem::create_directory(path);
    }
    for (const auto& entry : itr(path)){
        std::string file_path = entry.path();
        TagLib::FileRef f(file_path.c_str());
        if (f.isNull() || !f.tag()){
            continue;
        }
        TagLib::Tag *tag = f.tag();
        Song s;
        s.set_file_name(file_path);
        s.set_artist(tag->artist().to8Bit(true));
        s.set_title(tag->title().to8Bit(true));
        s.set_album(tag->album().to8Bit(true));
        s.set_year_rel(tag->year());
        
        Database::add_song(s);
    }
}

int main(){
    
    if (!Database::load_songs()){
        load_new_songs();
    }

    MediaWindow m;

    
    m.run();

}


