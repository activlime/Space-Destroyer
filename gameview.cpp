#include<QGraphicsScene>
#include<QGraphicsView>
#include"gameview.h"
/**constructor of gameview. It creates the scene with the boundaries passed through as paramters*/
Gameview::Gameview(int WINDOW_MAX_X, int WINDOW_MAX_Y) { 
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, WINDOW_MAX_X -10, WINDOW_MAX_Y -10);\
	this->setScene(scene);
}

