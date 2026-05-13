#include "./Wolf.h"
#include "./Core/Game.h"

Wolf::Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path) {}

bool Wolf::handleClick(int x, int y) {
	return false;
}


void Wolf::moveStep() { //how the wolf moves

	for (int i = 0; i < pGame->level; i++) { 
		RefPoint.x += i*curr_vel.x; // multiply level by wolf velocity
		RefPoint.y += i*curr_vel.y;
	}
	//Reverse direction when window boundary is hit 
	if (RefPoint.x > range_max_x || RefPoint.x < range_min_x) { curr_vel.x = -1 * curr_vel.x; }
	if (RefPoint.y > range_max_y || RefPoint.y < range_min_y) { curr_vel.y = -1 * curr_vel.y; }
}
