#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"

class Game;     //forward declaration == will be described later 

struct point //always public 
{
	int x, y;
};


class Drawable
{
protected: //means only this class and subclasses can access the info 
	point RefPoint;		//Each game object must have a reference point x/y
	int width, height;
	Game* pGame;        //pGame now knows where Game is in the memory (address)

public:
	Drawable(Game* r_pGame, point r_point, int r_width, int r_height); //constructor
	virtual ~Drawable() {} // destructor
	virtual void draw() const = 0; //each child of Drawable has to define a draw() function on its own
	point getrefpoint() const { return RefPoint; } //getter for ref point
	int getwidth() const { return width; } //getter for width
	int getheight() const { return height; } //getter for height
};

