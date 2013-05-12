#ifndef DEVILALIEN_H
#define DEVILALIEN_H
#include "alienbullet.h"

using namespace std;
/**this is the class used to create alien bullets*/
class DevilAlien : public AlienBullet {
	public:
	DevilAlien (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow,
	bool isShieldz, bool isHeartz);
	bool moveDown(Spaceship* s); 
};

#endif
