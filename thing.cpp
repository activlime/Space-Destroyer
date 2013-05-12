#include "thing.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <iostream>

using namespace std;
/**constructor for things which initializes the picture, x coordinate, y coordinate, width of the picture 
, the height of the picture, the velocity of the alien thing in the xdirection, the velocity of the thing
in the ydirection, and the maxWindow size in the x direction and the maxWindow size of the y direction in which it can move.*/
Thing::Thing(QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxWindow) : 
QGraphicsPixmapItem(*pm) {
	pixMap = pm;
	x = nx;
	y = ny;
	width = nwidth;
	height = nheight;
	this->setPos(x,y);
	//cout << this->pos().x() << endl;
	vX = nvx;
	vY = nvy;
	xmaxWindow = nxmaxWindow;
	ymaxWindow = nymaxWindow;
}
	
