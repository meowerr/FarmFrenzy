#pragma once
#include "Core/GameObject.h"

class Warehouse : public GameObject
{
private:
    string imagePath;
    point position;
    int objWidth;
    int objHeight;

public:
    Warehouse(Game* r_pGame, point r_uprleft, int r_width, int r_height);
    virtual void draw() const;
};