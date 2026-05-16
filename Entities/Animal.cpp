#include "Animal.h"
#include "../UI/BudgetBar.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include "../Wolf.h"
#include <iostream>
#include "../Grass.h"
using namespace std;

Animal::Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
	curr_pos = r_point;
	width = r_width;
	height = r_height;
	RefPoint = r_point;
	curr_vel.x = (rand() % 2)+1; // random number from 0 to 2. Random starting velocity
	curr_vel.y = (rand() % 2)+1; 
	lastseentime = pGame->timer; // time taken from timer
	animalcounter = 0; // animal counter to count seconds
}

void Animal::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();

	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
	if (image_path != "images\\wolf.jpg" && image_path != "images\\cat.jpg") {
		pWind->SetPen(BLACK, 50); //display animal counter above animal except wolf
		pWind->SetFont(16, BOLD, BY_NAME, "Arial");
		pWind->DrawString(RefPoint.x + 10, RefPoint.y - 20, to_string(animalcounter));

	}
}

Chick::Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{
	
	 timermax=10; //max timer for each animal, when counter reaches timermax, spawn egg 

}

void Chick::moveStep() //is being called continuously in budgetbar
{

	RefPoint.x += curr_vel.x;
	RefPoint.y += curr_vel.y;
	if (RefPoint.x > range_max_x || RefPoint.x < range_min_x) { curr_vel.x = -1*curr_vel.x; }
	if (RefPoint.y > range_max_y || RefPoint.y < range_min_y ) { curr_vel.y = -1*curr_vel.y; }

	if (pGame->timer != lastseentime) { //if time changed, increase animal counter
		animalcounter++;
		lastseentime = pGame->timer; //update timer
	}
	if (animalcounter >= timermax) { //if animal counter reaches timer max, spawn milk
		pGame->drawegg(RefPoint.x, RefPoint.y); //draw milk at cow position
		animalcounter = 0;
	}
	//cout << "Icon Chick Moved" << endl;
}

Cow::Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{
	timermax = 15; //max timer for each animal, when counter reaches timermax, milk
}


void Cow::moveStep() 
{
	//TO DO: add code for cleanup and game exit here
	RefPoint.x += curr_vel.x;
	RefPoint.y += curr_vel.y;
	if (RefPoint.x > range_max_x || RefPoint.x < range_min_x) { curr_vel.x = -1 * curr_vel.x; }
	if (RefPoint.y > range_max_y || RefPoint.y < range_min_y) { curr_vel.y = -1 * curr_vel.y; }
	//cout << "Icon Cow moved" << endl; removed this so no lag in cmd
	if (pGame->timer != lastseentime) { //if time changed, increase animal counter
		animalcounter++;
		lastseentime = pGame->timer; //update timer
	}
	if (animalcounter >= timermax) { //if animal counter reaches timer max, spawn milk
		pGame->drawmilk(RefPoint.x, RefPoint.y); //draw milk at cow position
		animalcounter = 0;
	}

}
Cat::Cat(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{
	 
}
void Cat::moveStep()
{
	//TO DO: add code for cleanup and game exit here
	RefPoint.x += 3*curr_vel.x;
	RefPoint.y += 3*curr_vel.y;
	if (RefPoint.x > range_max_x || RefPoint.x < range_min_x) { curr_vel.x = -1 * curr_vel.x; }
	if (RefPoint.y > range_max_y || RefPoint.y < range_min_y) { curr_vel.y = -1 * curr_vel.y; }
}

bool Animal:: iscolliding(Grass* targetgrass){ //function to check if colliding with grass
	int animalleft = RefPoint.x; //left edge of animal is the refpoint.x
int animalup = RefPoint.y; //up edge of animal is the refpoint.y
int animalright = RefPoint.x + width; //to get right edge of animal, we add width to refpoint.x
int animaldown = RefPoint.y + height; //to get down edge of animal, we add height to refpoint.y
int grassleft = targetgrass->getrefpoint().x; //use getter functions to get refpoint.x of grass, which is left edge
int grassup = targetgrass->getrefpoint().y; //use getter functions to get refpoint.y of grass, which is up edge
int grassright = targetgrass->getrefpoint().x + targetgrass->getwidth(); //to get right edge, we use getter functions to get width and refpoint.x and add them
int grassdown = targetgrass->getrefpoint().y + targetgrass->getheight(); //to get down edge, we use getter functions to get height and refpoint.y and add them
if (animalright > grassleft && animalleft<grassright && animaldown>grassup && animalup < grassdown) { //animal mus be under grassup, to the right of grassleft, to the left of grassright, and above grassdown
	
	return true;
}
return false;
	}

bool Animal::wolfcolliding(Wolf* wolf) { //function to check if colliding with grass
	int animalleft = RefPoint.x; //left edge of animal is the refpoint.x
	int animalup = RefPoint.y; //up edge of animal is the refpoint.y
	int animalright = RefPoint.x + width; //to get right edge of animal, we add width to refpoint.x
	int animaldown = RefPoint.y + height; //to get down edge of animal, we add height to refpoint.y
	int wolfleft = wolf->getrefpoint().x; //use getter functions to get refpoint.x of grass, which is left edge
	int wolfup = wolf->getrefpoint().y; //use getter functions to get refpoint.y of grass, which is up edge
	int wolfright = wolf->getrefpoint().x + wolf->getwidth(); //to get right edge, we use getter functions to get width and refpoint.x and add them
	int wolfdown = wolf->getrefpoint().y + wolf->getheight(); //to get down edge, we use getter functions to get height and refpoint.y and add them
	if (animalright > wolfleft && animalleft<wolfright && animaldown>wolfup && animalup < wolfdown) { //animal mus be under grassup, to the right of grassleft, to the left of grassright, and above grassdown

		return true;
	}
	return false;
}



