#include "Budgetbar.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include <iostream>
using namespace std;



BudgetbarIcon::BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
}

void BudgetbarIcon::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);

	// Draw the Sell button at the bottom 15 pixels of the icon
	pWind->SetPen(DARKRED, 1);
	pWind->SetBrush(RED);
	pWind->DrawRectangle(RefPoint.x, RefPoint.y + height - 15, RefPoint.x + width, RefPoint.y + height);

	pWind->SetPen(WHITE, 1);
	pWind->SetFont(14, BOLD, BY_NAME, "Arial");
	pWind->DrawString(RefPoint.x + 18, RefPoint.y + height - 15, "SELL");
}

Grass::Grass(Game* r_pGame, point r_point, int r_width, int r_height, string img_path,int r_foodcounter) : Drawable(r_pGame, r_point, r_width, r_height)
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

}
ChickIcon::ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
	chickList = new Chick * [MAX_ITEMS];
	for (int i = 0; i < MAX_ITEMS; i++) {
		chickList[i] = nullptr;
	}
}


CowIcon::CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
	CowList = new Cow * [MAX_ITEMS];
	for (int i = 0; i < MAX_ITEMS; i++) {
		CowList[i] = nullptr;
	}
}


WaterIcon::WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
	Grasslist = new Grass * [MAX_ITEMS];
	for (int i = 0; i < MAX_ITEMS; i++) { // Changed 10 to 15 to prevent memory crashes
		Grasslist[i] = nullptr;
	}
}


void WaterIcon::draw() const
{
	BudgetbarIcon::draw(); // Draw the button
	for (int i = 0; i < count; i++) { //loop to draw grass
		if (Grasslist[i] != nullptr) {
			Grasslist[i]->draw();
		}
	}
}

void ChickIcon::onClick(int x, int y)
{
	// Check if the click was in the bottom 15 pixels (SELL area)
	if (y >= RefPoint.y + height - 15) {
		if (count > 0) {
			count--;
			delete chickList[count];         // Free the memory
			chickList[count] = nullptr;      // Prevent dangling pointers
			pGame->budget += 100;             // Refund $100

			pGame->clearBudget();
			pGame->printBudget("BUDGET = $" + to_string(pGame->budget));
			cout << "Icon Chick Sold" << endl;
		}
	}
	else { // BUY area clicked
		cout << "Icon Chick Clicked" << endl;
		if (count < MAX_ITEMS && pGame->budget >= 100) {
			pGame->budget -= 100;
			pGame->clearBudget();
			pGame->printBudget("BUDGET = $" + to_string(pGame->budget));

			point p;
			std::random_device rd1;
			std::mt19937 gen1(rd1());
			std::uniform_int_distribution<int> dist1(range_min_x, range_max_x);
			p.x = dist1(gen1);

			std::random_device rd2;
			std::mt19937 gen2(rd2());
			std::uniform_int_distribution<int> dist2(range_min_y, range_max_y);
			p.y = dist2(gen2);

			chickList[count] = new Chick(pGame, p, 50, 50, image_path);
			chickList[count]->draw();
			count++;
		}
	}
}




void CowIcon::onClick(int x, int y)
{
	if (y >= RefPoint.y + height - 15) { // Sell area
		if (count > 0) {
			count--;
			delete CowList[count];
			CowList[count] = nullptr;
			pGame->budget += 100; // Refund $100

			pGame->clearBudget();
			pGame->printBudget("BUDGET = $" + to_string(pGame->budget));
			cout << "Icon Cow Sold" << endl;
		}
	}
	else { // Buy area
		cout << "Icon Cow Clicked" << endl;
		if (count < MAX_ITEMS && pGame->budget >= 100) {
			pGame->budget -= 100;
			pGame->clearBudget();
			pGame->printBudget("BUDGET = $" + to_string(pGame->budget));

			point p;
			std::random_device rd1;
			std::mt19937 gen1(rd1());
			std::uniform_int_distribution<int> dist1(range_min_x, range_max_x);
			p.x = dist1(gen1);

			std::random_device rd2;
			std::mt19937 gen2(rd2());
			std::uniform_int_distribution<int> dist2(range_min_y, range_max_y);
			p.y = dist2(gen2);

			CowList[count] = new Cow(pGame, p, 50, 50, image_path);
			CowList[count]->draw();
			count++;
		}
	}
}



void WaterIcon::onClick(int x, int y)
{
	if (y >= RefPoint.y + height - 15) { // Sell area
		if (count > 0) {
			count--;
			delete Grasslist[count];
			Grasslist[count] = nullptr;
			pGame->budget += 50; // Refund $50 for water

			pGame->clearBudget();
			pGame->printBudget("BUDGET = $" + to_string(pGame->budget));
			cout << "Icon Water Sold" << endl;
		}
	}
	else { // Buy area
		cout << "Icon water Clicked" << endl;
		if (count < MAX_ITEMS && pGame->budget >= 50) { // Assume buying water costs $50
			pGame->budget -= 50;
			pGame->clearBudget();
			pGame->printBudget("BUDGET = $" + to_string(pGame->budget));

			point p;
			std::random_device rd1;
			std::mt19937 gen1(rd1());
			std::uniform_int_distribution<int> dist1(range_min_x, range_max_x);
			p.x = dist1(gen1);

			std::random_device rd2;
			std::mt19937 gen2(rd2());
			std::uniform_int_distribution<int> dist2(range_min_y, range_max_y);
			p.y = dist2(gen2);

			Grasslist[count] = new Grass(pGame, p, 50, 50, image_path,10);
			Grasslist[count]->draw();
			count++;
		}
	}
}


Budgetbar::Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height) : Drawable(r_pGame, r_point, r_width, r_height)
{
	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_CHICK] = "images\\chick.jpg";
	iconsImages[ICON_COW] = "images\\cow.jpg";
	iconsImages[ICON_WATER] = "images\\water.jpg";

	point p;
	p.x = 0;
	p.y = config.toolBarHeight;

	iconsList = new BudgetbarIcon * [ANIMAL_COUNT];

	//For each icon in the tool bar create an object 
	iconsList[ICON_CHICK] = new ChickIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_CHICK]);
	p.x += config.iconWidth;
	iconsList[ICON_COW] = new CowIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_COW]);
	p.x += config.iconWidth;
	iconsList[ICON_WATER] = new WaterIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_WATER]);
	p.x += config.iconWidth;
	//p.x += config.iconWidth;
	//iconsList[ICON_CHICK] = new ChickIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_CHICK]);
	
}

Budgetbar::~Budgetbar()
{
	for (int i = 0; i < ANIMAL_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}

void Budgetbar::draw() const
{
	WaterIcon* pWaterIcon = (WaterIcon*)iconsList[ICON_WATER];
	Grass** grasslist = pWaterIcon->Grasslist;
	for (int i = 0; i < ANIMAL_COUNT; i++) {
	iconsList[i]->moveAllAnimals(grasslist); // when we draw budget bar, which will be in the main game loop, it will move animals
	iconsList[i]->draw();
}
	window* pWind = pGame->getWind();
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, 2*config.toolBarHeight, pWind->GetWidth(), 2*config.toolBarHeight);
}

bool Budgetbar::handleClick(int x, int y)
{
	if (x > ANIMAL_COUNT * config.iconWidth)
		return false;

	int clickedIconIndex = (x / config.iconWidth);

	// Pass the x and y coordinate to the clicked icon to calculate the region
	iconsList[clickedIconIndex]->onClick(x, y);

	return false;
}