#include "Animal.h"
#include "../UI/BudgetBar.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include "../Wolf.h"
#include <iostream>
using namespace std;

Animal::Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
	curr_pos = r_point;
	curr_vel.x = rand() % 3; // random number from 0 to 2. Random starting velocity
	curr_vel.y = rand() % 3; 

}

void Animal::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

Chick::Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{}

void Chick::moveStep() //is being called continuously in budgetbar
{
	//TO DO: add code for cleanup and game exit here
	/*
	//draw image of this object in the field
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
	*/

	RefPoint.x += curr_vel.x; // inc. its x point contin. "velocity of x direction"
	RefPoint.y += curr_vel.y; //inc. its y point contin. "velocity of y direction"
	if (RefPoint.x > range_max_x || RefPoint.x < range_min_x) { curr_vel.x = -1*curr_vel.x; }
	if (RefPoint.y > range_max_y || RefPoint.y < range_min_y ) { curr_vel.y = -1*curr_vel.y; }

	//cout << "Icon Chick Moved" << endl; //commented this to avoid lagging in terminal
}

Cow::Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{}


void Cow::moveStep() 
{
	//TO DO: add code for cleanup and game exit here
	RefPoint.x += curr_vel.x;
	RefPoint.y += curr_vel.y;
	if (RefPoint.x > range_max_x || RefPoint.x < range_min_x) { curr_vel.x = -1 * curr_vel.x; }
	if (RefPoint.y > range_max_y || RefPoint.y < range_min_y) { curr_vel.y = -1 * curr_vel.y; }
	//cout << "Icon Cow moved" << endl; removed this so no lag in cmd

}




