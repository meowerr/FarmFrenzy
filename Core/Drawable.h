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
	point RefPoint;		//Each game object must have a reference point
	int width, height;
	Game* pGame;        //pGame now knows where Game is in the memory (address)

public:
	Drawable(Game* r_pGame, point r_point, int r_width, int r_height); //constructor
	virtual void draw() const = 0; //?
};

