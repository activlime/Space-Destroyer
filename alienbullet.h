#ifndef ALIENBULLET_H
#define ALIENBULLET_H
#include "thing.h"
#include "spaceship.h"

using namespace std;
/**this is the class used to create alien bullets*/
class AlienBullet : public Thing {
	public:
	AlienBullet (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxwindow,
	bool isShieldz, bool isHeartz);
	void move();
	virtual bool moveDown(Spaceship* s); 
	bool isShield;
	bool isHeart;
	bool isSacAlien;
};

#endif
