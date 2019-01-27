#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    s=new s3s(this);
    setCentralWidget(s);
    //s->setFixedSize(1600,900);
    //setFixedSize(1600,900);
    resize(1600,900);
    connect(s,SIGNAL(setthetitle(char*)),this,SLOT(setmytitle(char*)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setmytitle(char *stts)
{
    setWindowTitle(QString(stts));
}
