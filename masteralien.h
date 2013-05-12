#ifndef MASTERALIEN_H
#define MASTERALIEN_H
#include "alien.h"

using namespace std;
/**class to create master alien */
class MasterAlien : public Alien {
	public:
	MasterAlien (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow);
	void move();
};

#endif
