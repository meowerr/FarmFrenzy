#pragma once
#include "../Core/Drawable.h"
#include "../Entities/Animal.h"
#include "../Config/GameConfig.h"
#include <random>
#include <limits>


const int range_min_x = 50;
const int range_max_x = config.windWidth - 50;
const int range_min_y = (config.toolBarHeight * 2) + 50;
const int range_max_y = config.windHeight - config.statusBarHeight - 50;         ///////////////// MALEK

const int MAX_ITEMS = 300;



//Base class for all toolbar icons 
class BudgetbarIcon :public Drawable
{
private:
	//string image_path;
public:
	string image_path;
	BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override;
	virtual void moveAllAnimals(Grass** grasslist) = 0; //pass through every grass in field
	// Change to accept coordinates:
	virtual void onClick(int x, int y) = 0;                                           ///////////// Malek
};
class Grass :public Drawable //had to define new class for grass since it isnt a budget bar icon
{
private:
	string image_path;
public:
	int foodcounter=1000;// add food counter to grass class and intialize to 1000
	Grass(Game* r_pGame, point r_point, int r_width, int r_height, string img_path,int foodcounter);// add food counter to constructor
	virtual void draw() const override; //only draw, no click
	void decreasefoodcounter() { // add function to decrease food counter
		if (foodcounter != 0) {
			foodcounter--;
		}
	}
};

class ChickIcon : public BudgetbarIcon
{
public:
	Chick** chickList;
	int count = 0;
	ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick(int x, int y) override;                                    ///////////// Malek

	void moveAllAnimals(Grass** grasslist) override;
};
 

class CowIcon : public BudgetbarIcon
{
public:
	Cow** CowList;
	int count = 0;
	CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick(int x, int y) override;                                      ///////////// Malek
	void moveAllAnimals(Grass** grasslist) override;
};
class WaterIcon : public BudgetbarIcon
{
public:
	Grass** Grasslist;
	int count = 0;
	WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick(int x, int y) override;                                      ///////////// Malek
	void moveAllAnimals(Grass** grasslist){ }
	virtual void draw() const override; // cant use default draw since we want to draw grass in the field when we click on water icon
};



// TO DO: The rest of icons in the toolbar

enum ANIMAL_ICONS //The icons of the toolbar (you should add more icons)
{
	//Note: Icons are ordered here as they appear in menu
	//If you want to change the menu icons order, change the order here
	ICON_CHICK,ICON_COW,ICON_WATER,

	//TODO: Add more icons names here

	//Cow icon

	ANIMAL_COUNT		//no. of menu icons ==> This should be the last line in this enum
};

class Budgetbar : public Drawable
{
private:
	BudgetbarIcon** iconsList; //an array of toolbarIcon pointers
	string iconsImages[ANIMAL_COUNT];

public:
	Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height);
	~Budgetbar();
	void draw() const override;


	bool handleClick(int x, int y);	//handles clicks on toolbar icons, returns true if exit is clicked

};

