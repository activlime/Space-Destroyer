#ifndef ALIEN_H
#define ALIEN_H
#include "thing.h"

using namespace std;

/**this class is used to create aliens in gameplay*/
class Alien : public Thing {
	public:
	Alien (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow);
	void move();
	void moveBack(int nx, int ny);
	int getX();
	int getY();
	int getOrigX();
	int getOrigY();
	long getDifferenceX();
	long getDifferenceY();
	int lives;
	bool isMaster;
	protected:
	int originalX;
	int originalY;
};

#endif
