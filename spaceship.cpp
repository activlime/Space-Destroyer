#include "spaceship.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

using namespace std;
/**constructor for the spaceship which initializes the picture, x coordinate, y coordinate, width of the picture
, the height of the picture, the velocity of the spaceship in the xdirection, the velocity of the spaceship
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move.*/
Spaceship::Spaceship(QPixmap *pm, int nx, int ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxWindow) : 
Thing(pm, nx,ny,nwidth, nheight, nvx,nvy, nxmaxWindow, nymaxWindow) {}
/**function to move spaceship. does nothing*/
void Spaceship::move() {}

//will be used if I make speed faster
/*else if (y + 3 < maxWindow) {
	int difference = ymaxWindow - y - 3;
	this->setOff*/
/**returns x coordinate of spaceship*/
int Spaceship::getX() {
	return x;
}
/**returns y coordinate of spaceship*/
int Spaceship::getY() {
	return y;
}
/**moves the spaceship up*/
void Spaceship::moveUp() {
	if (y - vY > 0) {
		y -= vY;
		this->setPos(x, y);
	} 
}
/**moves the spaceship down*/
void Spaceship::moveDown() {
	if (y + vY < ymaxWindow) {
		y += vY;
		this->setPos(x, y);
	} 
}
/**moves the spaceship right*/
void Spaceship::moveRight() { 
	if (x + vX < xmaxWindow) {
		x += vX;
		this->setPos(x, y);
	} 
}
/**moves the spaceship left*/
void Spaceship::moveLeft() {
	if (x - vX > 0) {
		x -= vX;
		this->setPos(x, y);
	} 
}
