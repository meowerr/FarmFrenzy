#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
class Warehouse;
class Game
{
private:
	window* pWind;	//Pointer to the CMU graphics window
	Toolbar* gameToolbar; // this is how we call our toolbar from now on 
	Budgetbar* gameBudgetbar;

public:
	int budget = 5000;
	int timer = 120;
	int goal = 0;
	int level = 1;
	int animalCount = 0;
	Warehouse* pWarehouse;
	void updateStatusBar() const;
	Game();
	~Game();

	clicktype getMouseClick(int& x, int& y) const; //Get coordinate where user clicks and returns click type (left/right click)
	string getSrting() const;	 //Returns a string entered by the user	 

	
	window* CreateWind(int, int, int, int) const; //creates the game window
	void createToolbar();
	
	void createBudgetbar();
	void clearBudget() const;
	void printBudget(string msg) const;
	void clearStatusBar() const;	//Clears the status bar


	void printMessage(string msg) const;	//Print a message on Status bar

	void go();

	window* getWind() const;		//returns a pointer to the graphics window

	void drawfoodarea(int x, int y)const; //define function to draw food area
	void drawegg(int x, int y)const;  //define function to draw egg
	void drawmilk(int x, int y)const;  //define function to draw milk
};

