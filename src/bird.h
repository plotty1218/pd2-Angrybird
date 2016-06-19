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

class Bird : public GameItem
{
    friend class MainWindow;
public:
    Bird(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void press()=0;
    double getPositionX();
    double getPositionY();
    void deleteblue();
    bool bluebirdpress;
private:
    bool canmove;
    bool func;
    bool flied;
    Bird* bluebird1;
    Bird* bluebird2;
};

class Stone : public Bird{
public:
    Stone(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(id,x,y,radius,timer,pixmap,world,scene){}
    virtual void press(){}
};

class Pig : public Bird{
public:
    Pig(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(id,x,y,radius,timer,pixmap,world,scene){
        m_contacting = false;
    }
    virtual void press(){}
    void startContact();
    bool m_contacting ;
};

class redbird : public Bird{
public:
    redbird(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(id,x,y,radius,timer,pixmap,world,scene){}
    virtual void press();
};

class yellowbird : public Bird{
public:
    yellowbird(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(id,x,y,radius,timer,pixmap,world,scene){}
    virtual void press();
};

class greenbird : public Bird{
public:
    greenbird(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(id,x,y,radius,timer,pixmap,world,scene){}
    virtual void press();
};

class bluebird : public Bird{
public:
    bluebird(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(id,x,y,radius,timer,pixmap,world,scene){}
    virtual void press();

};

#endif // BIRD_H
