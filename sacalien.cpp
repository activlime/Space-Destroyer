#include "sacalien.h"
/**constructor for sacalien which initializes the picture, x coordinate, y coordinate, width of the picture
, the height of the picture, the velocity of the sacalien in the xdirection, the velocity of the sac alien
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move
but also initializes the isSacAlien data member indicating that it is a sacAlien*/
SacAlien::SacAlien (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow,
	bool isShieldz, bool isHeartz) : AlienBullet (pm, nx, ny, nwidth, nheight, nvx, nvy, nxmaxWindow, nymaxwindow,
	isShieldz, isHeartz) {
		isSacAlien = true;
}
/**Moves down but detects where the user is to try to kill them. Only detects left and right movement, not up and down.*/
bool SacAlien::moveDown(Spaceship* s) {
	if (s->getX() > x) {
		x += vX;
	} else if (s->getX() < x) {
		x -= vX;
	}
	y += vY;
	if (y > ymaxWindow) {
		return true;
	}
	setPos(x, y);
	return false;
}
