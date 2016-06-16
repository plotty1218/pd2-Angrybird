#ifndef LAND_H
#define LAND_H

#include <gameitem.h>
#include <QGraphicsScene>

class Land : public GameItem
{
public:
    Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};
class Barrier : public Land{
public:
    Barrier(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):
        Land(x,y,w,h,pixmap,world,scene){}
};

#endif // LAND_H
