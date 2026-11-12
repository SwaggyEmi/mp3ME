#ifndef MEDIA_WINDOW_HPP
#define MEDIA_WINDOW_HPP

#include "WindowADT.hpp"
#include "SFML/Graphics/Font.hpp"
# include "SFML/Graphics/Text.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Song.hpp"
#include "Database.hpp"
#include <vector>
#include "PlayMedia.hpp"


class MediaWindow : public WindowADT{
	sf::Font title_font;
	sf::Text *song_title;
	sf::Text *artist_text;

	//song list
	std::vector<Song*> songs;
	


	int selected_index = -1; 
	int first_visible_index = 0; 


	//Buttons
	sf::RectangleShape prev_button;
	sf::RectangleShape play_button;
	sf::RectangleShape next_button;

	sf::Text prev_label;
	sf::Text play_label;
	sf::Text next_label; 

	//Queue / Logic
	PlayMedia pm;

	//Color
	sf::Color white = sf::Color::White;
	sf::Color blue = sf::Color(146, 175, 215); 
	sf::Color red = sf::Color(188, 71, 73); 
	sf::Color beige = sf::Color(242, 232, 207); 
	sf::Color green = sf::Color(56, 102, 65);


	bool contains_point(const sf::RectangleShape& rect, float x, float y); 

	void display_song_title(const Song* song);

	void display_song_artist(const Song* song);

	void display_song_album(const Song* song);

	void center_text(sf::Text* text);

	void play_selected_song(); 


protected:
	virtual void draw() override;
	void handle_event(const sf::Event& event) override; 

public:
	// MediaWindow();
	explicit MediaWindow(); 

	void load_songs();

	void display_song_info(const Song* song);

	~MediaWindow() override;
};

#endif