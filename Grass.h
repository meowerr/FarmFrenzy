#pragma once
#include <string>
#include "Core/Drawable.h" 
using namespace std;

class Grass :public Drawable //had to define new class for grass since it isnt a budget bar icon
{
private:
	string image_path;
public:
	int foodcounter = 1000;// add food counter to grass class and intialize to 1000
	Grass(Game* r_pGame, point r_point, int r_width, int r_height, string img_path, int foodcounter);// add food counter to constructor
	virtual void draw() const override; //only draw, no click
	void decreasefoodcounter() { // add function to decrease food counter
		if (foodcounter != 0) {
			foodcounter--;
		}
	}
};