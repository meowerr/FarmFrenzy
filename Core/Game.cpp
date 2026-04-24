#include "Game.h"
#include "../UI/BudgetBar.h"
#include "../Config/GameConfig.h"
#include "../CMUgraphicsLib/auxil.h"
#include "../Warehouse.h"
#include "../Entities/Animal.h"
#include "../Wolf.h"
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
	}
	
	//4- Create the Plane
	//TODO: Add code to create and draw the Plane


	//5- Create the Bullet
	//TODO: Add code to create and draw the Bullet


	//6- Create the enemies
	//TODO: Add code to create and draw enemies in random places

	// Create the starting point for the warehouse
	point warehousePos;
	warehousePos.x = config.windWidth - 200;  // 200 pixels away from the right wall
	warehousePos.y = config.windHeight - 220; // Above the status bar

	// Instantiate it (Width = 150, Height = 150)
	pWarehouse = new Warehouse(this, warehousePos, 150, 150);

	//7- Create and clear the status bar
	clearStatusBar();
}

Game::~Game()
{
}

clicktype Game::getMouseClick(int& x, int& y) const //function we put inzide Game, gets where we clicking
{
	return pWind->GetMouseClick(x, y);	//Waits for mouse click

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
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(config.windWidth - 500, config.toolBarHeight, config.windWidth, 2*config.toolBarHeight);
}

void Game::printBudget(string msg) const
{
	clearBudget();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.windWidth-200, config.toolBarHeight + 10, msg);

}

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
	// Clear the old text
	clearStatusBar();

	// Combine the four variables into one formatted string
	string statusText = "Timer: " + to_string(timer) +
		"      Goal: " + to_string(goal) +
		"      Level: " + to_string(level) +
		"      Animals: " + to_string(animalCount);

	// Set the font and draw the string
	pWind->SetPen(WHITE, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");

	// Draw it using the exact same coordinates that printMessage uses
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), statusText);
}


void Game::randomWolf() {
	if (rand() % 100 + 1 == 1){ //rolls a number between 1 and 100 and is true if gets 1
	if (level > 1) {
	//	cout << "Wolf spawned";
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
		wolfList[wolfCount]->draw();
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
	int x, y;
	bool isExit = false;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy - - - - - - - - - - -");
	
	pWind->SetBuffering(true); // helps remove the glitching by buffering in another memory

	do
	{

		//////////////////////////////////////// MALEK

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





		// ``````Shazly ``````
		
		pWind->SetPen(config.bkGrndColor, 1); // set pen color and thickness
		pWind->SetBrush(config.bkGrndColor); // set brush color
		pWind->DrawRectangle(0, 0, config.windWidth, config.windHeight - config.statusBarHeight); // keep drawing the blue area over and over
		gameToolbar->draw(); // Keep drawing the toolbar constantly
		gameBudgetbar->draw(); // same thing


		Game::randomWolf();
			for (int i = 0; i < MAX_ITEMS; i++) {
			if (wolfList[i] != nullptr) {
				wolfList[i]->moveStep();
				wolfList[i]->draw();
			}
		}



		// ````````````````````
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
		else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight)
		{
			isExit = gameBudgetbar->handleClick(x, y);
		}



		Pause(15);
		//////////////////////////saqib/////////// redraw all milk and egg
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
