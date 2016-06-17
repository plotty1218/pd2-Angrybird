#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    count = 1;
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
    itemList.push_back(new Barrier(30,4, 2.6, 2.4,QPixmap(":/barrier2.png").scaled(width()/8,height()/9),world,scene));
    itemList.push_back(new Barrier(30,6, 2.6, 2.4,QPixmap(":/barrier2.png").scaled(width()/8,height()/9),world,scene));
    itemList.push_back(new Barrier(5,6, 0.001, 0.001,QPixmap(":/stick.png").scaled(width()/13,height()/6),world,scene));


    // Create bird (You can edit here 出發x,出發y,地板高,高,寬)
    thisbird= new bluebird(5.0f,10.0f,0.40f,&timer,QPixmap(":/yellowbird.png").scaled(width()/16.0,height()/10.0),world,scene,1);
    itemList.push_back(new Stone(17.5f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene,2));
    itemList.push_back(new Stone(17.8f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene,2));
    pig = new Pig(22.0f,2.7f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene,0);
    itemList.push_back(thisbird);
    itemList.push_back(pig);

    myContactListenerInstance = new MyContactListener(pig);
    world->SetContactListener(myContactListenerInstance);
    score = new QGraphicsTextItem;
    score->setPos(100,80);
    score->setPlainText(QString::number(pig->score));
    scene->addItem(score);
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
        if(thisbird->flied == false)
            thisbird->canmove = true;
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(thisbird->canmove == true){
            thisbird->setLinearVelocity(b2Vec2(12,6));
            thisbird->func = true;
            thisbird->flied = true;
        }
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if((event->key() == Qt::Key_F && thisbird->func == true)){
            thisbird->press();
            thisbird->func = false;
            thisbird->canmove = false;
     }
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

void MainWindow::newbird()
{
    count++;

    switch (count) {
    case 2:
        delete thisbird;
        thisbird = new redbird(5.0f,10.0f,0.40f,&timer,QPixmap(":/redbird.png").scaled(width()/16.0,height()/10.0),world,scene,1);
        break;
    case 3:
        delete thisbird;
        thisbird = new bluebird(5.0f,10.0f,0.40f,&timer,QPixmap(":/bluebird.png").scaled(width()/16.0,height()/10.0),world,scene,1);
        break;
    case 4:
        delete thisbird;
        thisbird = new greenbird(5.0f,10.0f,0.40f,&timer,QPixmap(":/greenbird.png").scaled(width()/16.0,height()/10.0),world,scene,1);
        break;
    }

}
