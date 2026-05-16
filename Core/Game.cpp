#include "Game.h"
#include "../UI/BudgetBar.h"
#include "../Config/GameConfig.h"
#include "../CMUgraphicsLib/auxil.h"
#include "../Warehouse.h"
#include "../Entities/Animal.h"
#include "../SoundEffects.h"
#include "../Wolf.h"
#include <iostream>
#include <fstream>
#include "../Grass.h"
#include <random>
using namespace std;

soundPlayer mains;

struct PlayerScore{
	string name;
	int score;

};


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
			chickList[i] = nullptr;
			cowList[i] = nullptr;
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

	BoughtCage = false;

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
	timer = 90;
	goal = 10000;
	level = 1;
	animalCount = 0;
	wolfCount = 0;
	eggCount = 0;
	milkcount = 0;
	pWarehouse->resetegg();
	pWarehouse->resetmilk();


	for (int i = 0; i < MAX_ITEMS; i++) {
		if (wolfList[i] != nullptr) {
			delete wolfList[i];
			wolfList[i] = nullptr;

		}
	}
	delete gameBudgetbar; // as cows,chicks,and grass are drawn under budget bar
	createBudgetbar();
	randomWolf();
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


void Game::randomWolf() {
	if (wolfCount < level) { 
		mains.playswolf();
		cout << "Wolf spawned\n";
		for (int i = 0; i < level; i++) {

			point p;
			std::random_device rd1;
			static std::mt19937 gen1(rd1());
			std::uniform_int_distribution<int> dist1(range_min_x, range_max_x);
			p.x = dist1(gen1);

			std::random_device rd2;
			static std::mt19937 gen2(rd2());
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


	Wolf* draggedWolf = nullptr; ///////////////// detecting if the wolf currently being held by user     ----- malek



	if (bgmusic.openFromFile("track.wav")) {
		bgmusic.setLoop(true);
		bgmusic.setVolume(20);
		//bgmusic.play();
		
	}


	do
	{
		
		if (!isPaused) { 
			if (bgmusic.getStatus() != sf::Music::Playing) {
				bgmusic.play();
		}
		}
		else bgmusic.pause();
		





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



		//////////// Updated the colors of the playground and toolbar ( Malek )
		// 1. Draw the Playground Background
		//omar boundaries
		pWind->SetPen(SANDYBROWN, 6);
		pWind->SetBrush(config.bkGrndColor);
		int X1 = 0;
		int Y1 = (config.toolBarHeight * 2);
		int X2 = config.windWidth - 13;
		int Y2 = config.windHeight - config.statusBarHeight;

		pWind->DrawRectangle(X1, Y1, X2, Y2);

		//omar
		//draw cage top right
		int cageX1 = config.windWidth - 120;
		int cageX2 = config.windWidth - 20;
		if (BoughtCage) {
			pWind->SetPen(BLACK, 5);
			pWind->SetBrush(GRAY);

			pWind->DrawRectangle(cageX1, 110, cageX2, 210);

			pWind->SetPen(WHITE, 2);
			pWind->SetFont(20, BOLD, BY_NAME, "Arial");
			pWind->DrawString(cageX1 + 25, 150, "CAGE");
		}
		else {
			pWind->SetPen(RED, 3);
			pWind->SetBrush(config.bkGrndColor); // matches playground background
			pWind->DrawRectangle(cageX1, 110, cageX2, 210);

			pWind->SetPen(RED, 2);
			pWind->SetFont(12, BOLD, BY_NAME, "Arial");
			pWind->DrawString(cageX1 + 10, 140, "UNLOCK CAGE");
			pWind->DrawString(cageX1 + 25, 165, "$8000");
		}
		////////////////////  ``````` Shazly `````````

		// 2. Draw the Toolbar & BudgetBar Background
		pWind->SetPen(config.toolBarColor, 1);
		pWind->SetBrush(config.toolBarColor);
		pWind->DrawRectangle(0, 0, config.windWidth, 2 * config.toolBarHeight);

		gameToolbar->draw();
		gameBudgetbar->draw();





		Game::randomWolf();

		for (int i = 0; i < wolfCount; i++) {
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
		if (budget >= 50000 && level < 5) {
			printMessage("Level UP!!");
			mains.playslvlUP();
			pWind->UpdateBuffer();
			Pause(500);
			level = 5;
			timer = 20;  // Reset timer for Level 5
		}
		else if (budget >= 20000 && level < 4) {
			printMessage("Level UP!!");
			mains.playslvlUP();
			pWind->UpdateBuffer();
			Pause(500);
			goal = 50000;
			level = 4;
			timer = 30;  // Reset timer for Level 4
		}
		else if (budget >= 15000 && level < 3) {
			printMessage("Level UP!!");
			mains.playslvlUP();
			pWind->UpdateBuffer();
			Pause(500);
			level = 3;
			goal = 20000;
			timer = 60;  // Reset timer for Level 3
		}
		else if (budget >= 10000 && level < 2) {
			printMessage("Level UP!!");
			mains.playslvlUP();
			pWind->UpdateBuffer();
			Pause(500);
			level = 2;
			goal = 15000;
			timer = 90;  // Reset timer for Level 2
		}
		// -----------------------


		string budget_string = "MONEY = $" + to_string(budget); // make a string then turn the integer budget into string
		printBudget(budget_string); //How it will be displayed using the printBudget func.
		// ... existing code inside the do-while loop ...
		updateStatusBar();
		pWarehouse->draw();
		//printBudget("BUDGET = $1000"); 


		//////////////////////////////////////////////////////////////////////////// DRAG AND DROP WOLF LOGIC    ------ malek

		int mx, my;
		buttonstate leftState = pWind->GetButtonState(LEFT_BUTTON, mx, my);

		if (leftState == BUTTON_DOWN) {
			//omar
			// purchasing logic
			if (!BoughtCage) {
				int cageX1 = config.windWidth - 120;
				int cageX2 = config.windWidth - 20;

				// Did user click inside the locked cage area?
				if (mx >= cageX1 && mx <= cageX2 && my >= 110 && my <= 210) {
					if (budget >= 8000) {
						budget -= 8000;
						BoughtCage = true;
					
						printMessage("Cage unlocked! Drag and drop wolves here to trap them.");
				
					}
					else {
						printMessage("Insufficient funds! You need $8000 to unlock the cage.");
					}
				}
			}
			// If we aren't holding a wolf yet, check if we grabbed one
			if (draggedWolf == nullptr) {
				// Check from the newest wolf to the oldest
				for (int i = wolfCount - 1; i >= 0; i--) {
					if (wolfList[i] != nullptr) {
						int wx = wolfList[i]->getrefpoint().x;
						int wy = wolfList[i]->getrefpoint().y;
						int ww = wolfList[i]->getwidth();
						int wh = wolfList[i]->getheight();

						if (mx >= wx && mx <= wx + ww && my >= wy && my <= wy + wh) {
							draggedWolf = wolfList[i];
							draggedWolf->isDragged = true;

							break; // Grabbed one! Stop checking.
						}
					}
				}
			}

			// If we are actively holding a wolf, move it to the mouse!
			if (draggedWolf != nullptr) {
				int nx = mx - draggedWolf->getwidth() / 2;
				int ny = my - draggedWolf->getheight() / 2;

				// Keep the wolf strictly inside the grass/playing area!
				if (nx < range_min_x) nx = range_min_x;
				if (nx > range_max_x) nx = range_max_x;
				if (ny < range_min_y) ny = range_min_y;
				if (ny > range_max_y) ny = range_max_y;

				draggedWolf->setLocation(nx, ny);
			}
		}
		else { // BUTTON_UP (Mouse Released)
			if (draggedWolf != nullptr) {
				// omar's trap logic
				int cageX1 = config.windWidth - 120;
				int cageX2 = config.windWidth - 20;

				// Did the player drop the wolf inside the new grey box , and the cage is purchased?
				if (mx >= cageX1 && mx <= cageX2 && my >= 110 && my <= 210 && BoughtCage) {
					draggedWolf->isCaged = true; //traps it
					draggedWolf->setLocation(cageX1 + 25, 135); // sets wolf to center
				}
				// ----------------------
				draggedWolf->isDragged = false; // Resume random movement
				draggedWolf = nullptr;
				pWind->FlushMouseQueue(); // Clear the drop click so we don't accidentally click UI buttons!
				x = -1; y = -1; // Reset coords just in case
			}
		}
		// ---------------------------------



		getMouseClick(x, y);	//Get the coordinates of the user click


		//if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		//{
			//[1] If user clicks on the Toolbar

		if (draggedWolf == nullptr) /////////////////////////////////// Only process clicks if NOT holding a wolf  ----- malek
		{
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit = gameToolbar->handleClick(x, y);
			}
			else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight) {
				isExit = gameBudgetbar->handleClick(x, y);
			}
			else if (y >= 2 * config.toolBarHeight && y <= (config.windHeight - config.statusBarHeight)) {//clicked on playing area

				bool clickedwolf = false;
				for (int i = 0; i < wolfCount; i++) {
					if (wolfList[i] != nullptr) {
						int wolfx = wolfList[i]->getrefpoint().x;
						int wolfy = wolfList[i]->getrefpoint().y;
						int wolfw = wolfList[i]->getwidth();
						int wolfh = wolfList[i]->getheight();

						if (x >= wolfx && x < wolfx + wolfw && y >= wolfy && y <= wolfy + wolfh) {
							if (wolfList[i]->handleClick(x, y)) {
								delete wolfList[i];
								wolfList[i] = nullptr;
								wolfCount--;
							}
							clickedwolf = true;
							break;

						}
					}
				}


				///////////////////////////////////////////////////////////////////////////////////////////////////////////////// [WareHouse pop-up window Logic]
				int wX = pWarehouse->getrefpoint().x;
				int wY = pWarehouse->getrefpoint().y;
				int wW = pWarehouse->getwidth();
				int wH = pWarehouse->getheight();
				if (!clickedwolf) {
					if (x >= wX && x < wX + wW && y >= wY && y < wY + wH) {

						/////////////////////////////////////////////////////////////////////// new popup window
						window* popup = new window(420, 320, config.wx + 200, config.wy + 150);
						mains.playsclick();
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
								mains.playsclick();
								if (pWarehouse->storedeggs > 0) {
									pWarehouse->storedeggs--;
									budget += pWarehouse->eggprice; // Add money to game budget
								}
							}
							else if (pX >= 280 && pX <= 380 && pY >= 115 && pY <= 145) {
								// Milk Clicked
								mains.playsclick();
								if (pWarehouse->storedmilk > 0) {
									pWarehouse->storedmilk--;
									budget += pWarehouse->milkprice; // Add money to game budget
								}
							}
							else if (pX >= 280 && pX <= 380 && pY >= 155 && pY <= 185) {
								// "SELL ALL" Clicked
								mains.playsclick();
								budget += totalValue;       // Add total worth to budget
								pWarehouse->resetegg();     // Empty eggs
								pWarehouse->resetmilk();    // Empty milk
							}
							else if (pX >= 110 && pX <= 310 && pY >= 250 && pY <= 290) {
								// "CLOSE" Clicked
								mains.playsclick();
								closePopup = true;          // Will break the while loop
							}
						}


						delete popup;
						popup = nullptr;
					}

					else {
						for (int i = 0; i < eggCount; i++) {
							if (x > eggs[i].x && x<eggs[i].x + 50 && y>eggs[i].y && y < eggs[i].y + 50) {
								eggs[i] = eggs[eggCount - 1];
								eggCount--;
								pWarehouse->addegg();
								break;
							}
						}
						for (int i = 0; i < milkcount; i++) {
							if (x > milks[i].x && x<milks[i].x + 50 && y>milks[i].y && y < milks[i].y + 50) {
								milks[i] = milks[milkcount - 1];
								milkcount--;
								pWarehouse->addmilk();
								break;
							}
						}
					}
				}
			}
		}

	


		
		for (int i = 0; i < eggCount; i++) {
			
			pWind->DrawImage("images\\egg.jpg", eggs[i].x, eggs[i].y, 50, 50);
		}
		
		for (int i = 0; i < milkcount; i++) {
			
			pWind->DrawImage("images\\milk.jpg", milks[i].x, milks[i].y, 50, 50);
		}

		// omar's GAME OVER and leaderboard when timer hits zero
		// --- GAME OVER & LEADERBOARD CHECK ---
		if (timer <= 0)
		{
			isPaused = true;

			// 1. Draw the Game Over text
			pWind->SetPen(RED, 1);
			pWind->SetFont(60, BOLD, BY_NAME, "Arial");
			pWind->DrawString((config.windWidth / 2) - 150, 100, "GAME OVER");
			pWind->UpdateBuffer();

			int finalScore = budget;

			// 2. Ask for name inside the game window
			pWind->SetPen(YELLOW, 3);
			pWind->SetFont(30, BOLD, BY_NAME, "Arial");

			string promptText = "You scored $" + to_string(finalScore) + "! Type your name:";
			pWind->DrawString((config.windWidth / 2) - 200, 180, promptText);
			pWind->UpdateBuffer();

			// Capture keyboard input using your Game class's string function
			string playerName = getSrting();
			clearStatusBar();
			// 3. Save to the permanent text file (Force creation & bypass OneDrive lock)
			ofstream outFile;
			outFile.open("FarmScores.txt", ios::out | ios::app);
			if (outFile.is_open()) {
				outFile << playerName << " " << finalScore << endl;
				outFile.close();
			}

			// 4. Load the file into a STANDARD ARRAY
			ifstream inFile;
			inFile.open("FarmScores.txt");
			PlayerScore board[100];
			int playerCount = 0;

			// Only try to read if the file successfully unlocked!
			if (inFile.is_open()) {
				string n;
				int s;
				while (inFile >> n >> s && playerCount < 100) {
					board[playerCount].name = n;
					board[playerCount].score = s;
					playerCount++;
				}
				inFile.close();
			}

			// --- LEADERBOARD FAILSAFE ---
			if (playerCount == 0 && playerName != "") {
				board[0].name = playerName;
				board[0].score = finalScore;
				playerCount = 1;
			}			// 5. MANUAL BUBBLE SORT (Highest to Lowest)
			for (int i = 0; i < playerCount - 1; i++) {
				for (int j = 0; j < playerCount - i - 1; j++) {
					if (board[j].score < board[j + 1].score) {
						// Swap the two players if the lower one has a higher score
						PlayerScore temp = board[j];
						board[j] = board[j + 1];
						board[j + 1] = temp;
					}
				}
			}

			// 6. Draw the Leaderboard UI Box
			pWind->SetBrush(WHITE);
			pWind->SetPen(BLACK, 3);
			pWind->DrawRectangle(200, 200, 600, 500);

			pWind->SetFont(40, BOLD, BY_NAME, "Arial");
			pWind->DrawString(220, 210, "--- TOP FARMERS ---");

			// 7. Draw the Top 5 Players
			pWind->SetFont(30, PLAIN, BY_NAME, "Arial");
			int drawY = 270;

			// Loop up to 5 times, or the total number of players if less than 5
			int displayLimit = (playerCount < 5) ? playerCount : 5;
			for (int i = 0; i < displayLimit; i++) {
				string entry = to_string(i + 1) + ". " + board[i].name + " - $" + to_string(board[i].score);
				pWind->DrawString(230, drawY, entry);
				drawY += 40;
			}

			pWind->UpdateBuffer();

			int clickX, clickY;
			pWind->WaitMouseClick(clickX, clickY);
			isExit = true;
		}
		pWind->UpdateBuffer();
		Pause(15);
	} while (!isExit);
}

void Game::drawfoodarea(int x, int y)const {
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\grass.jpg", x, y, 50, 50); //draw grass.jpg from images folder, 50x50
}

void Game::drawegg(int x, int y) {
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\egg.jpg", x, y, 50, 50); //draw egg.jpg from images folder, 50x50
	if (eggCount < 100) { //store egg positions
		eggs[eggCount].x = x;
		eggs[eggCount].y = y;
		eggCount++;
		mains.playsdrop();

	}
}
void Game::drawmilk(int x, int y) {
	window* pWind = getWind(); //open window
	pWind->DrawImage("images\\milk.jpg", x, y, 50, 50); //draw milk.jpg from images folder, 50x50
	if (milkcount < 100) { //store milk positions
		milks[milkcount].x = x;
		milks[milkcount].y = y;
		milkcount++;
		mains.playsdrop();
	}
}



///////////////////////////////////////////////////////////////// SAVE and LOAD game progress logic ----------------- [MALEK]




void Game::saveGame() {
	ofstream OutFile("savegame.txt");
	if (!OutFile.is_open()) return;

	// 1. Save basic game stats
	OutFile << "===_Game_Status_===\n";
	OutFile << "Budget: " << budget << "\n";
	OutFile << "Timer: " << timer << "\n";
	OutFile << "Level: " << level << "\n\n";

	// 2. Save Warehouse
	OutFile << "===_Warehouse_Data_===\n";
	OutFile << "Stored_Eggs: " << pWarehouse->storedeggs << "\n";
	OutFile << "Stored_Milk: " << pWarehouse->storedmilk << "\n\n";

	// 3. Save Wolves
	OutFile << "===_Wolves_Data_===\n";
	OutFile << "Wolves_Count: " << wolfCount << "\n";
	for (int i = 0; i < wolfCount; i++) {
		OutFile << "Wolf_" << i + 1 << "_Pos: " << wolfList[i]->curr_pos.x << " " << wolfList[i]->curr_pos.y << "\n";
	}
	OutFile << "\n";

	// 4. Save Chicks
	OutFile << "===_Chicks_Data_===\n";
	ChickIcon* pChick = (ChickIcon*)gameBudgetbar->iconsList[ICON_CHICK];
	OutFile << "Chicks_Count: " << pChick->count << "\n";
	for (int i = 0; i < pChick->count; i++) {
		OutFile << "Chick_" << i + 1 << "_Pos: " << pChick->chickList[i]->curr_pos.x << " " << pChick->chickList[i]->curr_pos.y << "\n";
	}
	OutFile << "\n";

	// 5. Save Cows
	OutFile << "===_Cows_Data_===\n";
	CowIcon* pCow = (CowIcon*)gameBudgetbar->iconsList[ICON_COW];
	OutFile << "Cows_Count: " << pCow->count << "\n";
	for (int i = 0; i < pCow->count; i++) {
		OutFile << "Cow_" << i + 1 << "_Pos: " << pCow->CowList[i]->curr_pos.x << " " << pCow->CowList[i]->curr_pos.y << "\n";
	}
	OutFile << "\n";

	// 6. Save Grass
	OutFile << "===_Grass_Data_===\n";
	WaterIcon* pWater = (WaterIcon*)gameBudgetbar->iconsList[ICON_WATER];
	OutFile << "Grass_Count: " << pWater->count << "\n";
	for (int i = 0; i < pWater->count; i++) {
		OutFile << "Grass_" << i + 1 << "_Pos_&_Food: " << pWater->Grasslist[i]->getrefpoint().x << " " << pWater->Grasslist[i]->getrefpoint().y << " " << pWater->Grasslist[i]->foodcounter << "\n";
	}
	OutFile << "\n";

	// 7. Save items on the ground
	OutFile << "===_Ground_Eggs_Data_===\n";
	OutFile << "Eggs_Count: " << eggCount << "\n";
	for (int i = 0; i < eggCount; i++) {
		OutFile << "Egg_" << i + 1 << "_Pos: " << eggs[i].x << " " << eggs[i].y << "\n";
	}
	OutFile << "\n";

	OutFile << "===_Ground_Milk_Data_===\n";
	OutFile << "Milk_Count: " << milkcount << "\n";
	for (int i = 0; i < milkcount; i++) {
		OutFile << "Milk_" << i + 1 << "_Pos: " << milks[i].x << " " << milks[i].y << "\n";
	}
	OutFile << "\n";

	OutFile.close();
	printMessage("Game Saved Successfully!");
}



void Game::loadGame() {
	ifstream InFile("savegame.txt");
	if (!InFile.is_open()) {
		printMessage("No save file found!");
		return;
	}

	string label; // Dummy string used to "absorb" the text labels from the file

	// 1. CLEAR CURRENT GAME STATE BEFORE LOADING
	for (int i = 0; i < wolfCount; i++) {
		if (wolfList[i]) { delete wolfList[i]; wolfList[i] = nullptr; }
	}
	wolfCount = 0;

	ChickIcon* pChick = (ChickIcon*)gameBudgetbar->iconsList[ICON_CHICK];
	for (int i = 0; i < pChick->count; i++) {
		if (pChick->chickList[i]) { delete pChick->chickList[i]; pChick->chickList[i] = nullptr; }
	}
	pChick->count = 0;

	CowIcon* pCow = (CowIcon*)gameBudgetbar->iconsList[ICON_COW];
	for (int i = 0; i < pCow->count; i++) {
		if (pCow->CowList[i]) { delete pCow->CowList[i]; pCow->CowList[i] = nullptr; }
	}
	pCow->count = 0;

	WaterIcon* pWater = (WaterIcon*)gameBudgetbar->iconsList[ICON_WATER];
	for (int i = 0; i < pWater->count; i++) {
		if (pWater->Grasslist[i]) { delete pWater->Grasslist[i]; pWater->Grasslist[i] = nullptr; }
	}
	pWater->count = 0;

	// 2. LOAD DATA BACK IN

	// Status
	InFile >> label; // reads "===_Game_Status_==="
	InFile >> label >> budget; // reads "Budget:" then the number
	InFile >> label >> timer;
	InFile >> label >> level;

	// Warehouse
	InFile >> label; // reads "===_Warehouse_Data_==="
	InFile >> label >> pWarehouse->storedeggs;
	InFile >> label >> pWarehouse->storedmilk;

	// Wolves
	InFile >> label; // reads "===_Wolves_Data_==="
	InFile >> label >> wolfCount;
	for (int i = 0; i < wolfCount; i++) {
		point p;
		InFile >> label >> p.x >> p.y; // reads "Wolf_X_Pos:", X, Y
		wolfList[i] = new Wolf(this, p, 50, 50, "images\\wolf.jpg");
	}

	// Chicks
	InFile >> label; // reads "===_Chicks_Data_==="
	InFile >> label >> pChick->count;
	for (int i = 0; i < pChick->count; i++) {
		point p;
		InFile >> label >> p.x >> p.y;
		pChick->chickList[i] = new Chick(this, p, 50, 50, pChick->image_path);
	}

	// Cows
	InFile >> label; // reads "===_Cows_Data_==="
	InFile >> label >> pCow->count;
	for (int i = 0; i < pCow->count; i++) {
		point p;
		InFile >> label >> p.x >> p.y;
		pCow->CowList[i] = new Cow(this, p, 50, 50, pCow->image_path);
	}

	// Grass
	InFile >> label; // reads "===_Grass_Data_==="
	InFile >> label >> pWater->count;
	for (int i = 0; i < pWater->count; i++) {
		point p; int fc;
		InFile >> label >> p.x >> p.y >> fc;
		pWater->Grasslist[i] = new Grass(this, p, 50, 50, pWater->image_path, fc);
	}

	// Eggs on Ground
	InFile >> label; // reads "===_Ground_Eggs_Data_==="
	InFile >> label >> eggCount;
	for (int i = 0; i < eggCount; i++) {
		InFile >> label >> eggs[i].x >> eggs[i].y;
	}

	// Milk on Ground
	InFile >> label; // reads "===_Ground_Milk_Data_==="
	InFile >> label >> milkcount;
	for (int i = 0; i < milkcount; i++) {
		InFile >> label >> milks[i].x >> milks[i].y;
	}

	InFile.close();

	// 3. 
	// visuals
	clearBudget();
	printBudget("MONEY = $" + to_string(budget));
	printMessage("Game Loaded Successfully!");
}