#include "Song.hpp"
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>


void write_str(std::ofstream& file, const std::string& s){
    std::uint32_t s_len = static_cast<std::uint32_t>(s.size());
    file.write(reinterpret_cast<const char*>(&s_len), sizeof(s_len));
    file.write(s.data(), s_len);
}

void read_str(std::ifstream& file, std::string& s){
    std::uint32_t s_len = 0;
    file.read(reinterpret_cast<char *>(&s_len), sizeof(s_len));


    s.resize(s_len);
    if (0 < s_len){
        file.read(s.data(), s_len);
    }
}

Song::Song() : file_name("No File Name"), title("No Song Title"),
                artist("No Song Artist"), album("No Song Album"),
                year_rel(0), times_played(0){}

void Song::set_file_name(const std::string& file_name){
    this->file_name = file_name;
}
void Song::set_title(const std::string& title){
    this->title = title;
}
void Song::set_artist(const std::string& artist){
    this->artist = artist;
}
void Song::set_album(const std::string& album){
    this->album = album;
}
void Song::set_year_rel(const int year_rel){
    this->year_rel = year_rel;
}

void Song::inc_times_played(){
    ++times_played;
}

std::string Song::get_file_name() const{return file_name;}

std::string Song::get_title() const{return title;}

std::string Song::get_artist() const{return artist;}

std::string Song::get_album() const{return album;}

unsigned int Song::get_year_rel() const{return year_rel;}


unsigned int Song::get_times_played() const{return times_played;}


void Song::save(std::ofstream& file){
    write_str(file, file_name);
    write_str(file, title);
    write_str(file, artist);
    write_str(file, album);
    std::uint32_t year_r = year_rel;
    std::uint32_t times_p = times_played;
    file.write(reinterpret_cast<const char*>(&year_r), sizeof(year_r));
    file.write(reinterpret_cast<const char*>(&times_p), sizeof(times_p));
    
    std::cout << title << " successfully saved!\n";
}


Song Song::load(std::ifstream& file){
    Song song;

    read_str(file, song.file_name);
    read_str(file, song.title);
    read_str(file, song.artist);
    read_str(file, song.album);
    std::uint32_t year_r = 0;
    std::uint32_t times_p = 0;
    std::uint32_t genre_size  =0;

    file.read(reinterpret_cast<char *>(&year_r), sizeof(year_r));
    file.read(reinterpret_cast<char *>(&times_p), sizeof(times_p));
    file.read(reinterpret_cast<char *>(&genre_size), sizeof(genre_size));

    song.year_rel = year_r;
    song.times_played = times_p;

    std::cout << song.title << " successfully loaded!\n";
    return song;
}

