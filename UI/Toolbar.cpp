#include "Toolbar.h"
#include "../Config/GameConfig.h"
#include "../SoundEffects.h"
#include "../Core/Game.h"

soundPlayer toolbarsf;
ToolbarIcon::ToolbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
}

void ToolbarIcon::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

RestartIcon::RestartIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{}

void RestartIcon::onClick()
{
	toolbarsf.playsclick();
	pGame->restart();
}

ExitIcon::ExitIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{}

void ExitIcon::onClick()
{
	//TO DO: add code for cleanup and game exit here
}
//Pause Icon
PauseIcon::PauseIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void PauseIcon::onClick()
{
	//omar
	toolbarsf.playsclick();
	pGame->isPaused = true;
	
}

// Resume Icon
ResumeIcon::ResumeIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void ResumeIcon::onClick()
{
	//omar
	toolbarsf.playsclick();
	pGame->isPaused = false;
}

// Save Icon
SaveIcon::SaveIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void SaveIcon::onClick()
{
	toolbarsf.playsclick();
	pGame->saveGame();  //////// call the saving function               [MALEK]
}

// Load Icon
LoadIcon1::LoadIcon1(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : ToolbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}
void LoadIcon1::onClick()
{
	toolbarsf.playsclick();
	pGame->loadGame();   //////// call the loading function               [MALEK]

}
Toolbar::Toolbar(Game* r_pGame, point r_point, int r_width, int r_height) : Drawable(r_pGame, r_point, r_width, r_height)
{
	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
// 1. Prepare the list of images
	iconsImages[ICON_RESTART] = "images\\newrestarting.jpg";
	iconsImages[ICON_PAUSE] = "images\\newpause.jpg";
	iconsImages[ICON_RESUME] = "images\\newcontinue.jpg";
	iconsImages[ICON_SAVE] = "images\\newsave.jpg";
	iconsImages[ICON_LOAD] = "images\\newloading.jpg";
	iconsImages[ICON_EXIT] = "images\\newexit.jpg";

	iconsList = new ToolbarIcon * [ICON_COUNT];

	// 2. Create the objects side-by-side

	point p;
	p.x = 0;
	p.y = 0;

	iconsList[ICON_RESTART] = new RestartIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_RESTART]);
	p.x += config.iconWidth;

	iconsList[ICON_PAUSE] = new PauseIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_PAUSE]);
	p.x += config.iconWidth;

	iconsList[ICON_RESUME] = new ResumeIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_RESUME]);
	p.x += config.iconWidth;

	iconsList[ICON_SAVE] = new SaveIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_SAVE]);
	p.x += config.iconWidth;

	iconsList[ICON_LOAD] = new LoadIcon1(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_LOAD]);
	p.x += config.iconWidth;

	iconsList[ICON_EXIT] = new ExitIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_EXIT]);
}

Toolbar::~Toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete[] iconsList;
}

void Toolbar::draw() const
{
	for (int i = 0; i < ICON_COUNT; i++)
		iconsList[i]->draw();

	window* pWind = pGame->getWind();

	// --- NEW: Draw the Farm Frenzy banner in the top right ---
	int bannerWidth = 250; // You can tweak this number to make it wider/thinner
	int bannerHeight = config.toolBarHeight;
	int bannerX = config.windWidth - bannerWidth;
	int bannerY = 0;

	pWind->DrawImage("images\\farmfrenzy2banner.jpg", bannerX, bannerY, bannerWidth, bannerHeight);
	// ---------------------------------------------------------

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, config.toolBarHeight, pWind->GetWidth(), config.toolBarHeight);
}

bool Toolbar::handleClick(int x, int y)
{
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;


	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x co-ord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicled icon

	if (clickedIconIndex == ICON_EXIT) return true;

	return false;

}

