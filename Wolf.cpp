#include "./Wolf.h"


////////////////////////////////////////////////////////////////////////////////////////////      Wolf movement Updated ------ malek


Wolf::Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Animal(r_pGame, r_point, r_width, r_height, img_path) {
}

void Wolf::moveStep() {
	if (isDragged) return; // Freeze random movement while the user holds the wolf!

	RefPoint.x += curr_vel.x;
	RefPoint.y += curr_vel.y;

	//Reverse direction when window boundary is hit 
	if (RefPoint.x > range_max_x || RefPoint.x < range_min_x) { curr_vel.x = -1 * curr_vel.x; }
	if (RefPoint.y > range_max_y || RefPoint.y < range_min_y) { curr_vel.y = -1 * curr_vel.y; }

	curr_pos = RefPoint; // Sync positions
}

void Wolf::draw() const {
	Animal::draw(); // Draw the normal wolf image

	if (isDragged) {
		window* pWind = pGame->getWind();

		int cx = RefPoint.x + width / 2; // Center X of the wolf
		int ty = RefPoint.y - 5;         // Just above the wolf

		// Draw a red arrow pointing down at the wolf
		pWind->SetPen(RED, 2);
		pWind->SetBrush(RED);
		// Arrowhead
		pWind->DrawTriangle(cx, ty, cx - 10, ty - 15, cx + 10, ty - 15);
		// Arrow Tail
		pWind->SetPen(RED, 4);
		pWind->DrawLine(cx, ty - 15, cx, ty - 30);
	}
}

void Wolf::setLocation(int nx, int ny) {
	RefPoint.x = nx;
	RefPoint.y = ny;
	curr_pos.x = nx;
	curr_pos.y = ny;
}