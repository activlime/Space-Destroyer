#include "devilAlien.h"
/**constructor for devilalien which initializes the picture, x coordinate, y coordinate, width of the picture
, the height of the picture, the velocity of the devilalien in the xdirection, the velocity of the devilAlien
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move
but also initializes the isSacAlien data member indicating that it is a sacAlien*/
DevilAlien::DevilAlien (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow,
	bool isShieldz, bool isHeartz) : AlienBullet (pm, nx, ny, nwidth, nheight, nvx, nvy, nxmaxWindow, nymaxwindow,
	isShieldz, isHeartz) {
		isSacAlien = true;
	}
/**Moves down but detects where the user is to try to kill them. Only detects left and right movement, not up and down.*/
bool DevilAlien::moveDown(Spaceship* s) {
	if (s->getX() > x) {
		x += vX;
	} else if (s->getX() < x) {
		x -= vX;
	}
	if (s->getY() > y) {
		y += vY;
	} else if (s->getY() < y) {
		y -= vY;
	}
	setPos(x, y);
	return false;
}
