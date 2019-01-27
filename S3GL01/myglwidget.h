#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QTimer>

#include <vector>
#include <cmath>

using namespace std;

extern const double pi;
extern const double pi2;
extern const double p18;

class s3s: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    s3s(QWidget* parent=NULL);
    void initializeGL();
    void paintGL();
    void resizeGL(int width,int height);
    void drawpic();
    void draweach(int x1,int x2,int x3);
    void gentt();
public slots:
signals:
    setthetitle(char*);
protected:
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    QTimer tm;
    double vangle;
    double cdis;
    bool sw1;
    bool sw2;
    bool sw3;
    bool adown;
    bool sdown;
    bool ddown;
    bool qdown;
    bool wdown;
    bool edown;
    bool updown;
    bool downdown;
    bool leftdown;
    bool rightdown;
    bool rdown;
    bool fdown;
    bool tdown;
    bool gdown;
    bool plusdown;
    bool mindown;
    bool mdown;
    bool ndown;
    bool jdown;
    bool kdown;
    int t1sp,t2sp,t3sp,lnw;
    int sc,sd,sf;
    int mulrate;
    double xrt,yrt;
    double cc,dd,ff;
    double sincc,coscc;
    double sindd,cosdd;
    double sinff,cosff;
    vector <double> tt[3];
    char stts[128];
};

#endif // MYGLWIDGET_H
