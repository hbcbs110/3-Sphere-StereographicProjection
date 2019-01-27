#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    s=new s3s(this);
    setCentralWidget(s);
    s->setFixedSize(1024,768);
    setFixedSize(1024,768);
    connect(s,SIGNAL(setthetitle(char*)),this,SLOT(setmytitle(char*)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setmytitle(char *stts)
{
    setWindowTitle(QString(stts));
}
