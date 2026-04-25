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
    string eggtext = "Eggs: " + to_string(storedeggs) + " ($" + to_string(eggprice) + ")"; //display eggs,milk,prices, and total count
    string milkText = "Milk: " + to_string(storedmilk) + " ($" + to_string(milkprice) + ")";
    int totalcount = storedeggs + storedmilk;
    string totalText = "Total count: " + to_string(totalcount);
    pWind->SetPen(BLACK, 50); 
    pWind->SetFont(18, BOLD, BY_NAME, "Arial");
    pWind->DrawString(RefPoint.x + 10, RefPoint.y + 20, eggtext);
    pWind->DrawString(RefPoint.x + 10, RefPoint.y + 50, milkText);
    pWind->DrawString(RefPoint.x + 10, RefPoint.y + 80, totalText);
}