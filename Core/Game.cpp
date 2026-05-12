#include "Game.h"
#include "../UI/BudgetBar.h"
#include "../Config/GameConfig.h"
#include "../CMUgraphicsLib/auxil.h"
#include "../Warehouse.h"
#include "../Entities/Animal.h"
#include "../Wolf.h"
#include <iostream>
#include <fstream>
#include "../Grass.h"
#include <random>
using namespace std;

Game::Game()
{
	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	createToolbar();
	createBudgetbar();
	//3 - create and draw the backgroundPlayingArea
	
	for (int i = 0; i < MAX_ITEMS; i++) {
		wolfList[i] = nullptr;
		//omar
		for (int i = 0; i < MAX_ITEMS; i++) {
			wolfList[i] = nullptr;
			chickList[i] = nullptr; 
			cowList[i] = nullptr;   
		}
	}
	
	//4- Create the Plane
	//TODO: Add code to create and draw the Plane


	//5- Create the Bullet
	//TODO: Add code to create and draw the Bullet


	//6- Create the enemies
	//TODO: Add code to create and draw enemies in random places

	// Create the starting point for the warehouse
	point warehousePos;                                                    /// Made the ware house Icon a bit smaller to be fit ( MALEK )
	warehousePos.x = config.windWidth - 130;  // Adjusted X
	warehousePos.y = config.windHeight - 130; // Adjusted Y

	// Instantiate it (Width = 100, Height = 100)
	pWarehouse = new Warehouse(this, warehousePos, 100, 100);

	//7- Create and clear the status bar
	clearStatusBar();
}

Game::~Game()
{
	delete pWind;
	delete gameToolbar;
	delete gameBudgetbar;
	delete pWarehouse;
	for (int i = 0; i < wolfCount; i++) {
		if (wolfList[i] != nullptr) {
			delete wolfList[i];
		}
	}
}

clicktype Game::getMouseClick(int& x, int& y) const //function we put inzide Game, gets where we clicking
{
	return pWind->GetMouseClick(x, y);	//Gets for mouse click and not Wait because this would pause game loop
}

string Game::getSrting() const 
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

void Game::restart() {

	printMessage("Game Restarting...");
	pWind->UpdateBuffer();
	Pause(1200);

	budget = 5000;
	timer = 120;
	goal = 0;
	level = 1;
	animalCount = 0;
	wolfCount = 0;
	eggCount = 0;
	milkcount = 0;
	pWarehouse->resetegg();
	pWarehouse->resetmilk();


	for (int i = 0; i < MAX_ITEMS; i++) {
		if (wolfList[i] != nullptr) {
			delete[] wolfList[i];
			wolfList[i] = nullptr;

		}

		delete gameBudgetbar; // as cows,chicks,and grass are drawn under budget bar
		createBudgetbar();
	}
}



window* Game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}

void Game::createToolbar() 
{
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new Toolbar(this, toolbarUpperleft, 0, config.toolBarHeight);
	gameToolbar->draw();
}

void Game::createBudgetbar()
{
	point budgetbarUpperleft;
	budgetbarUpperleft.x = 0;
	budgetbarUpperleft.y = config.toolBarHeight;

	gameBudgetbar = new Budgetbar(this, budgetbarUpperleft, 0, config.toolBarHeight);
	gameBudgetbar->draw();
}


void Game::clearBudget() const
{
	// Clear Budget bar area using the new Dark Red color
	pWind->SetPen(config.toolBarColor, 1);
	pWind->SetBrush(config.toolBarColor);
	pWind->DrawRectangle(config.windWidth - 500, config.toolBarHeight, config.windWidth, 2 * config.toolBarHeight);
}


void Game::printBudget(string msg) const
{
	clearBudget();

	pWind->SetPen(WHITE, 50); // Changed to WHITE so it pops on the Dark Red background
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.windWidth - 200, config.toolBarHeight + 10, msg);
}

//omar
void Game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

void Game::printMessage(string msg) const
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);

}


void Game::updateStatusBar() const
{
	//Clear the old text
	clearStatusBar();

	
	string statusText = "Timer: " + to_string(timer) +
		"      Goal: " + to_string(goal) +
		"      Level: " + to_string(level) +
		"      Animals: " + to_string(animalCount);

	//Set the font and draw the string
	pWind->SetPen(WHITE, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");

	//Draw it using the exact same coordinates that printMessage uses
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), statusText);
}


bool CollisionDetection(BudgetbarIcon& a1, BudgetbarIcon& a2) {
	int a1x = a1.getRef().x, a1y = a1.getRef().y;
	int a2x = a2.getRef().x, a2y = a2.getRef().y;


	if ((a1x + a1.getWidth() >= a2x) && (a1x <= a2x + a2.getWidth()) && (a1y <= a2y + a2.getHeight()) && (a1y + a1.getHeight() >= a2y)) { return true; cout << "Collision!"; }


	else { return false; }
}

void Game::randomWolf() {
	if (wolfCount < level){ //rolls a number between 1 and 5000 and is true if gets 1
		cout << "Wolf spawned";
		for (int i = 0; i < level; i++) {

		point p;
		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> dist1(range_min_x, range_max_x);
		p.x = dist1(gen1);

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> dist2(range_min_y, range_max_y);
		p.y = dist2(gen2);

		
			wolfList[wolfCount] = new Wolf(this, p, 50, 50, "images\\wolf.jpg");
			wolfList[wolfCount]->draw(); //first the wolf is drawn
			wolfCount++;
		}
			
	}

}



window* Game::getWind() const
{
	return pWind;
}

void Game::go()
{
	//This function reads the position where the user clicks to determine the desired operation
	int x = 0;
	int y = 0;
	bool isExit = false;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy - - - - - - - - - - -");

	pWind->SetBuffering(true); // helps remove the glitching by buffering in another memory

	do
	{

		//////////////////////////////////////// MALEK
		if (!isPaused)//<--Omar
		{
			if (timer > 0)
			{
				if (ElapsedTime(1000)) {
					timer--;
				}
			}
			else
			{
				printMessage("Time's up! GAME OVER. Click anywhere to exit...");

				pWind->UpdateBuffer();
				pWind->FlushMouseQueue();
				int dummyX, dummyY;
				pWind->WaitMouseClick(dummyX, dummyY);

				isExit = true;
				continue;
			}
		}



		//////////////////////////////////////////////////////////////// Updated the colors of the playground and toolbar ( Malek )
		// 1. Draw the Playground Background
		//omar boundaries
		pWind->SetPen(SANDYBROWN, 6);
		pWind->SetBrush(config.bkGrndColor);
		int X1 = 0;
		int Y1 = (config.toolBarHeight * 2) ;
		int X2 = config.windWidth - 13;
		int Y2 = config.windHeight - config.statusBarHeight;

		pWind->DrawRectangle(X1, Y1, X2, Y2);

		////////////////////  ``````` Shazly `````````

		// 2. Draw the Toolbar & BudgetBar Background
		pWind->SetPen(config.toolBarColor, 1);
		pWind->SetBrush(config.toolBarColor);
		pWind->DrawRectangle(0, 0, config.windWidth, 2 * config.toolBarHeight);

		gameToolbar->draw();
		gameBudgetbar->draw();


		Game::randomWolf();
		
		for (int i = 0; i < MAX_ITEMS; i++) {
			if (wolfList[i] != nullptr) {
				if (!isPaused) {   //<--Omar
					wolfList[i]->moveStep();
				}
				wolfList[i]->draw();
			}
		}
		
		


		// ````````````````````

		// --- LEVELING SYSTEM ---                                                          <-- [Leveling Logic + Timer based on level]  ///// MALEK
		// We use "&& level < X" so that if they spend money, they don't lose their level!
		if (budget >= 20000 && level < 4) {
			level = 4;
			timer = 30;  // Reset timer for Level 4
		}
		else if (budget >= 15000 && level < 3) {
			level = 3;
			timer = 60;  // Reset timer for Level 3
		}
		else if (budget >= 10000 && level < 2) {
			level = 2;
			timer = 90;  // Reset timer for Level 2
		}
		// -----------------------


		string budget_string = "MONEY = $" + to_string(budget); // make a string then turn the integer budget into string
		printBudget(budget_string); //How it will be displayed using the printBudget func.
		// ... existing code inside the do-while loop ...
		updateStatusBar();
		pWarehouse->draw();
		//printBudget("BUDGET = $1000"); 
		getMouseClick(x, y);	//Get the coordinates of the user click
		//if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		//{
			//[1] If user clicks on the Toolbar
		if (y >= 0 && y < config.toolBarHeight)
		{
			isExit = gameToolbar->handleClick(x, y);
		}
		else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight) {
			isExit = gameBudgetbar->handleClick(x, y);
		}
		else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight) {
			isExit = gameBudgetbar->handleClick(x, y);
		}
		else if (y >= 2 * config.toolBarHeight && y <= (config.windHeight - config.statusBarHeight)) {//clicked on playing area

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////// [WareHouse pop-up window Logic]
			int wX = pWarehouse->getrefpoint().x;
			int wY = pWarehouse->getrefpoint().y;
			int wW = pWarehouse->getwidth();
			int wH = pWarehouse->getheight();

			if (x >= wX && x < wX + wW && y >= wY && y < wY + wH) {

				/////////////////////////////////////////////////////////////////////// Create a new pop-up window
				window* popup = new window(420, 320, config.wx + 200, config.wy + 150);
				popup->ChangeTitle("Warehouse Inventory");
				popup->SetBuffering(true); // Enables smooth drawing for updating text

				bool closePopup = false;
				while (!closePopup) {
					
					popup->SetBrush(WHITE);
					popup->SetPen(BLACK, 3);
					popup->DrawRectangle(0, 0, 420, 320);

					// text and calculations
					string eggtext = "Eggs: " + to_string(pWarehouse->storedeggs) + "  ($" + to_string(pWarehouse->eggprice) + " each)";
					string milkText = "Milk: " + to_string(pWarehouse->storedmilk) + "  ($" + to_string(pWarehouse->milkprice) + " each)";
					int totalcount = pWarehouse->storedeggs + pWarehouse->storedmilk;
					int totalValue = (pWarehouse->storedeggs * pWarehouse->eggprice) + (pWarehouse->storedmilk * pWarehouse->milkprice);

					string totalText = "Total Items: " + to_string(totalcount);
					string valueText = "Total Value: $" + to_string(totalValue);

					///////////////////////////////////////////////////////////////// Draw products text
					popup->SetPen(BLUE, 50);
					popup->SetFont(22, BOLD, BY_NAME, "Arial");
					popup->DrawString(20, 20, "--- WAREHOUSE INVENTORY ---");	

					popup->SetPen(BLACK, 50);
					popup->SetFont(18, BOLD, BY_NAME, "Arial");
					popup->DrawString(20, 80, eggtext);
					popup->DrawString(20, 120, milkText);
					popup->DrawString(20, 160, totalText);

					popup->SetPen(DARKGREEN, 50);
					popup->DrawString(20, 200, valueText);

					/////////////////////////////////////////////////////////// Drawing sell buttons --------------- [ MALEK ]

					// Sell Egg
					popup->SetBrush(RED);
					popup->SetPen(DARKRED, 2);
					popup->DrawRectangle(280, 75, 380, 105);
					popup->SetPen(WHITE, 50);
					popup->SetFont(16, BOLD, BY_NAME, "Arial");
					popup->DrawString(295, 82, "SELL 1");

					// Sell Milk
					popup->SetBrush(RED);
					popup->SetPen(DARKRED, 2);
					popup->DrawRectangle(280, 115, 380, 145);
					popup->SetPen(WHITE, 50);
					popup->DrawString(295, 122, "SELL 1");

					// Sell ALL Items
					popup->SetBrush(DARKGREEN);
					popup->SetPen(BLACK, 2);
					popup->DrawRectangle(280, 155, 380, 185);
					popup->SetPen(WHITE, 50);
					popup->DrawString(290, 162, "SELL ALL");

					// Close Window
					popup->SetBrush(GRAY);
					popup->SetPen(BLACK, 2);
					popup->DrawRectangle(110, 250, 310, 290);
					popup->SetPen(WHITE, 50);
					popup->SetFont(20, BOLD, BY_NAME, "Arial");
					popup->DrawString(170, 258, "CLOSE");

					
					popup->UpdateBuffer();

					
					int pX, pY;
					popup->WaitMouseClick(pX, pY);

					///////////////////////////////////////////////////////////  Handle the Clicks
					if (pX >= 280 && pX <= 380 && pY >= 75 && pY <= 105) {
						// Egg Clicked
						if (pWarehouse->storedeggs > 0) {
							pWarehouse->storedeggs--;
							budget += pWarehouse->eggprice; // Add money to game budget
						}
					}
					else if (pX >= 280 && pX <= 380 && pY >= 115 && pY <= 145) {
						// Milk Clicked
						if (pWarehouse->storedmilk > 0) {
							pWarehouse->storedmilk--;
							budget += pWarehouse->milkprice; // Add money to game budget
						}
					}
					else if (pX >= 280 && pX <= 380 && pY >= 155 && pY <= 185) {
						// "SELL ALL" Clicked
						budget += totalValue;       // Add total worth to budget
						pWarehouse->resetegg();     // Empty eggs
						pWarehouse->resetmilk();    // Empty milk
					}
					else if (pX >= 110 && pX <= 310 && pY >= 250 && pY <= 290) {
						// "CLOSE" Clicked
						closePopup = true;          // Will break the while loop
					}
				}

				
				delete popup;
			}

			else {
				for (int i = 0; i < eggCount;i++) {
					if (x > eggs[i].x && x<eggs[i].x + 50 && y>eggs[i].y && y < eggs[i].y + 50) {
						eggs[i] = eggs[eggCount - 1];
						eggCount--;
						pWarehouse->addegg();
						break;
					}
				}
				for (int i = 0; i < milkcount;i++) {
					if (x > milks[i].x && x<milks[i].x + 50 && y>milks[i].y && y < milks[i].y + 50) {
						milks[i] = milks[milkcount - 1];
						milkcount--;
						pWarehouse->addmilk();
						break;
					}
				}
			}
		}

		
		Pause(15);

		// SLOW DOWN AND PUSH TO MONITOR ONCE
		Pause(15);
		for (int i = 0; i < eggCount; i++) {
			pWind->DrawImage("images\\egg.jpg", eggs[i].x, eggs[i].y, 50, 50);
		}
		for (int i = 0; i < milkcount; i++) {
			pWind->DrawImage("images\\milk.jpg", milks[i].x, milks[i].y, 50, 50);
		}

		pWind->UpdateBuffer(); // part of the buffer that pushes elements to ur  ``shazly``
	} while (!isExit);
}

void Game::drawfoodarea(int x, int y)const {
		window* pWind = getWind(); //open window
		pWind->DrawImage("images\\grass.jpg", x, y, 50, 50); //draw grass.jpg from images folder, 50x50
	}

void Game::drawegg(int x, int y){
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\egg.jpg", x, y, 50, 50); //draw egg.jpg from images folder, 50x50
	if (eggCount<100){ //store egg positions
		eggs[eggCount].x = x;
		eggs[eggCount].y = y;
		eggCount++;

	}
}
void Game::drawmilk(int x, int y) {
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\milk.jpg", x, y, 50, 50); //draw milk.jpg from images folder, 50x50
	if (milkcount < 100) { //store milk positions
		milks[milkcount].x = x;
		milks[milkcount].y = y;
		milkcount++;
	}
}



///////////////////////////////////////////////////////////////// SAVE and LOAD game progress logic ----------------- [MALEK]




void Game::saveGame() {
	ofstream OutFile("savegame.txt");
	if (!OutFile.is_open()) return;

	// 1. Save basic game stats and Warehouse
	OutFile << budget << " " << timer << " " << level << "\n";
	OutFile << pWarehouse->storedeggs << " " << pWarehouse->storedmilk << "\n";

	// 2. Save Wolves
	OutFile << wolfCount << "\n";
	for (int i = 0; i < wolfCount; i++) {
		OutFile << wolfList[i]->curr_pos.x << " " << wolfList[i]->curr_pos.y << "\n";
	}

	// 3. Save Chicks
	ChickIcon* pChick = (ChickIcon*)gameBudgetbar->iconsList[ICON_CHICK];
	OutFile << pChick->count << "\n";
	for (int i = 0; i < pChick->count; i++) {
		OutFile << pChick->chickList[i]->curr_pos.x << " " << pChick->chickList[i]->curr_pos.y << "\n";
	}

	// 4. Save Cows
	CowIcon* pCow = (CowIcon*)gameBudgetbar->iconsList[ICON_COW];
	OutFile << pCow->count << "\n";
	for (int i = 0; i < pCow->count; i++) {
		OutFile << pCow->CowList[i]->curr_pos.x << " " << pCow->CowList[i]->curr_pos.y << "\n";
	}

	// 5. Save Grass
	WaterIcon* pWater = (WaterIcon*)gameBudgetbar->iconsList[ICON_WATER];
	OutFile << pWater->count << "\n";
	for (int i = 0; i < pWater->count; i++) {
		OutFile << pWater->Grasslist[i]->getrefpoint().x << " " << pWater->Grasslist[i]->getrefpoint().y << " " << pWater->Grasslist[i]->foodcounter << "\n";
	}

	// 6. Save items on the ground
	OutFile << eggCount << "\n";
	for (int i = 0; i < eggCount; i++) OutFile << eggs[i].x << " " << eggs[i].y << "\n";

	OutFile << milkcount << "\n";
	for (int i = 0; i < milkcount; i++) OutFile << milks[i].x << " " << milks[i].y << "\n";

	OutFile.close();
	printMessage("Game Saved Successfully!");
}

void Game::loadGame() {
	ifstream InFile("savegame.txt");
	if (!InFile.is_open()) {
		printMessage("No save file found!");
		return;
	}

	// 1. CLEAR CURRENT GAME STATE BEFORE LOADING
	for (int i = 0; i < wolfCount; i++) if (wolfList[i]) delete wolfList[i];

	ChickIcon* pChick = (ChickIcon*)gameBudgetbar->iconsList[ICON_CHICK];
	for (int i = 0; i < pChick->count; i++) if (pChick->chickList[i]) delete pChick->chickList[i];

	CowIcon* pCow = (CowIcon*)gameBudgetbar->iconsList[ICON_COW];
	for (int i = 0; i < pCow->count; i++) if (pCow->CowList[i]) delete pCow->CowList[i];

	WaterIcon* pWater = (WaterIcon*)gameBudgetbar->iconsList[ICON_WATER];
	for (int i = 0; i < pWater->count; i++) if (pWater->Grasslist[i]) delete pWater->Grasslist[i];

	// 2. LOAD DATA BACK IN
	InFile >> budget >> timer >> level;
	InFile >> pWarehouse->storedeggs >> pWarehouse->storedmilk;

	InFile >> wolfCount;
	for (int i = 0; i < wolfCount; i++) {
		point p; InFile >> p.x >> p.y;
		wolfList[i] = new Wolf(this, p, 50, 50, "images\\wolf.jpg");
	}

	InFile >> pChick->count;
	for (int i = 0; i < pChick->count; i++) {
		point p; InFile >> p.x >> p.y;
		pChick->chickList[i] = new Chick(this, p, 50, 50, pChick->image_path);
	}

	InFile >> pCow->count;
	for (int i = 0; i < pCow->count; i++) {
		point p; InFile >> p.x >> p.y;
		pCow->CowList[i] = new Cow(this, p, 50, 50, pCow->image_path);
	}

	InFile >> pWater->count;
	for (int i = 0; i < pWater->count; i++) {
		point p; int fc; InFile >> p.x >> p.y >> fc;
		pWater->Grasslist[i] = new Grass(this, p, 50, 50, pWater->image_path, fc);
	}

	InFile >> eggCount;
	for (int i = 0; i < eggCount; i++) InFile >> eggs[i].x >> eggs[i].y;

	InFile >> milkcount;
	for (int i = 0; i < milkcount; i++) InFile >> milks[i].x >> milks[i].y;

	InFile.close();

	// 3. Update the visual budget text
	clearBudget();
	printBudget("MONEY = $" + to_string(budget));
	printMessage("Game Loaded Successfully!");
}