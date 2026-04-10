#include "Game.h"
#include "../Config/GameConfig.h"

Game::Game()
{
	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	createToolbar();
	createBudgetbar();
	//3 - create and draw the backgroundPlayingArea
	
	
	//4- Create the Plane
	//TODO: Add code to create and draw the Plane


	//5- Create the Bullet
	//TODO: Add code to create and draw the Bullet


	//6- Create the enemies
	//TODO: Add code to create and draw enemies in random places



	//7- Create and clear the status bar
	clearStatusBar();
}

Game::~Game()
{
}

clicktype Game::getMouseClick(int& x, int& y) const //function we put inzide Game, gets where we clicking
{
	return pWind->WaitMouseClick(x, y);	//Waits for mouse click

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


window* Game::getWind() const
{
	return pWind;
}

void Game::go() const
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy - - - - - - - - - - -");

	do
	{
		printMessage("Ready...");
		string budget_string = "MONEY = $" + to_string(budget); // make a string then turn the integer budget into string
		printBudget(budget_string); //How it will be displayed using the printBudget func.
		// ... existing code inside the do-while loop ...
		updateStatusBar();

		drawfoodarea(500, 300);
		// ...
		drawfoodarea(500, 300);
		drawegg(300, 400);
		drawmilk(200, 300);
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
		//}

	} while (!isExit);
}
void Game::drawfoodarea(int x, int y)const {
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\grass.jpg", x, y, 50, 50); //draw grass.jpg from images folder, 50x50
}

void Game::drawegg(int x, int y)const {
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\egg.jpg", x, y, 50, 50); //draw egg.jpg from images folder, 50x50
}
void Game::drawmilk(int x, int y)const {
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\milk.jpg", x, y, 50, 50); //draw milk.jpg from images folder, 50x50
}
