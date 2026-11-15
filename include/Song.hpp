#ifndef SONG_HPP
#define SONG_HPP
#include <memory>
#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Song{

    sf::Texture imgTexture;
    sf::Sprite *imgSprite;
    std::string file_name;
    std::string title;
    std::string artist;
    std::string album;
    unsigned int year_rel;
    unsigned int times_played;
    

public:
    Song();
    Song(const Song& song) = delete;
    Song &operator=(Song &song) = delete;

    ~Song();

    void set_file_name(const std::string& file_name);
    void set_title(const std::string& title);
    void set_artist(const std::string& artist);
    void set_album(const std::string& album);
    void set_year_rel(const int year_rel);
    void setImage(const sf::Texture &texture);



    void inc_times_played();

    std::string get_file_name() const;
    std::string get_title() const;
    std::string get_artist() const;
    std::string get_album() const;
    unsigned int get_year_rel() const;
    unsigned int get_times_played() const;
    const sf::Sprite *getImage() const;


    void save(std::ofstream& file);

    static std::unique_ptr<Song> load(std::ifstream& file);

};


#endif