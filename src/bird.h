#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <iostream>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f
struct bodyUserData{
    int label;
};
class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void press()=0;
    double getPositionX();
    double getPositionY();
    double  getVelocityX();
    double  getVelocityY();
    bool canmove;
    bool func;
    bool flied;

};

class Stone : public Bird{
public:
    Stone(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input):
        Bird(x,y,radius,timer,pixmap,world,scene,input){}
    virtual void press(){}

};

class Pig : public Bird{
public:
    Pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input):
        Bird(x,y,radius,timer,pixmap,world,scene,input){
            m_contacting = false;
            score = 0;
    }
    virtual void press(){}
    void startContact(){
        if(m_contacting == false){
            score +=1000;
            m_contacting = true;
         }
    }
/*    void endContact(){
        if(m_contacting == true ){
            m_contacting = false;
         }
    }
*/
    bool m_contacting ;
    int score;

};

class redbird : public Bird{
public:
    redbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input):
        Bird(x,y,radius,timer,pixmap,world,scene,input){}
    virtual void press();
};

class yellowbird : public Bird{
public:
    yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input):
        Bird(x,y,radius,timer,pixmap,world,scene,input){}
    virtual void press();
};

class greenbird : public Bird{
public:
    greenbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input):
        Bird(x,y,radius,timer,pixmap,world,scene,input){}
    virtual void press();
};

class bluebird : public Bird{
public:
    bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input):
        Bird(x,y,radius,timer,pixmap,world,scene,input){}
    virtual void press();
};

#endif // BIRD_H
