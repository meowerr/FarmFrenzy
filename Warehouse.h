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
    int storedeggs = 0; //variables to keep track of milks and eggs in warehouse
    int storedmilk = 0;
    int eggprice = 200; // variables for prices in warehouse
    int milkprice = 400;
    void addegg() { storedeggs++; } //function to add eggs and milk in warehouse
    void addmilk() { storedmilk++; }

    void resetegg() { storedeggs = 0; }//shazly
    void resetmilk() { storedmilk = 0; }
};