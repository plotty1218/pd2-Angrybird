#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void press()=0;
    void startContact() { contact = true; }
    void endContact() { contact = false; }
    void render();
    bool canmove;
    bool func;
    bool contact;
};

class Stone : public Bird{
public:
    Stone(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void press(){}

};

class Pig : public Bird{
public:
    Pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void press(){}
};

class redbird : public Bird{
public:
    redbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void press(){}
};

class yellowbird : public Bird{
public:
    yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void press();
    bool canmove;
    bool func;
};

class greenbird : public Bird{
public:
    greenbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void press();
};

class bluebird : public Bird{
public:
    bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Bird(x,y,radius,timer,pixmap,world,scene){}
    virtual void press();
};

#endif // BIRD_H
