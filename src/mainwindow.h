#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>
#include <gameitem.h>
#include <land.h>
#include <bird.h>

namespace Ui {
class MainWindow;
}
class MyContactListener;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent *);
    void deletepig();
public slots:
    void newbird();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void quitgame();
    void restartgame();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    Bird* thisbird;
    int count;
    Pig * pig1 ;
    Pig * pig2 ;
    Pig * pig3 ;
    b2Fixture* GetFixtureA();
    b2Fixture* GetFixtureB();
    MyContactListener *myContactListenerInstance;
    QGraphicsTextItem* score;
    bool check1;
    bool check2;
    bool check3;
    QPushButton *quit;
    QPushButton *restart;
    Stone* stone1;
    Stone* stone2;
    QPoint p;
    double x1,y1,x2,y2,bluex1,bluey1;

};
class MyContactListener : public b2ContactListener
  {
public:
    MyContactListener(Pig* pig1,Pig* pig2,Pig* pig3):pig1(pig1),pig2(pig2),pig3(pig3){
        score=0;
    }
    void BeginContact(b2Contact* contact) {
      //check if fixture A was a bird
      bodyUserData* body1 = (bodyUserData*)contact->GetFixtureA()->GetBody()->GetUserData();
      bodyUserData* body2 = (bodyUserData*)contact->GetFixtureB()->GetBody()->GetUserData();
     if ( (body1->label == 0  && body2->label ==1)||(body1->label == 1  && body2->label == 0 )||
          (body1->label == 4  && body2->label ==1)||(body1->label == 1  && body2->label == 4 )){
            pig1->startContact();
            score++;
     }else if ( (body1->label == 2  && body2->label ==0)||(body1->label == 0  && body2->label == 2 )||
                (body1->label == 2  && body2->label ==4)||(body1->label == 4  && body2->label == 2 )){
            pig2->startContact();
            score++;
     }else if ( (body1->label == 3  && body2->label == 0 )||(body1->label == 0  && body2->label == 3 )||
                (body1->label == 3  && body2->label == 4 )||(body1->label == 4  && body2->label == 3 )){
            pig3->startContact();
            score++;
     }
    }
    int getScore(){
        return score;
    }
private:
    Pig * pig1 ;
    Pig * pig2 ;
    Pig * pig3 ;
    int score;
};
#endif // MAINWINDOW_H
