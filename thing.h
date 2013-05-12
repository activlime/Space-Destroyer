#ifndef THING_H
#define THING_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

using namespace std;
/**class used to create all things */
class Thing: public QGraphicsPixmapItem {
	public:
	Thing (QPixmap *pm, float nx, float ny, int nwidth, int nheight, double nvx, double nvy, int nxmaxWindow, int nymaxWindow);
	virtual void move() = 0;
	
	protected:
	float x;
	float y;
	int width;
	int height;
	double vX;
	double vY;
	QPixmap *pixMap;
	int xmaxWindow;
	int ymaxWindow;
};
#endif
