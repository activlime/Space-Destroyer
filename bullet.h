#ifndef BULLET_H
#define BULLET_H
#include "thing.h"

using namespace std; 
/**this class creates the bullet shot by the spaceship*/
class Bullet : public Thing {
	public:
	Bullet (QPixmap *pm, int nx, int ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow);
	void move();
	bool moveUp();
};

#endif
