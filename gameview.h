#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include<QGraphicsScene>
#include<QGraphicsView>
/**creates a view for the game. Created in seperate class to avoid the consumption of keypress of view in mainwindow*/
class Gameview : public QGraphicsView {
	public:
	Gameview(int WINDOW_MAX_X, int WINDOW_MAX_Y);
	QGraphicsScene* scene;
};


#endif
