#include "MediaWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Color.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "WindowADT.hpp"
#include <iostream>
#include "Database.hpp"
#include  "SongGraph.hpp"
#include <algorithm>
#include "PlayMedia.hpp"




MediaWindow::MediaWindow(SongGraph* g): WindowADT("Media Window"), 
song_title(nullptr),
artist_text(nullptr),
prev_label(title_font, "Prev", 18),
play_label(title_font, "Play", 18),
next_label(title_font, "Next", 18),
graph(g)
{
	//font
	if(!title_font.openFromFile("assets/Fonts/Sono-Bold.ttf")){
		std::cout << "No Font found.\n";
	}

	//Text: title and artist
	song_title = new sf::Text(title_font,  " ", 24);
	artist_text = new sf::Text(title_font, " ", 18); 

	song_title->setPosition({SCREEN_WIDTH / 2, 600});
	song_title->setFillColor(red);

	artist_text->setFillColor(red); 
	artist_text->setPosition({SCREEN_WIDTH / 2, 400});

	//load all songs
	 //fixme later
	load_songs();


	//Buttons
	sf::Vector2f buttonSize(100.0f, 40.0f); 
	float bottomY = 740.f;
	float labelY = bottomY + 8.0f;

	prev_button.setSize(buttonSize);
	play_button.setSize(buttonSize); 
	next_button.setSize(buttonSize);

	sf::Color buttonColor(green); 
	prev_button.setFillColor(buttonColor);
	play_button.setFillColor(buttonColor);
	next_button.setFillColor(buttonColor);

	prev_button.setPosition({150.0f, bottomY});
	play_button.setPosition({350.0f, bottomY});
	next_button.setPosition({550.0f, bottomY}); 

	//Labels
	prev_label.setString("Prev");
	play_label.setString("Play");
	next_label.setString("Next");
	
	prev_label.setFillColor(white);
	play_label.setFillColor(white);
	next_label.setFillColor(white);

	prev_label.setPosition({160.0f, labelY});
	play_label.setPosition({370.0f, labelY});
	next_label.setPosition({570.0f, labelY});
}


void MediaWindow::load_songs(){
	auto& all_songs = Database::get_all_songs();
	pm.set_queue(all_songs);

	songs.clear();
	songs.reserve(all_songs.size());
	for (const auto& song : all_songs){
		songs.push_back(song.get());
	}
	pm.set_queue(all_songs);
}

bool MediaWindow::contains_point(const sf::RectangleShape& rect, float x, float y){
	return rect.getGlobalBounds().contains({x, y}); 
}

void MediaWindow::handle_event(const sf::Event& event){

	if(event.is<sf::Event::Closed>()){
		Database::save_songs();
		window.close();
	}

	WindowADT::handle_event(event);
	

	//Event: mouse clicks
	if (auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()){ 

		float m_x = static_cast<float>(mouse->position.x);
		float m_y = static_cast<float>(mouse->position.y); 

	  if(mouse->button == sf::Mouse::Button::Left){ 

		//Event: Click song list
		int mouseY = mouse->position.y;
		int lineHeight = 24;
		int listStartY = 50;

		if(mouseY >= listStartY){ 
			int row = (mouseY - listStartY) / lineHeight; 
			int index = first_visible_index + row; 

			if(index >= 0 && index < static_cast<int>(songs.size())){
				selected_index = index;
				Song* s = songs[index];
				display_song_info(s);  
				play_selected_song(); 
				
			if(graph && s) {
				auto neighbors = graph->get_similar_songs(s);
				std::cout << "Similar songs from this artist: " <<s->get_title() << ":\n"; 
			
			if(neighbors.empty()){
				std::cout <<"No similar song found.\n"; 
			}
			else{
				for(Song* n : neighbors){
					if(n == s){
						continue; 
					}
					std::cout << " - by" << n->get_title() << " by " << n->get_artist() << "\n"; 
				}
			}
		}
	}
}


		//Event: button clicks
		if(contains_point(prev_button, m_x, m_y)){
			if(!songs.empty()){
				selected_index = (selected_index - 1 + static_cast<int>(songs.size())) %
								static_cast<int>(songs.size()); 
								display_song_info(songs[selected_index]);
								play_selected_song(); 
			}
			return; 
		}

		

		if(contains_point(play_button, m_x, m_y)){
			if(selected_index >= 0 && selected_index < static_cast<int>(songs.size())){
				display_song_info(songs[selected_index]);
				pm.toggle_song(); 
			}
			
			return; 
		}

		if(contains_point(next_button, m_x, m_y)){
			if(!songs.empty()){
				selected_index = (selected_index + 1) % static_cast<int>(songs.size());
				display_song_info(songs[selected_index]);
				play_selected_song(); 
			}
			return; 
		}
	  }
	}

	//Event: Scrolling
	if (auto* mouse = event.getIf<sf::Event::MouseWheelScrolled>()){
		int visibleSongs = 5;
		int max = static_cast<int>(songs.size()) - visibleSongs;

		if(max < 0) {
			max = 0;
		}
		if(mouse->delta < 0){
			//Event: scroll down
			if(first_visible_index < max){
				first_visible_index++;
			}
		}
		else if(mouse->delta > 0){
			//scroll down
			if(first_visible_index > 0){
				first_visible_index--; 
			}
		}
	}
}


	
void MediaWindow::display_song_title(const Song* song){
	if(!song || !song_title){
		return; 
	}
	song_title->setString(song->get_title());
	center_text(song_title);
}

void MediaWindow::display_song_artist(const Song* song){
	if(!song || !artist_text){
		return; 
	}
	artist_text->setString(song->get_artist());
	center_text(artist_text); 
}

void MediaWindow::display_song_album(const Song* song){
	display_song_title(song);
	display_song_artist(song); 
}


void MediaWindow::center_text(sf::Text* text){
	sf::FloatRect bounds = text->getLocalBounds();
	text->setOrigin(bounds.getCenter());
}

void MediaWindow::play_selected_song()
{
	if(selected_index < 0 || selected_index >= static_cast<int>(songs.size())){
		std::cout << "No song has been selected.\n"; 
		return;
	}

	pm.play_from_idx(songs, selected_index);
}


void MediaWindow::draw(){
	//draw title
	if (song_title){
		window.draw(*song_title);
	}

	//draw artist
	if (artist_text){
		window.draw(*artist_text);
	}

	//Draw: scrollable list
	float x = 50.0f;
	float y = 50.0f; 
	float lineHeight = 24.0f; 
	
	sf::Text lineText(title_font,"", 18);

	int visibleSongs = 5;
	int start = first_visible_index;
	int end = std::min(start + visibleSongs, static_cast<int>(songs.size()));

	for(int i = start; i < end; i++){
		Song* s = songs[i];
		
		if(!s){
			continue;
		}
		
		lineText.setString(s->get_title());
		lineText.setPosition({x,y});

		if(i == selected_index){
			lineText.setFillColor(red); 
		}
		else{
			lineText.setFillColor(green); 
		}
		window.draw(lineText);
		y += lineHeight; 
	}

	//draw buttons and labels
	window.draw(prev_button);
	window.draw(play_button);
	window.draw(next_button);

	window.draw(prev_label);
	window.draw(play_label);
	window.draw(next_label); 
}

void MediaWindow::display_song_info(const Song* song){
	display_song_title(song);
	display_song_artist(song);
}


MediaWindow::~MediaWindow(){
	delete song_title;
	delete artist_text; 
}

