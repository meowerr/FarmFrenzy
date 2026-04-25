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
	//virtual void moveAllAnimals() = 0;
	point getRef() { return RefPoint; }
	int getWidth() { return width; }
	int getHeight() { return height; }

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
	~ChickIcon() {
		for (int i = 0; i < count; i++) {
			if (chickList[i] != nullptr) delete chickList[i];
		}
		delete[] chickList; 
	}

	virtual void onClick(int x, int y) override;                                    ///////////// Malek



	void moveAllAnimals(Grass** grasslist) {
		for (int i = 0; i < MAX_ITEMS; i++) {
			if (chickList[i] != nullptr) {
				chickList[i]->moveStep();
				for (int j = 0; j < 15; j++) { //loop through grasslist to check if colliding with any grass
					if (grasslist[j] != nullptr) {
						if (chickList[i]->iscolliding(grasslist[j])) {
							grasslist[j]->decreasefoodcounter(); // if colliding, decrease food counter
							if (grasslist[j]->foodcounter == 0) { //if food counter reach 0, delete grass and set pointer to null
								delete grasslist[j];
								grasslist[j] = nullptr;
							}
						}
					}
				}
				chickList[i]->draw();
			}
		}
	}
};


class CowIcon : public BudgetbarIcon
{
public:
	Cow** CowList;
	int count = 0;
	CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	~CowIcon() {
		for (int i = 0; i < count; i++) {
			if (CowList[i] != nullptr) delete CowList[i];
		}
		delete[] CowList;
	}
	virtual void onClick(int x, int y) override;                                      ///////////// Malek
	void moveAllAnimals(Grass** grasslist) { 
		for (int i = 0; i < MAX_ITEMS; i++) {
			if (CowList[i] != nullptr) {
				CowList[i]->moveStep();
				for (int j = 0;j < 15;j++) { //loop through grasslist to check if colliding with any grass
					if (grasslist[j] != nullptr) {
						if (CowList[i]->iscolliding(grasslist[j])) {
							grasslist[j]->decreasefoodcounter(); // if colliding, decrease food counter
							if (grasslist[j]->foodcounter == 0) { //if food counter reach 0, delete grass and set pointer to null
								delete grasslist[j];
								grasslist[j] = nullptr;
							}
						}
					}
				}
				CowList[i]->draw();
			}
		}
	}
};
class WaterIcon : public BudgetbarIcon
{
public:
	Grass** Grasslist;
	int count = 0;
	WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	~WaterIcon() {
		for (int i = 0; i < count; i++) {
			if (Grasslist[i] != nullptr) delete Grasslist[i];
		}
		delete[] Grasslist;
	}
	virtual void onClick(int x, int y) override;                                      ///////////// Malek
	void moveAllAnimals(Grass** grasslist){ }
	virtual void draw() const override; // cant use default draw since we want to draw grass in the field when we click on water icon
};
	class CowIcon : public BudgetbarIcon
	{
	public:
		Cow** CowList;
		int count = 0;
		CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
		virtual void onClick(int x, int y) override;                                      ///////////// Malek
		void moveAllAnimals(Grass** grasslist) {
			for (int i = 0; i < MAX_ITEMS; i++) {
				if (CowList[i] != nullptr) {
					CowList[i]->moveStep();
					for (int j = 0; j < 15; j++) { //loop through grasslist to check if colliding with any grass
						if (grasslist[j] != nullptr) {
							if (CowList[i]->iscolliding(grasslist[j])) {
								grasslist[j]->decreasefoodcounter(); // if colliding, decrease food counter
								if (grasslist[j]->foodcounter == 0) { //if food counter reach 0, delete grass and set pointer to null
									delete grasslist[j];
									grasslist[j] = nullptr;
								}
							}
						}
					}
					CowList[i]->draw();
				}
			}
		}
	};
	class WaterIcon : public BudgetbarIcon
	{
	public:
		Grass** Grasslist;
		int count = 0;
		WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
		virtual void onClick(int x, int y) override;                                      ///////////// Malek

		void moveAllAnimals() {}

		void moveAllAnimals(Grass** grasslist) {}

		virtual void draw() const override; // cant use default draw since we want to draw grass in the field when we click on water icon
	};



	// TO DO: The rest of icons in the toolbar

	enum ANIMAL_ICONS //The icons of the toolbar (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_CHICK, ICON_COW, ICON_WATER,

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

