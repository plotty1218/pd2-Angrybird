#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    itemList.push_back(new Land(16,1.6,32,3,QPixmap(":/GROUND.png").scaled(width(),height()/6.0),world,scene));
    itemList.push_back(new Barrier(17,4, 2.6, 2.4,QPixmap(":/barrier2.png").scaled(width()/8,height()/9),world,scene));
    itemList.push_back(new Barrier(5,4, 2.6, 3.4,QPixmap(":/stick.png").scaled(width()/13,height()/6),world,scene));


    // Create bird (You can edit here 出發x,出發y,地板高,高,寬)
    thisbird= new yellowbird(5.0f,10.0f,0.40f,&timer,QPixmap(":/yellowbird.png").scaled(width()/16.0,height()/10.0),world,scene);
    Bird* stone = new Stone(17.5f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene);
    Bird* stone1 = new Stone(17.8f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene);
    Bird* pig = new Pig(22.0f,2.7f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene);

    // Setting the Velocity
    itemList.push_back(thisbird);
    itemList.push_back(stone);
    itemList.push_back(stone1);
    itemList.push_back(pig);

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        thisbird->canmove = true;
        if(thisbird->func ==true){
            thisbird->press();
        }
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
       /* if(thisbird->canmove==true)
        {
            if(event->buttons() & Qt::LeftButton)
            {
                this->move(mapToParent(event->pos() - thisbird->offset));
            }
        }*/
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(thisbird->canmove == true){
            thisbird->setLinearVelocity(b2Vec2(10.1,5));
            thisbird->func = true;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{

    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
