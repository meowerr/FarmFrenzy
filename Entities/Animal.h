#pragma once
#include "../Core/Drawable.h"

class Grass; 

class Animal :public Drawable // Animal Is-A of drawable
{
private:
	string image_path;
public:
	virtual ~Animal() {}
	point curr_pos;
	point curr_vel;
	//Animal();
	Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override; 
	//virtual void random();
	virtual void moveStep() = 0;  // The action that should be taken each time step, each child of animal should create its own movestep()
	bool iscolliding(Grass* targetgrass);  //function to check if colliding with grass
	int animalcounter; // animal counter to count seconds
	int timermax ; //max timer for each animal, when counter reaches timermax, spawn egg or milk
	int lastseentime; // time taken from timer
};

class Chick : public Animal 
{
public:
	Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
};


class Cow : public Animal
{
public:
	Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
};



//class Wolf : public Animal // Wolf Is-A Animal
//{
//public:
//	Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
//	virtual void moveStep();
//	static Wolf** wolfList;
//	int count = 0;
//	
//	
//	void moveAllAnimals() {
//		for (int i = 0; i < MAX_ITEMS; i++) {
//			if (wolfList[i] != nullptr) {
//				wolfList[i]->moveStep();
//				wolfList[i]->draw();
//			}
//		}
//	}
//
//}