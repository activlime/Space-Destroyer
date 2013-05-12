#include "bullet.h"
#include "thing.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
using namespace std; 

/**constructor for bullet which initializes the picture, x coordinate, y coordinate, width of the picture
, the height of the picture, the velocity of the bullet in the xdirection, the velocity of the bullet
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move.*/
Bullet::Bullet(QPixmap *pm, int nx, int ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxWindow) : 
Thing(pm, nx,ny,nwidth, nheight, nvx,nvy, nxmaxWindow, nymaxWindow) {}
/**move fucntion for the bullet. Does nothing*/
void Bullet::move() {}
/**move function for the bullet which gradually moves the bullet shot the spaceship up*/
bool Bullet::moveUp() {
	y -= vY;
	if (y < 0) {
		return true;
	}
	setPos(x, y);
	return false;
}
