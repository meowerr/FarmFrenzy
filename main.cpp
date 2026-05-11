#include "./Core/Game.h"
#include "SFML/Audio.hpp"


int main()
{

	sf::Music bgmusic;
	if (bgmusic.openFromFile("track.wav")) {
		bgmusic.setLoop(true);
		bgmusic.play();
		bgmusic.setVolume(20);
	}


	//Create an object of controller
	Game game; //create a game object

	game.go(); //call go() function
}
