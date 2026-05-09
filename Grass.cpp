#include "Grass.h"
#include <iostream> 
#include "Core/Game.h"
using namespace std;

Grass::Grass(Game* r_pGame, point r_point, int r_width, int r_height, string img_path, int r_foodcounter) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
	foodcounter = r_foodcounter;
	width = r_width;
	height = r_height;
	RefPoint = r_point;

}
void Grass::draw() const
{
	window* pWind = pGame->getWind();
	pGame->drawfoodarea(RefPoint.x, RefPoint.y); //use function drawfoodarea
	pWind->SetPen(BLACK, 50); //display food count above food area
	pWind->SetFont(16, BOLD, BY_NAME, "Arial");
	pWind->DrawString(RefPoint.x + 10, RefPoint.y + 15, to_string(foodcounter));
}