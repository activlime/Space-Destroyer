#include "alienbullet.h"
#include "thing.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
using namespace std;
/**constructor for alien bullet which initializes the picture, x coordinate, y coordinate, width of the picture
, the height of the picture, the velocity of the alien bullet in the xdirection, the velocity of the alien bullet
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move*/
AlienBullet::AlienBullet(QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxWindow
, bool isShieldz, bool isHeartz) : Thing(pm, nx,ny,nwidth, nheight, nvx,nvy, nxmaxWindow, nymaxWindow) {
	isShield = isShieldz;
	isHeart = isHeartz;
	isSacAlien = false;
}
/**move function for alienbullet. does nothing*/ 
void AlienBullet::move() {}
/**move down function for alienbullet which moves the alien bullet down according to velocity specified in constructor*/
bool AlienBullet::moveDown(Spaceship* s) {
	s->getX();
	y += vY;
	if (y > ymaxWindow) {
		return true;
	}
	setPos(x, y);
	return false;
}
