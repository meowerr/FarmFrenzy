#pragma once
#include "./Entities/Animal.h"
#include "./Core/Game.h"

class Wolf : public Animal // Wolf Is-A Animal, i put in separate file because its an enemy.
{
public:
	Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
	bool handleClick(int x, int y);

};