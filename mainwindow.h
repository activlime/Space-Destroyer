#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QVector>
#include <QKeyEvent>
#include <QLineEdit>
#include <QString>
#include "thing.h"
#include "spaceship.h"
#include "alien.h"
#include "gameview.h"
#include "bullet.h"
#include "alienbullet.h"
#include "masteralien.h"
#include <string>
#include <QListWidgetItem>
#include <QListWidget>
#include "sacalien.h"

#define WINDOW_MAX_X 1000
#define WINDOW_MAX_Y 600

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow();
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);  
private:
    //menu data members
    QGraphicsScene* scene;
    QPushButton* startGame;
    QPushButton* quitGame;
    QLineEdit* pName;
    QString strPName;
    
    QTimer *timer;
    QTimer* deathTimer;
    QGraphicsPixmapItem* exp;
    Gameview* gv;
    Gameview* menu;
    Gameview* topScoreBoard;
    Spaceship *s;
    QString sScore;
    vector<Alien*> characters;
    QLineEdit* strScore;
    //vector<MasterAlien*> mCharacters;
    vector<Bullet*> bb;
    vector<AlienBullet*> ab;
    vector<QGraphicsPixmapItem*> health;
    //vector<MasterAlien*> ma;
    void setScore();
    void createSpaceship();
    void createBullet();
    void moveBullets();
    void createMonsters(int nx);
    void moveMonster(); 
    long count;
    long masterCount;
    long countTemp;
    long score;
    int numShipBullets;
    int lives;
    long frequencyAB;
    long frequencyMA;
    long frequencyShield; 
    long frequencyHeart;
    long differenceX;
    long differenceY;
    int numCommon;
    int numMaster;
    int numUltimate;       
    bool createdGame;
    bool commonDead;
    bool masterDead;
    bool ultimateDead;
    bool shipDead;
    bool pause;
    int vCommon;
    int vMaster;
    int vUltimate;
    void collisionAliens();
    void collisionBullets();
    void collisionAlienBullets();
    void createExplosion();
    void createCommonAlienBullet(Alien* a);
    void moveAlienBullets();
    void shootAlienBullets();
    void shootMasterAlienBullets();
    void displayScore();
    void printHearts();
    void createMasterAlien(int nx);
    void createMasterAlienBullets(Alien* a);
    void createUltimateAlien(int nx);
    void createShield();
    void createHeart();
    void createGame();
    void createSacAlien();
    void createDevilAlien();
public slots:
    void handleTimer();
    void handleTimerTemp();
    void gameStart();
    //void fn();
};

#endif // MAINWINDOW_H
