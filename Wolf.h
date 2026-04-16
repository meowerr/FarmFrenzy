#pragma once
#include "./Entities/Animal.h"
#include "./Core/Game.h"

class Wolf : public Animal // Wolf Is-A Animal
{
public:
	Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();

};