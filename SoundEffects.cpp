#include "SoundEffects.h"

bool soundPlayer::initializeSF() {
    if (!chick.loadFromFile("chick.ogg")) return false;
    schick.setBuffer(chick);

    if (!cow.loadFromFile("cow.ogg")) return false;
    scow.setBuffer(cow);

    if (!wolf.loadFromFile("wolf.ogg")) return false;
    swolf.setBuffer(wolf);

    if (!click.loadFromFile("click.ogg")) return false;
    sclick.setBuffer(click);

    if (!grass.loadFromFile("grass.ogg")) return false;
    sgrass.setBuffer(grass);

    
    if (!lvlUP.loadFromFile("lvlup.ogg")) return false;
    slvlUP.setBuffer(lvlUP);

    if (!drop.loadFromFile("drop.wav")) return false;
    sdrop.setBuffer(drop);


    if (!cat.loadFromFile("cat.ogg")) return false;
    scat.setBuffer(cat);


    return true;
}

void soundPlayer::playschick() { schick.play(); };
void soundPlayer::playsdrop() { sdrop.play(); };
void soundPlayer::playslvlUP() { slvlUP.play(); };
void soundPlayer::playsclick() { sclick.play(); };
void soundPlayer::playswolf() { swolf.play(); };
void soundPlayer::playscat(){ scat.play(); };
void soundPlayer::playsgrass() { sgrass.play(); };
void soundPlayer::playscow() { scow.play(); };