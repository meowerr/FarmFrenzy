#include "Warehouse.h"
#include "Core/Game.h"

Warehouse::Warehouse(Game* r_pGame, point r_uprleft, int r_width, int r_height)
    : GameObject(r_pGame, r_uprleft, r_width, r_height, WHITE, BLACK)
{
    imagePath = "images\\warehouseicon.jpg";

    position = r_uprleft;
    objWidth = r_width;
    objHeight = r_height;
}

void Warehouse::draw() const                         /// updated the shape of the ware house icon to be more refined ( MALEK )
{
    window* pWind = pGame->getWind();

    // Draw a refined rounded border around the image to make it look like a neat UI element
    pWind->SetPen(WHITE, 3); // Clean white outline
    pWind->SetBrush(color(200, 200, 200)); // Light gray backing

    // The "15, 15" at the end tells CMUgraphics to round the corners of the rectangle!
    pWind->DrawRectangle(position.x - 5, position.y - 5, position.x + objWidth + 5, position.y + objHeight + 5, FILLED, 15, 15);

    // Draw the image on top
    pWind->DrawImage(imagePath, position.x, position.y, objWidth, objHeight);
}