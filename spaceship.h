#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "thing.h"

using namespace std;
/**class used to create spaceship*/
class Spaceship : public Thing { 
	public:
	Spaceship (QPixmap *pm, int nx, int ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow);
	int getX();
	int getY();
	void move();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};

#endif
