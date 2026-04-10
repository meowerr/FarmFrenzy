#pragma once
#include "../Core/Drawable.h"
#include "../Entities/Animal.h"
#include "../Config/GameConfig.h"
#include <random>
#include <limits>

//Ranges for generating a random location for the animals
const int range_min_x = 50;
const int range_max_x = config.windWidth - 50;
const int range_min_y = (config.toolBarHeight * 2) + 50;
const int range_max_y = config.windHeight - config.statusBarHeight - 50;

//Base class for all toolbar icons 
class BudgetbarIcon :public Drawable
{
private:
	//string image_path;
public:
	string image_path;
	BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override;
	virtual void moveAllAnimals() = 0;
	virtual void onClick() = 0;   //The action that should be taken when this icon is clicked
};
class Grass :public Drawable //had to define new class for grass since it isnt a budget bar icon
{
private:
	string image_path;
public:
	Grass(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override; //only draw, no click
	
};

class ChickIcon : public BudgetbarIcon
{
public:
	Chick** chickList; //an array of Chick pointers
	int count = 0;
	ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();

	void drawAllChickens() {
		for (int i = 0; i < 15; i++) {
			if (chickList[i] != nullptr) {
				
				chickList[i]->draw();
			}
		}
	}

	void moveAllAnimals() {
		for (int i = 0; i < 15; i++) {
			if (chickList[i] != nullptr) {
				chickList[i]->moveStep();
				chickList[i]->draw();
			}
		}
	}
};

class CowIcon : public BudgetbarIcon
{
public:
	Cow** CowList; //an array of Cow pointers
	int count = 0;
	CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
	void moveAllAnimals() {
		for (int i = 0; i < 15; i++) {
			if (CowList[i] != nullptr) {
				CowList[i]->moveStep();
				CowList[i]->draw();
			}
		}
	}
};
class WaterIcon : public BudgetbarIcon
{
public:
	Grass** Grasslist; //an array of Grass pointers from class we defined
	int count = 0;
	WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
	void moveAllAnimals(){ }
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

