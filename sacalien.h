#ifndef SACALIEN_H
#define SACALIEN_H
#include "alienbullet.h"

using namespace std;
/**this is the class used to create sac alien*/
class SacAlien : public AlienBullet {
	public:
	SacAlien (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow,
	bool isShieldz, bool isHeartz);
	bool moveDown(Spaceship* s); 
};

#endif
