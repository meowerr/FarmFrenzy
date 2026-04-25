#include "GameObject.h"

#include <iostream>

GameObject::GameObject(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc) : Drawable (r_pGame, ref, r_width, r_height)
{
	fillColor = fc;
	borderColor = bc;
}

void GameObject::setRefPoint(point p)
{
	RefPoint = p;
}


// you should implement this function knowing that each game object has refPoint, width and height 
// for simplicity, you can consider all game objects are rectangles
//bool GameObject::CollisionDetection(BudgetbarIcon& a1, BudgetbarIcon& a2)
//{
//	int a1x = a1.getRef().x , a1y = a1.getRef().y;
//	int a2x = a2.getRef().x, a2y = a2.getRef().y;
//
//
//	if ((a1x + a1.getWidth() >= a2x) && (a1x <= a2x + a2.getWidth()) && (a1y <= a2y + a2.getHeight()) && (a1y + a1.getHeight() >= a2y)) { return true; cout << "Collision!"; }
//
//
//	else { return false; }
//}
