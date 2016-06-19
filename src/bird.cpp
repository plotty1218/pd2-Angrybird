#include "bird.h"
#include "mainwindow.h"
Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,int input):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);
    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodyUserData* myStruct = new bodyUserData;
    myStruct->label = input;
    bodydef.userData = myStruct;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    scene->addItem(&g_pixmap);

    //i add
    canmove = false;
    func = false;
    flied = false;
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
double Bird::getPositionX(){
    return g_body->GetPosition().x;
}
double Bird::getPositionY(){
    return g_body->GetPosition().y;
}
void yellowbird::press()
{
    setLinearVelocity(b2Vec2(5,-5));
}

void bluebird::press()
{
    setLinearVelocity(b2Vec2(0,0));
}

void greenbird::press()
{
    this->setLinearVelocity(b2Vec2(-5,5));
}

void redbird::press()
{
}
