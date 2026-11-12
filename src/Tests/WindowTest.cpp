
#include "MediaWindow.hpp"
#include "Song.hpp"
#include "Database.hpp"
#include "tag.h"
#include "fileref.h"
#include <string>
#include <filesystem>


using itr = std::filesystem::directory_iterator;

/*

int  main(){
    // Load all songs from the songs directory into the database
    std::string path = "songs";
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

    SongGraph graph;
    graph.graph_by_artist(); 

    // Create and run the media window
    MediaWindow w(&graph);
    w.run();
    
    return 0;
}





*/