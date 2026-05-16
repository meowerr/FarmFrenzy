#pragma once
#include "SFML/Audio.hpp"

class soundPlayer {
private:
	sf::SoundBuffer chick;
	sf::SoundBuffer wolf;
	sf::SoundBuffer cat;
	sf::SoundBuffer grass;
	sf::SoundBuffer drop;
	sf::SoundBuffer lvlUP;
	sf::SoundBuffer click;
	sf::SoundBuffer cow; // Declared safely inside the class

	sf::Sound schick;
	sf::Sound sdrop;
	sf::Sound slvlUP;
	sf::Sound sclick;
	sf::Sound swolf;
	sf::Sound scat;
	sf::Sound sgrass;
	sf::Sound scow;
public:

	soundPlayer() { initializeSF(); }
	bool initializeSF();
	void playschick();
	void playsdrop();
	void playslvlUP();
	void playsclick();
	void playswolf();
	void playscat();
	void playsgrass();
	void playscow();

};