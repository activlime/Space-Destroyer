#include "mainwindow.h"
#include "thing.h"
#include "spaceship.h"
#include "QPushButton"
#include "alien.h"
#include <iostream>
#include <string>
#include <QtGui>
#include <QMainWindow>
#include <QKeyEvent>
#include "gameview.h"
#include "bullet.h"
#include <QErrorMessage> 
#include <QPalette>
#include <QLineEdit>
#include <QString>
#include "masteralien.h"
#include "alienbullet.h"
#include <QProcess>
#include <QPushButton>
#include <stdexcept>
#include <fstream>
#include <QListWidgetItem>
#include <QListWidget>
#include "sacalien.h"
#include "devilAlien.h"

using namespace std;
/** constructor for mainwindow which sets up the entire program*/
MainWindow::MainWindow()  {
    //initializing needed data members
    count = 0;
    masterCount = 1;
    score = 0;
    numShipBullets = 1;
    lives = 10;
    frequencyAB = 175;
    frequencyMA = 50;
    frequencyShield = 6000;
    frequencyHeart = 4000;
    numCommon = 0;
    numMaster = 0;
    numUltimate = 0;
    vCommon = 1;
    vMaster = 25;
    vUltimate = 2;
    commonDead = false;
    masterDead = false;
    ultimateDead = false;
    shipDead = false;
    createdGame = false;
    pause = false;
    
     this->setFixedSize(WINDOW_MAX_X, WINDOW_MAX_Y);
    //menu initialization
    menu = new Gameview(WINDOW_MAX_X, WINDOW_MAX_Y);
    menu->scene->setBackgroundBrush(*(new QBrush(*(new QPixmap("pictures/nebula.png")))));
    this->setCentralWidget(menu); //putting menu as central widget
    
    QString* t = new QString("Space Destroyer");
    QLineEdit* title = new QLineEdit(*t);
    title->setGeometry(WINDOW_MAX_X/2 - 150,30 +20,300,150);
    title->setAlignment(Qt::AlignHCenter);
    title->setReadOnly(true);
    menu->scene->addWidget(title);
    
    pName = new QLineEdit("Enter Player Name");
    pName->setGeometry(WINDOW_MAX_X/2 - 100, WINDOW_MAX_Y/2 - 100 + 20,200,30);
    pName->setAlignment(Qt::AlignHCenter);
    menu->scene->addWidget(pName);
    
    startGame = new QPushButton("Start Game");
    startGame->setGeometry(WINDOW_MAX_X / 2 - 60 - 15, WINDOW_MAX_Y /2 - 50 +20, 150, 50);
    menu->scene->addWidget(startGame);
    connect(startGame, SIGNAL(clicked()), this, SLOT(gameStart()));
    
    quitGame = new QPushButton("Quit");
    quitGame->setGeometry(WINDOW_MAX_X / 2 - 30 - 15, WINDOW_MAX_Y/2 + 20, 100, 50);
    menu->scene->addWidget(quitGame);
    connect(quitGame, SIGNAL(clicked()), qApp, SLOT(quit()));
    
    QString z = "Press <q> to quit during game";
    QLineEdit* pressq = new QLineEdit(z);
    pressq->setGeometry(WINDOW_MAX_X/2 - 125, WINDOW_MAX_Y/2 + 50 +20,250,30);
    pressq->setAlignment(Qt::AlignHCenter);
    pressq->setReadOnly(true);
    menu->scene->addWidget(pressq);
    QString m = "Press <r> to restart during game";
    QLineEdit* pressr = new QLineEdit(m);
    pressr->setGeometry(WINDOW_MAX_X/2 - 125, WINDOW_MAX_Y/2 + 80 + 20,250,30);
    pressr->setAlignment(Qt::AlignHCenter);
    pressr->setReadOnly(true);
    menu->scene->addWidget(pressr);
    QString r = "Press <p> to pause during game and press again to resume";
    QLineEdit* pressp = new QLineEdit(r);
    pressp->setGeometry(WINDOW_MAX_X/2 - 225, WINDOW_MAX_Y/2 + 80 + 20 + 30,450,30);
    pressp->setAlignment(Qt::AlignHCenter);
    pressp->setReadOnly(true);
    menu->scene->addWidget(pressp);
    //this->setFocus();
}
/**starts the game with the user pressing the start button. The user must of entered a name to start*/
void MainWindow::gameStart() {
	//cout << "check1" << endl;
	if (pName->isModified()) {
		QString temp = pName->text();
		try {
			if (temp == "") {
	    			throw std::invalid_argument("Must enter player name.");
			}
	
    		}
		catch (const std::invalid_argument& ia) {
		    	QErrorMessage errorMessage;
			errorMessage.showMessage(ia.what());
			errorMessage.exec();
			return;
    		}
    		strPName = temp;
    		createGame();
	} else {
		QErrorMessage errorMessage;
		errorMessage.showMessage("Must enter player name.");
		errorMessage.exec();
		return;
	}
}
/**starts a new window for the actual game and makes the menu window disappear*/
void MainWindow::createGame() {
	createdGame = true;
	//initializing the main game view;
    menu->setVisible(false);
    gv = new Gameview(WINDOW_MAX_X, WINDOW_MAX_Y);
    //gv->setVisible(false);
    this->setCentralWidget(gv);
    
    
    //setting score and playername
    sScore.setNum(score);
    strScore = new QLineEdit("Score: " + sScore);
    strScore->setGeometry(0,0,200,40);
    strScore->setReadOnly(true);
    gv->scene->addWidget(strScore);
    
    QLineEdit* playerName = new QLineEdit(strPName);
    playerName->setGeometry(0,40,200,40);
    playerName->setReadOnly(true);
    gv->scene->addWidget(playerName);

    //This sets the size of the window and gives it a title.
    gv->setFixedSize( WINDOW_MAX_X, WINDOW_MAX_Y);
    gv->setWindowTitle( "Space Destroyer");
    //QPalette* p = new QPalette();
    //gv->scene->setPalette(*p);
   
    createSpaceship(); 
    printHearts();
    createMonsters(vCommon);
    moveMonster();
    //This is how we do animation. We use a timer with an interval of 5 milliseconds
    //We connect the signal from the timer - the timeout() function to a function
    //of our own - called handleTimer - which is in this same MainWindow class
    timer = new QTimer(this);
    timer->setInterval(5);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
    
    timer->start();
    this->setFocus();
}
/**this detects which key the user has clicked and according to the clicks does some action*/
void MainWindow::keyPressEvent(QKeyEvent *e) {

	switch(e->key()) {
		if (createdGame) {
			case Qt::Key_Left :
				s->moveLeft();
				break;
			case Qt::Key_Right :
				s->moveRight();
				break;
			case Qt::Key_Up:
				s->moveUp();
				break;
			case Qt::Key_Down:
				s->moveDown();
				break;
			case Qt::Key_Space:
				if (!shipDead) {
					this->createBullet();
				}
				break;
			case Qt::Key_P:
				if (!pause) {
					timer->stop();
					pause = true;
				} else {
					timer->start();
					pause = false;
				}
		}
		case Qt::Key_Q:
			qApp->quit();
			break;
		case Qt::Key_R:
			qApp->quit();
			QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
	}
}
/**this functions handles all the movements based on the timer*/
void MainWindow::handleTimer() {
	if (count > 200) {
		this->moveMonster();
	}
	this->moveBullets();
	this->collisionAliens();
	this->collisionBullets();
	this->collisionAlienBullets();
	if (numCommon > 0 && !commonDead) {
		if (count % frequencyAB == 0) {
			this->shootAlienBullets();
		}
	} else if (numMaster > 0) {
		if (count % frequencyMA == 0) {
			this->shootMasterAlienBullets();
		}
	}
	if (masterCount % frequencyShield == 0) {
		createShield();
	}
	if (masterCount % frequencyHeart == 0) {
		createHeart();
	}
	if (masterCount % 700 == 0) {
		createSacAlien();
	}
	if (masterCount % 1000 == 0) {
		createDevilAlien();
	}
	this->moveAlienBullets();
	count++;
	masterCount++;
	//cout << count << endl;
}
/**handles the temporary timer to move the aliens back if user loosed a life*/
void MainWindow::handleTimerTemp() {
	//cout << countTemp << endl;
	if (countTemp == 400) {
			//cout << temp.timerId() << endl;
			deathTimer->stop();
			int size = (int)ab.size();
			for (int i = 0; i < size; i++) {
				int zz = size - i - 1;
				delete ab[zz];
				//cout << "test" << endl;
				ab.pop_back();
			}
			delete exp;
			//delete deathTimer;
			delete s;
			createSpaceship();
			timer->start();
			return;
	} else {
	//cout << countTemp << endl;
		if (countTemp % 2 == 0) {
				for (int i = 0; i < (int)characters.size(); i++) {
					if ((characters[i]->getX() != characters[i]->getOrigX()) && (characters[i]->getDifferenceX() > 0)) {
						characters[i]->moveBack(characters[i]->getX() + 1, characters[i]->getY());
					}
					if ((characters[i]->getX() != characters[i]->getOrigX()) && (characters[i]->getDifferenceX() < 0)) {
						characters[i]->moveBack(characters[i]->getX() - 1, characters[i]->getY());
					}
					if (characters[i]->getY() != characters[i]->getOrigY() && (characters[i]->getDifferenceY() < 0)) {
						characters[i]->moveBack(characters[i]->getX(), characters[i]->getY() - 1);
					}
					if (characters[i]->getY() != characters[i]->getOrigY() && (characters[i]->getDifferenceY() > 0)) {
						characters[i]->moveBack(characters[i]->getX(), characters[i]->getY() + 1);
					}
				}
		}
		countTemp++;
	}
}
/**creates the spaceship in the gameplay view*/
void MainWindow::createSpaceship()  {
    QPixmap* shipPic = new QPixmap("pictures/spaceship.png");
    s = new Spaceship(shipPic, WINDOW_MAX_X/2, WINDOW_MAX_Y - 150, 100, 100, 15, 15, WINDOW_MAX_X - 100, WINDOW_MAX_Y - 100);
    s->setScale(1);
    shipDead = false;
    (*gv).scene->addItem(s);
}
/**creating commonAlien monsters to gameplay*/
void MainWindow::createMonsters(int nx) {
    //Creating aliens
    gv->scene->setBackgroundBrush(*(new QBrush(*(new QPixmap("pictures/background2.png")))));
    QPixmap* cAlien = new QPixmap("pictures/commonalien.png");
    Alien* commonAlien;
    int initialX = 110;
    for (int i = 0; i < 8 ; i++) {
    	    int tempvx = rand() % 4 + nx;
    	    int tempvy = rand() % 4 + nx;
	    commonAlien = new Alien(cAlien, 50 + initialX * i, 50, 100, 100, tempvx, tempvy, WINDOW_MAX_X, WINDOW_MAX_Y);
	    numCommon++;
	    (*gv).scene->addItem(commonAlien);
	    characters.push_back(commonAlien);
    }	    
    //commonAlien->move();
}
/**creates the Master aliens which can move only side to side. Each has ten lives*/
void MainWindow::createMasterAlien(int nx) {
	gv->scene->setBackgroundBrush(*(new QBrush(*(new QPixmap("pictures/space2.png")))));
    QPixmap* cAlien = new QPixmap("pictures/masteralien.png");
    MasterAlien* mAlien;
    int initialX = 150;
    for (int i = 0; i < 3 ; i++) {
    	    int tempvx = rand() % 20 - nx;
    	    int tempvy = 0;
    	    //int tempvy = rand() % 4 + 1;
	    mAlien = new MasterAlien(cAlien, 50 + initialX * i, 50 + (70*i), 200, 100, tempvx, tempvy, WINDOW_MAX_X, WINDOW_MAX_Y);
	    mAlien->setScale(.5);
	    numMaster++;
	    (*gv).scene->addItem(mAlien);
	    characters.push_back(mAlien);
    }	 	
}
/**creates ultimate alien which only bounces around but has many lives*/
void MainWindow::createUltimateAlien(int nx) {
	gv->scene->setBackgroundBrush(*(new QBrush(*(new QPixmap("pictures/space3.png")))));
    QPixmap* cAlien = new QPixmap("pictures/ultimate.png");
    Alien* ultimateAlien;
    
    int tempvx = nx;
    int tempvy = -nx;
    ultimateAlien = new Alien(cAlien, WINDOW_MAX_X / 2, 10, 100, 100, tempvx, tempvy, WINDOW_MAX_X - 150, WINDOW_MAX_Y-150);
    numUltimate++;
    ultimateAlien->lives = 15;
    (*gv).scene->addItem(ultimateAlien);
    characters.push_back(ultimateAlien);
    //commonAlien->move();c
}
/**Creates the general sacalien who is player-aware and tries to sacrifies itself to kill the user. The Sacalien will track only Left and right.
but constantly move down*/
void MainWindow::createSacAlien() {    
	QPixmap* pm = new QPixmap("pictures/sacAlien.png");
	int nx = rand() % WINDOW_MAX_X;
	if (nx > WINDOW_MAX_X - 50) {
		nx-=50; 
	}
	SacAlien* newBullet = new SacAlien(pm, nx, 0, nx, 100, 1, .8, WINDOW_MAX_X, WINDOW_MAX_Y
	, false, false);
	newBullet->setScale(1);
	(*gv).scene->addItem(newBullet); 
	ab.push_back(newBullet);
}
/**Creates a devil alien who is player-aware and tries to sacrifies itself to kill the user. The devil will track up and down. Left and right.*/
void MainWindow::createDevilAlien() {    
	QPixmap* pm = new QPixmap("pictures/devil.png");
	int nx = rand() % WINDOW_MAX_X;
	if (nx > WINDOW_MAX_X - 50) {
		nx-=50; 
	}
	DevilAlien* newBullet = new DevilAlien(pm, nx, 0, nx, 100, .5, .3, WINDOW_MAX_X, WINDOW_MAX_Y
	, false, false);
	newBullet->setScale(1);
	(*gv).scene->addItem(newBullet); 
	ab.push_back(newBullet);
}
/**creates master alien bullets which shoots three at a time*/
void MainWindow::createMasterAlienBullets(Alien* a) {
	for (int i = 0; i < 3; i++) {
		QPixmap* pm = new QPixmap("pictures/thunder.png");
		AlienBullet* newBullet = new AlienBullet(pm, a->getX() + 10 + (i*20), a->getY() + 40, 100, 100, .6, .6, WINDOW_MAX_X, WINDOW_MAX_Y
		, false, false);
		newBullet->setScale(.6);
		(*gv).scene->addItem(newBullet);
		ab.push_back(newBullet);
	}
}
/**creates the powerup which allows the user to shoot mutiple bullets if captured. This ability is lost if they die*/
void MainWindow::createShield() {
	QPixmap* pm = new QPixmap("pictures/shield.png");
	int nx = rand() % WINDOW_MAX_X;
	if (nx > WINDOW_MAX_X - 100) {
		nx-=50;
	}
	AlienBullet* newBullet = new AlienBullet(pm, nx, 0, nx, 100, .4, .4, WINDOW_MAX_X - 100, WINDOW_MAX_Y
	, true, false);
	//newBullet->setScale(.6);
	(*gv).scene->addItem(newBullet);
	ab.push_back(newBullet);  
}
/**creates the heart which during the gameplay appears at random times. if captured, the player gets an extra life*/
void MainWindow::createHeart() {    
	QPixmap* pm = new QPixmap("pictures/heart.png");
	int nx = rand() % WINDOW_MAX_X;
	if (nx > WINDOW_MAX_X - 50) {
		nx-=50; 
	}
	AlienBullet* newBullet = new AlienBullet(pm, nx, 0, nx, 100, .4, .4, WINDOW_MAX_X, WINDOW_MAX_Y
	, false, true);
	newBullet->setScale(.5);
	(*gv).scene->addItem(newBullet); 
	ab.push_back(newBullet);
}
/**creates an explosion if spaceship runs into bullet or alien. Also 
triggers aliens to move back and away from the spaceship and to delete bullets in space.
only does this if user has at least one life left*/
void MainWindow::createExplosion() {
	//s->setVisible(false);
	QPixmap* explosion = new QPixmap("pictures/explosion.png");
        exp = new QGraphicsPixmapItem(*explosion);
        exp->setPos(s->getX(), s->getY());
        (*gv).scene->addItem(exp);
        timer->stop(); //end game
        s->setVisible(false);
        shipDead = true;
        --lives;
        printHearts();
        numShipBullets = 1;
        if (lives > 0) {
        	//cout << "ehllo" << endl;
        	delete health[health.size() -1];
        	health.pop_back();
        	countTemp =0;
		deathTimer = new QTimer();
		deathTimer->setInterval(5);
		connect(deathTimer, SIGNAL(timeout()), this, SLOT(handleTimerTemp()));
		deathTimer->start();
	} else {
		QErrorMessage errorMessage;
		QString num;
		num.setNum(score);
		errorMessage.showMessage("Game Over. Your Score: " + num);
		errorMessage.exec();
		
		/*ofstream fout;
		fout.open("topscores.txt");
		string tempPname = strPName.toLocal8Bit().constData();
		fout << tempPname << endl << score << endl;
		fout.close();*/
		string tempPname = strPName.toLocal8Bit().constData();
		//fout << tempPname << endl << score << endl;
		vector<string> playerNa;
		vector<long> playerSc;
		ifstream fin;
		string topPName;
		long topScore;
		fin.open("topscores.txt"); 
		while (getline(fin,topPName)) {
			fin >> topScore;
			if (playerSc.size() < 10) {
				//cout << "pushing old score" << endl;
				playerNa.push_back(topPName);
				playerSc.push_back(topScore);
			}
			fin.ignore(1000, '\n'); 
		}
		fin.close();
		
		playerNa.push_back(tempPname);
		//cout << tempPname << endl;
		playerSc.push_back(score); 
		
		int temp;
		string tempk;
		for (int i = 0; i < (int)playerSc.size() - 1; i++) {
			//cout << playerNa.siz
			int max = i;
			for ( int j = i + 1; j < (int)playerSc.size(); j++ ) {
				if (playerSc[j] > playerSc[max]) {
					max = j;
				}
			}
			temp = playerSc[i];
			playerSc[i] = playerSc[max];
			playerSc[max] = temp;
			tempk = playerNa[i];
			playerNa[i] = playerNa[max];
			playerNa[max] = tempk;
		}
		if (playerSc.size() > 10) {
			playerSc.pop_back();
			playerNa.pop_back();
		}
		createdGame = false;
		gv->setVisible(false);
		topScoreBoard = new Gameview(WINDOW_MAX_X, WINDOW_MAX_Y);
		topScoreBoard->scene->setBackgroundBrush(*(new QBrush(*(new QPixmap("pictures/nebula.png")))));
    		this->setCentralWidget(topScoreBoard);
		QListWidget* topScoreList = new QListWidget();
		topScoreList->setGeometry(300, 75, 400, 300);
		QListWidgetItem* scoreItem;
		string str;
		QString qstrNumScore;
		QString qstrScore;
		QString qstr;
		QString total;
		
		QString s = "Top Scores";
		QLineEdit* start = new QLineEdit(s);
		start->setGeometry(WINDOW_MAX_X/2 - 125, 50,250,30);
		start->setAlignment(Qt::AlignHCenter);
		start->setReadOnly(true);
		topScoreBoard->scene->addWidget(start);
		
		for (int i = (int)playerSc.size() - 1; i >= 0; i--) {
			qstrNumScore.setNum(i+1);
			qstrScore.setNum(playerSc[i]);
			str = playerNa[i];
			//cout << str << endl;
			//Qstring qstr("0."+str);
			qstr = QString::fromStdString(str);
			scoreItem = new QListWidgetItem();
			total = qstrNumScore + ". " + qstr + " " + qstrScore;
			scoreItem->setText(total);
			topScoreList->insertItem(0, scoreItem);
		}
		topScoreBoard->scene->addWidget(topScoreList);
		ofstream fout;
		fout.open("topscores.txt");
		for (int i = 0; i < (int)playerSc.size(); i++) {
			fout << playerNa[i] << endl;
			fout << playerSc[i] << endl;
		}
		fout.close();
		
		QString z = "Press <q> to quit during game";
		QLineEdit* pressq = new QLineEdit(z);
		pressq->setGeometry(WINDOW_MAX_X/2 - 125, 300,250,30);
		pressq->setAlignment(Qt::AlignHCenter);
		pressq->setReadOnly(true);
		topScoreBoard->scene->addWidget(pressq);
		QString m = "Press <r> to restart during game";
		QLineEdit* pressr = new QLineEdit(m);
		pressr->setGeometry(WINDOW_MAX_X/2 - 125, 325,250,30);
		pressr->setAlignment(Qt::AlignHCenter);
		pressr->setReadOnly(true);
		topScoreBoard->scene->addWidget(pressr);
    
		//qApp->quit();
	}
}
/**moving Alien monsters which ever way they are assigned to move*/
void MainWindow::moveMonster() {
	if (count < 5000) {
		if (count % 8 == 0) {
			for (int i = 0; i < (int)characters.size(); i++) {
				characters[i]->move();
			}
		}
	} else {
		/*if (count == 5000) {
			for (int i = 0; i < (int)characters.size(); i++) {
				differenceX = characters[i]->getDifferenceX();
				differenceY = characters[i]->getDifferenceY();
			}
		}*/
		if (count % 2 == 0) {
			for (int i = 0; i < (int)characters.size(); i++) {
				if ((characters[i]->getX() != characters[i]->getOrigX()) && (characters[i]->getDifferenceX() > 0)) {
					characters[i]->moveBack(characters[i]->getX() + 1, characters[i]->getY());
				}
				if ((characters[i]->getX() != characters[i]->getOrigX()) && (characters[i]->getDifferenceX() < 0)) {
					characters[i]->moveBack(characters[i]->getX() - 1, characters[i]->getY());
				}
				if (characters[i]->getY() != characters[i]->getOrigY() && (characters[i]->getDifferenceY() < 0)) {
					characters[i]->moveBack(characters[i]->getX(), characters[i]->getY() - 1);
				}
				if (characters[i]->getY() != characters[i]->getOrigY() && (characters[i]->getDifferenceY() > 0)) {
					characters[i]->moveBack(characters[i]->getX(), characters[i]->getY() + 1);
				}
			}
		}
		if ((characters[0]->getX() == characters[0]->getOrigX()) && (characters[0]->getY() == characters[0]->getOrigY())) {
			count = 0;
		}
	}
}
/**creating Bullets for spaceship if the user presses spacebar*/
void MainWindow::createBullet() {
	for (int i = 0; i < numShipBullets; i++) {
		QPixmap* pm = new QPixmap("pictures/bullet1.png");
		int nx = 0;
		if (numShipBullets > 1) {
			nx  = (-15 * (i+1)) + (45 * (i));
		}
		Bullet* newBullet = new Bullet(pm, (s->getX() + 15 + nx), s->getY() - 30, 30, 100, 3, 3, WINDOW_MAX_X, WINDOW_MAX_Y);
		newBullet->setScale(.25);
		(*gv).scene->addItem(newBullet);
		bb.push_back(newBullet);
	}
}
/**sets the score of the scoreboard on the gameplay screen*/
void MainWindow::setScore() {
    QString sScore;
    sScore.setNum(score);
    strScore->setText("Score: " + sScore);
}
/**checks constantly if the spaceship has collided with the aliens. If collided, it creates an explosion and the user looses a life*/
void MainWindow::collisionAliens() {
	for (int i = 0; i < (int)characters.size(); i++) {
		if (s->collidesWithItem(characters[i])) {
			createExplosion();
		}
	} 
}
/**creates the bullets for common aliens*/
void MainWindow::createCommonAlienBullet(Alien* a) {
	//cout << "creating alien bullets" << endl;
	QPixmap* pm = new QPixmap("pictures/commonalienbullet.png");
	AlienBullet* newBullet = new AlienBullet(pm, a->getX() + 23, a->getY() + 40, 30, 100, .7, .7, WINDOW_MAX_X, WINDOW_MAX_Y, false, false);
	newBullet->setScale(.4);
	(*gv).scene->addItem(newBullet);
	ab.push_back(newBullet);
}
/**actually shoots the common alien bullets at random times and with random aliens*/
void MainWindow::shootAlienBullets() {
	int num = rand() % (int)characters.size();
	for (int i = 0; i < num; i++) {
		int r = rand() % (int)characters.size();
		createCommonAlienBullet(characters[r]);
	}
}
/**shoots master alien bullets ar random times and with random aliens*/
void MainWindow::shootMasterAlienBullets() {
	int num = rand() % (int)characters.size();
	for (int i = 0; i < num; i++) {
		int r = rand() % (int)characters.size();
		createMasterAlienBullets(characters[r]);
	}
}
/**moves Alien bullets down*/
void MainWindow::moveAlienBullets() {
	int flag = false;
	for (int i = 0; i < (int)ab.size(); i++) {
		flag = ab[i]->moveDown(s);
		if (flag && (int)ab.size() > 0) {
			delete ab[i];
			ab[i] = ab[ab.size() - 1];
			ab.pop_back();
		}
	}
}

/**moves the spaceship bullets up if created*/
void MainWindow::moveBullets() {
	int flag = false;
	for (int i = 0; i < (int)bb.size(); i++) {
		flag = bb[i]->moveUp();
		if (flag && (int)bb.size() > 0) {
			delete bb[i];
			bb[i] = bb[bb.size() - 1];
			bb.pop_back();
		}
	}
}

/**sees if spaceship's bullets make contact with aliens*/
void MainWindow::collisionBullets() {
	for (int i = 0; i < (int)bb.size(); i++) {
		for (int k = 0; k < (int)ab.size(); k++) {
			if (ab[k]->isSacAlien && bb[i]->collidesWithItem(ab[k])) {
				score+=100;
				setScore();
				delete ab[k];
				ab[k] = ab[ab.size() - 1];
				ab.pop_back();
				delete bb[i];
				bb[i] = bb[bb.size() - 1];
				bb.pop_back();
				return;
			}
		}
		for (int j = 0; j < (int)characters.size(); j++) {
			if (bb[i]->collidesWithItem(characters[j])) {
				//cout << characters[j]->lives << endl;
				if (characters[j]->lives == 0) {
					delete characters[j];
					characters[j] = characters[characters.size() - 1];
					characters.pop_back();
					delete bb[i];
					bb[i] = bb[bb.size() - 1];
					bb.pop_back();
					if (numCommon > 0) {
						numCommon--;
						score+=50;
						setScore();
					}
					if (numMaster > 0) {
						numMaster--;
						score+=150;
						setScore();
					}
					if (numUltimate > 0) {
						numUltimate--;
						score+=300;
						setScore();
						ultimateDead = true;
					}
					if (numCommon == 0 && !commonDead) {
						commonDead = true;
						createMasterAlien(vMaster += 5);
					}
				
					if (commonDead && numMaster==0 && !masterDead) {
						masterDead = true;
						createUltimateAlien(vUltimate+=4);
					}
					if (commonDead&& numUltimate ==0 && ultimateDead) {
						createMonsters(vCommon+=2);
						commonDead = false;
						masterDead = false;
						ultimateDead = false;
						
					}
				} else if (characters[j]->lives > 0) {
					characters[j]->lives--;
					delete bb[i];
					bb[i] = bb[bb.size() - 1];
					bb.pop_back();
				}
				return;
			}
		}
	}
}
/**sees if alien bullets collide with spaceship
Also sees if powerup or heart runs into spaceship.*/
void MainWindow::collisionAlienBullets() {
	for (int i = 0; i < (int)ab.size(); i++) {
		if (ab[i]->collidesWithItem(s)) {
			if (!ab[i]->isShield && !ab[i]->isHeart) {
				this->createExplosion();
			} else if (numShipBullets < 3 && ab[i]->isShield) {
				numShipBullets++;
			} else if (lives < 10 && ab[i]->isHeart) {
				lives++;
				printHearts();
			}
			delete ab[i];
			ab[i] = ab[ab.size() - 1];
			ab.pop_back();
			return;
		}
	}
}
/**this displays the score*/
void MainWindow::displayScore() { 
	QString strScore = "Score";
	QTextEdit* sScore = new QTextEdit(strScore, this);
	sScore->setReadOnly(true);
	sScore->move(30,30);	
	gv->scene->addWidget(sScore);
}
/**printing hearts on the screen depending on how many lives the player has*/
void MainWindow::printHearts() {
	for (int i = 0; i < (int)health.size(); i++ ) {
		delete health[health.size() -1];
        	health.pop_back();
	}
	for (int i = 1; i <= lives; i++) {
		//cout << "why" << endl;
		QPixmap* pm = new QPixmap("pictures/heart.png");
		QGraphicsPixmapItem* h = new QGraphicsPixmapItem(*pm);
		h->setPos(WINDOW_MAX_X - (i*40), 5);
		h->setScale(.3);
		health.push_back(h);
		(*gv).scene->addItem(h);
	}
}

/**destructor for mainwindow. Does nothing.*/
MainWindow::~MainWindow()  
{
    //delete timer;
}

