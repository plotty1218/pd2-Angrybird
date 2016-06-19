#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <QGraphicsTextItem>
#include <QFont>
#include <QCursor>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    count = 1;
    check1 = true;
    check2 = true;
    check3 = true;
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
    itemList.push_back(new Barrier(29,4, 2.6, 2.4,QPixmap(":/barrier2.png").scaled(width()/8,height()/9),world,scene));
    itemList.push_back(new Barrier(29,6, 2.6, 2.4,QPixmap(":/barrier2.png").scaled(width()/8,height()/9),world,scene));
    itemList.push_back(new Barrier(5,6, 0.001, 0.001,QPixmap(":/stick.png").scaled(width()/13,height()/6),world,scene));
    // Create bird (You can edit here 出發x,出發y,地板高,高,寬)
    //thisbird= new yellowbird(5.0f,10.0f,0.40f,&timer,QPixmap(":/yellowbird.png").scaled(width()/16.0,height()/10.0),world,scene,0);
    newbird();
    stone1 = new Stone(17.5f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene,4);
    stone2 = new Stone(17.8f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene,4);
    itemList.push_back(stone1);
    itemList.push_back(stone2);
    pig1 = new Pig(22.0f,2.7f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene,1);
    pig2 = new Pig(10.0f,5.0f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene,2);
    pig3 = new Pig(29.0f,8.0f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene,3);
    itemList.push_back(thisbird);
    itemList.push_back(pig1);
    itemList.push_back(pig2);
    itemList.push_back(pig3);

    myContactListenerInstance = new MyContactListener(pig1,pig2,pig3);
    world->SetContactListener(myContactListenerInstance);
    score = new QGraphicsTextItem;
    score->setPos(50,35);
    score->setPlainText(QString::number(0));
    score->setFont(QFont("Courier", 30, QFont::Bold));
    scene->addItem(score);

    // Create the button, make "this" the parent
    quit = new QPushButton(this);
    quit->setGeometry(QRect(QPoint(50, 10),QSize(60, 20)));
    quit->setText("Quitgame");
    quit->show();
    connect(quit, SIGNAL (released()), this, SLOT (quitgame()));
    restart = new QPushButton(this);
    restart->setGeometry(QRect(QPoint(120, 10),QSize(60, 20)));
    restart->setText("Restart");
    restart->show();
    connect(restart, SIGNAL (released()), this, SLOT (restartgame()));

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
        if(thisbird->canmove==true){
            p = QCursor::pos();
            x1 = p.x()*(thisbird->g_worldsize.width()/thisbird->g_windowsize.width())-8.0;
            y1 = (thisbird->g_worldsize.height())- p.y() *((thisbird->g_worldsize.height()/thisbird->g_windowsize.height()))+3.5;
            //change the starting position and angle
            thisbird->g_body->SetTransform(b2Vec2(x1,y1),0);
            thisbird->g_body->SetGravityScale(-0.4);
        }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(thisbird->canmove == true){
            x2 = thisbird->getPositionX();
            y2 = thisbird->getPositionY();
            thisbird->g_body->SetGravityScale(1);
            thisbird->setLinearVelocity(b2Vec2(20-1.1*x2,15-1.1*y2));
            thisbird->func = true;
            thisbird->flied = true;
            thisbird->canmove = false;
        }
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if((event->key() == Qt::Key_A && thisbird->func == true)){
        thisbird->press();
        thisbird->func = false;
        thisbird->canmove = false;
     }
    if(event->key() == Qt::Key_S){
        newbird();
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
    score->setPlainText(QString::number(myContactListenerInstance->getScore()));
    if(pig1->m_contacting == true && check1 == true){
        check1 = false;
        delete pig1;
    }
    if(pig2->m_contacting == true && check2 == true){
        check2 = false;
        delete pig2;
    }
    if(pig3->m_contacting == true && check3 == true){
        check3 = false;
        delete pig3;
    }
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::newbird()
{
    switch (count) {
    case 1:
        thisbird = new yellowbird(5.0f,10.0f,0.40f,&timer,QPixmap(":/yellowbird.png").scaled(width()/16.0,height()/10.0),world,scene,0);
        break;
    case 2:
        delete thisbird;
        thisbird = new redbird(5.0f,10.0f,0.40f,&timer,QPixmap(":/redbird.png").scaled(width()/16.0,height()/10.0),world,scene,0);
        break;
    case 3:
        delete thisbird;
        thisbird = new bluebird(5.0f,10.0f,0.40f,&timer,QPixmap(":/bluebird.png").scaled(width()/16.0,height()/10.0),world,scene,0);
        break;
    case 4:
        delete thisbird;
        thisbird = new greenbird(5.0f,10.0f,0.40f,&timer,QPixmap(":/greenbird.png").scaled(width()/16.0,height()/10.0),world,scene,0);
        break;
    }
    count++;
}

void MainWindow::quitgame()
{
    emit quitGame();
    this->close();
}

void MainWindow::restartgame()
{
    if(check1==false){
        pig1 = new Pig(22.0f,2.7f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene,1);
        itemList.push_back(pig1);
        check1=true;
    }
    if(check2==false){
        pig2 = new Pig(10.0f,5.0f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene,2);
        itemList.push_back(pig2);
        check2=true;
    }
    if(check3==false){
        pig3 = new Pig(29.0f,8.0f,0.40f,&timer,QPixmap(":/pig.png").scaled(width()/16.0,height()/10.0),world,scene,3);
        itemList.push_back(pig3);
        check3=true;
    }
    delete myContactListenerInstance;
    myContactListenerInstance = new MyContactListener(pig1,pig2,pig3);
    world->SetContactListener(myContactListenerInstance);
    delete thisbird;
    count=1;
    newbird();
    delete stone1;
    delete stone2;
    stone1 = new Stone(17.5f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene,4);
    stone2 = new Stone(17.8f,4.5f,0.40f,&timer,QPixmap(":/stone.png").scaled(width()/16.0,height()/10.0),world,scene,4);
    itemList.push_back(stone1);
    itemList.push_back(stone2);
}
