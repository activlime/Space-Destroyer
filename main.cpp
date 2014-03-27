/** @mainpage CSCI102 Programming Assignment 5
		Name : Andrew Cho
		ID   : 6042240885
		Prof : Professor Redekopp
    @section purpose Purpose/Overview
    	This program computer graphics game where the objective is to kill as many aliens as possible to rack up as many points as possible
    @section classes
    	There are classes of :
    		/Alien
    		/AlienBullet
    		/MasterAlien
    		/Bullet 
    		/Thing
    		/Gameview
    		/Spaceship
    		/MainWindow
    @section Mission/Goal
    	This program is supposed to provide a game with a UI and supposed to used for the enjoyment of users. It takes in the name of the player.
    	The player is able to control the spaceship to kill aliens that trying to kill him. The player's objective is rack up as many points as possible.
    	The game is supposed to challenging, but fun at the same time.
*/

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "spaceship.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    
    
    w.show();

    return a.exec();
}
