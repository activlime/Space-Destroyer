#include "alien.h"
#include "thing.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <iostream>
using namespace std;

/**constructor for aliens which initializes the picture, x coordinate, y coordinate, width of the picture
, the height of the picture, the velocity of the alien bullet in the xdirection, the velocity of the alien bullet
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move.
Also stores the original x coordinate and the original y coordinate, the lives that the alien*/
Alien::Alien(QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxWindow) : 
Thing(pm, nx,ny, nwidth, nheight, nvx,nvy, nxmaxWindow, nymaxWindow) {
	originalX = nx;
	originalY = ny;
	lives = 3;
	isMaster = false;
}
/**this function makes alien move like a boucing rectangle. Velocity is determined by constructor*/
void Alien::move() {
	//We move by adding the velocity to the current position.
    //Then we test whether we have reached the edge of our moving space
    //If so, we reverse the velocity (y-velocity when we hit the top/bottom and
    //x-velocity when we hit the left/right sides) and undo the position change
    //that moved part of the rectangle off the screen.
    x += vX;
    y += vY;

    if ( x < 0 ) {
        vX = -vX;
        x += vX;
    }

    if ( y < 0 ) {
        vY = -vY;
        y +=vY;
    }

    if ( (x+width) > xmaxWindow) {
         vX = -vX;
         x+=vX;
    }

    if ( (y+height) > ymaxWindow) {
         vY = -vY;
         y+=vY;
    }
    this->setPos(x,y);
}
/**returns the x coordinate of the alien*/
int Alien::getX() {
	return x;
}
/**returns the y coordinate of the alien*/
int Alien::getY() {
	return y;
}
/**returns the original x coordinate of the alien*/
int Alien::getOrigX() {
	return originalX;
}
/**returns the originial y coordinate of the alien*/
int Alien::getOrigY() {
	return originalY;
}
/**returns the difference of the original x coordinate of the alien to current x coordinate
of the alien. Used to move the aliens back to formation*/
long Alien::getDifferenceX() {
	return originalX - x;
}
/**returns the difference of the original y coordinate of the laien to the curren y coordinate
of the alien. Used to move the aliens back to formation*/
long Alien::getDifferenceY() {
	return originalY - y;
}
/**moves the aliens back to formation according to the difference of the original to current coordinates*/
void Alien::moveBack(int nx, int ny) {
	x = nx;
	y = ny;
	this->setPos(x, y);
}

