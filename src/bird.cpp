#include "bird.h"
#include "mainwindow.h"
Bird::Bird(int id,float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);
    // Create Body
    bodyUserData* Pigstruct = new bodyUserData;
    Pigstruct->ispig = true;
    Pigstruct->ID = id;
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = Pigstruct;
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
    canmove = false;
    func = false;
    flied = false;
    bluebirdpress = false;
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
    setLinearVelocity(b2Vec2(0,0));
}

void bluebird::press()
{
    this->bluebirdpress=true;
}

void greenbird::press()
{
    this->setLinearVelocity(b2Vec2(-5,5));
}

void redbird::press()
{
    this->setLinearVelocity(b2Vec2(5,-5));
}

void Bird::deleteblue(){
    delete bluebird1;
    delete bluebird2;
}
void Pig::startContact(){
    if(m_contacting == false)
        m_contacting = true;
}
