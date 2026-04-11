#include "Warehouse.h"
#include "Core/Game.h"

Warehouse::Warehouse(Game* r_pGame, point r_uprleft, int r_width, int r_height)
    : GameObject(r_pGame, r_uprleft, r_width, r_height, WHITE, BLACK)
{
    imagePath = "images\\warehouse.jpg";

    position = r_uprleft;
    objWidth = r_width;
    objHeight = r_height;
}

void Warehouse::draw() const
{
    window* pWind = pGame->getWind();
    pWind->DrawImage(imagePath, position.x, position.y, objWidth, objHeight);
}