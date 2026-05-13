#pragma once
#include "./Entities/Animal.h"
#include "./Core/Game.h"




class Wolf : public Animal           //////////////////////////////////////// Wolf Class updated to be draggable      ------     malek
{
public:
	bool isDragged = false; // Flag to track if the wolf is being held

	Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
	bool handleClick(int x, int y);

	virtual void moveStep() override;
	virtual void draw() const override; // Overriding to draw the red arrow
	void setLocation(int nx, int ny);   // Function to update position during drag
};