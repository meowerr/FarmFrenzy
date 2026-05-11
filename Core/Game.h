#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
#include "../Entities/Animal.h"
class Warehouse;
class Wolf;
class Game
{
private:
	window* pWind;	//Pointer to the CMU graphics window
	Toolbar* gameToolbar ; // this is how we call our toolbar from now on 
	Budgetbar* gameBudgetbar;



public:

	// --- NEW FEATURE VARIABLES ---                        //// MALEK
	string playerName;
	int maxScore = 5000; // Initialize to initial budget
	void promptForNickname();


	//omar 
	bool isPaused = false;
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
	void randomWolf(); ////////////////Shazly
	void createBudgetbar();
	void clearBudget() const;
	void printBudget(string msg) const;
	void clearStatusBar() const;	//Clears the status bar
	bool CollisionDetection(BudgetbarIcon& a1, BudgetbarIcon& a2);

	void printMessage(string msg) const;	//Print a message on Status bar
	void restart();
	void go();

	/////////////////////   Saving and Loading Progress Declaration ----- [MALEK]

	void saveGame();  
	void loadGame();  

	window* getWind() const;		//returns a pointer to the graphics window

	void drawfoodarea(int x, int y)const; //define function to draw food area
	void drawegg(int x, int y);  //define function to draw egg
	void drawmilk(int x, int y);  //define function to draw milk

	Wolf* wolfList[MAX_ITEMS];
	int wolfCount = 0;
	//omar
	Chick* chickList[MAX_ITEMS];
	Cow* cowList[MAX_ITEMS];
	

	point eggs[100]; // Array to store egg positions
	int eggCount = 0;
	point milks[100];
	int milkcount = 0;

};

