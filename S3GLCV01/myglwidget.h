#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QTimer>

#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

extern const double pi;
extern const double pi2;
extern const double p18;

class Matrix44
{
public:
    Matrix44();
    void setval(int x,int y,double _v);
    double getval(int x,int y);
    void transpose();
    double v[4][4];
    Matrix44& operator =(const Matrix44 &b);
    void ror(int t,double ang);
    void multm(Matrix44 &b);
    int xy[6][2];
};

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
    void seteyx(double _e,int sgn=1);
public slots:
    void callkeypress(QKeyEvent *ev);
    void callkeyup(QKeyEvent *ev);
    void letgo();
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
    bool down16[6];
    bool vdown;
    bool bdown;
    bool pdown;
    bool pudown;
    bool pddown;
    bool brldown;
    bool brrdown;
    int t1sp,t2sp,t3sp,lnw;
    int sa,sb,se;
    int sc,sd,sf;
    int mulrate;
    int esgn;
    double xrt,yrt,zrt;
    double cc,dd,ff;
    double aa,bb,ee;
    double sinaa,cosaa;
    double sinbb,cosbb;
    double sincc,coscc;
    double sindd,cosdd;
    double sinee,cosee;
    double sinff,cosff;
    double prodis;
    double pw,ph,eyx;
    vector <double> tt[3];
    char stts[256];
    Matrix44 totst;
    Matrix44 totrv;
    Matrix44 rrrr;
};

#endif // MYGLWIDGET_H
