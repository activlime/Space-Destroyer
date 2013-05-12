#include "alien.h"
#include "masteralien.h"
#include "thing.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <iostream>
using namespace std;

/**constructor for masteraliens which initializes the picture, x coordinate, y coordinate, width of the picture
, the height of the picture, the velocity of the masteralien bullet in the xdirection, the velocity of the masteralien bullet
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move.
Also stores the original x coordinate and the original y coordinate, the lives that the masteralien. Puts true to detect that this character
is a masteralien*/
MasterAlien::MasterAlien(QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxWindow) : 
Alien(pm, nx,ny, nwidth, nheight, nvx,nvy, nxmaxWindow, nymaxWindow) {
	lives = 7; 
	isMaster = true;
}
/**this function makes the alien move. Master aliens can only move left and right*/
void MasterAlien::move() {
	//We move by adding the velocity to the current position.
    //Then we test whether we have reached the edge of our moving space
    //If so, we reverse the velocity (y-velocity when we hit the top/bottom and
    //x-velocity when we hit the left/right sides) and undo the position change
    //that moved part of the rectangle off the screen.
    x += vX;

    if ( x < 0 ) {
        vX = -vX;
        x += vX;
    }

    if ( (x+width) > xmaxWindow) {
         vX = -vX;
         x+=vX;
    }

    this->setPos(x,y);
}

