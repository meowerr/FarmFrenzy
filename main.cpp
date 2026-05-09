#include "./Core/Game.h"
#include "SFML/Audio.hpp"


int main()
{

	//sf::Music bgmusic;
	//if (bgmusic.openFromFile("track.wav")) { // demo track
	//	bgmusic.setLoop(true);
	//	bgmusic.play();
	//	bgmusic.setVolume(20);
	//}

	//bgmusic.play();


	//Create an object of controller
	Game game; //create a game object

	game.go(); //call go() function
}
