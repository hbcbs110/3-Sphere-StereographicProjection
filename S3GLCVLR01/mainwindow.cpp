#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    lr3d=true;
    tongj=0.2;
    s1=new s3s(this);
    s2=new s3s(this);
    //setCentralWidget(s);
    //s->setFixedSize(1600,900);
    //setFixedSize(1600,900);
    resize(1600,900);
    s1->setGeometry(0,0,width()/2,height());
    s2->setGeometry(width()/2,0,width()/2,height());
    s1->letgo();
    s2->letgo();
    s1->seteyx(tongj,-1);
    s2->seteyx(tongj,1);
    connect(s1,SIGNAL(setthetitle(char*)),this,SLOT(setmytitle(char*)));
    connect(s2,SIGNAL(setthetitle(char*)),this,SLOT(setmytitle(char*)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setmytitle(char *stts)
{
    setWindowTitle(QString(stts));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    s1->callkeypress(event);
    s2->callkeypress(event);
    if(event->key() == Qt::Key_Slash)
    {
        lr3d=!lr3d;
        lrresize();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    s1->callkeyup(event);
    s2->callkeyup(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    lrresize();
}

void MainWindow::lrresize()
{
    if(lr3d)
    {
        s1->seteyx(tongj,-1);
        s2->seteyx(tongj,1);
        s1->setGeometry(0,0,width()/2,height());
        s2->setGeometry(width()/2,0,width()/2,height());
        s1->show();
        s2->show();
    }else{
        //s2->hide();
        s1->seteyx(0.0,-1);
        s2->seteyx(0.0,1);
        s1->setGeometry(0,0,width(),height());
        s2->setGeometry(width(),height(),1,1);
    }
}
