#include "myglwidget.h"

const double pi = acos(-1.0);
const double pi2 = acos(-1.0)*2.0;
const double p18 = acos(-1.0)/180.0;

s3s::s3s(QWidget *parent):
    QOpenGLWidget(parent),tm(this),
    sw1(false),sw2(false),sw3(false),
    adown(false),sdown(false),ddown(false),
    qdown(false),wdown(false),edown(false),
    updown(false),downdown(false),leftdown(false),
    rightdown(false),rdown(false),fdown(false),
    tdown(false),gdown(false),mdown(false),ndown(false),
    plusdown(false),mindown(false),jdown(false),kdown(false),
    t1sp(12),t2sp(12),t3sp(24),lnw(5),
    sc(0),sd(0),sf(0),xrt(0),yrt(0),mulrate(4)
{
    grabKeyboard();
    vangle=45.0;
    cdis=10.0;

    gentt();

    connect(&tm,SIGNAL(timeout()),this,SLOT(update()));
    tm.start(50);
}

void s3s::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(vangle,4.0/3.0,0.1,500);
    gluLookAt(0,0,cdis,0,0,0,0,1,0);
}

void s3s::paintGL()
{
    glRotatef(0.0 + (int(updown) - int(downdown)), 1, 0, 0);
    glRotatef(0.0 + (int(rightdown) - int(leftdown)), 0, 1, 0);
    xrt = xrt + int(updown) - int(downdown);
    yrt = yrt + int(rightdown) - int(leftdown);
    cdis = cdis+int(fdown)-int(rdown);
    vangle = vangle+(int(gdown)-int(tdown))*p18;
    sc = (sc + int(ddown) - int(adown) + 360)%360;
    sd = (sd + int(edown) - int(qdown) + 360)%360;
    sf = (sf + int(wdown) - int(sdown) + 360)%360;
    if(fdown or rdown or tdown or gdown)
    {
        glLoadIdentity();
        gluPerspective(vangle, 4.0/3.0, 0.1, 500.0);
        gluLookAt(0, 0, cdis, 0, 0, 0, 0, 1, 0);
        glRotatef(xrt, 1, 0, 0);
        glRotatef(yrt, 0, 1, 0);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lnw = lnw+(int(plusdown)-int(mindown));
    if(lnw<=0) lnw=1;
    glLineWidth(lnw);
    sprintf(stts,"sc=%d sd=%d sf=%d xag=%f yag=%f vag=%f dis=%f line=%d mul=%d sp=%d", sc, sd, sf, xrt, yrt, vangle,cdis,lnw,mulrate,t1sp);
    emit setthetitle(stts);
    mulrate = mulrate + int(ndown) - int(mdown);
    if(mulrate<=1) mulrate=1;
    if(jdown or kdown)
    {
        t1sp = t1sp + 2 * (int(kdown)-int(jdown));
        if(t1sp<=2) t1sp=2;
        t2sp = t1sp;
        t3sp = 2*t1sp;
        gentt();
    }
    drawpic();
}

void s3s::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-width/2,width/2,-height/2,height/2,-1,1);
    //glOrtho(-width/2,width/2,-height/2,height/2,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void s3s::drawpic()
{
    cc=sc*p18;
    dd=sd*p18;
    ff=sf*p18;

    sincc = sin(cc);
    coscc = cos(cc);
    sindd = sin(dd);
    cosdd = cos(dd);
    sinff = sin(ff);
    cosff = cos(ff);

    int i,j;
    for(i=0;i<=t2sp;++i)
    {
        if(sw1) break;
        for(j=0;j<=t3sp;++j)
        {
            draweach(-1,i,j);
        }
    }
    for(i=0;i<=t1sp;++i)
    {
        if(sw2) break;
        for(j=0;j<=t3sp;++j)
        {
            draweach(i,-1,j);
        }
    }
    for(i=0;i<=t1sp;++i)
    {
        if(sw3) break;
        for(j=0;j<=t2sp;++j)
        {
            draweach(i,j,-1);
        }
    }
}

void s3s::draweach(int x1, int x2, int x3)
{
    int i,n;
    double st1,st2,st3,ct1,ct2,ct3;
    double x,y,z,w,tmp;
    if(x1==-1)
    {
        n=t1sp*mulrate;
        glColor3f(0.5,0,0);
        glBegin(GL_LINE_LOOP);
        for(i=0;i<=n;++i)
        {
            tmp=(i*pi/double(n));
            st1 = sin(tmp);
            st2 = sin(tt[1][x2]);
            st3 = sin(tt[2][x3]);
            ct1 = cos(tmp);
            ct2 = cos(tt[1][x2]);
            ct3 = cos(tt[2][x3]);
            w = 1 - sincc * st1 * st2 * st3 - coscc * sindd * st1 * st2 * ct3 - coscc * cosdd * sinff * st1 * ct2 - coscc * cosdd * cosff * ct1;
            if(w==0) continue;
            x = (coscc * st1 * st2 * st3 - sincc * sindd * st1 * st2 * ct3 - sincc * cosdd * sinff * st1 * ct2 - sincc * cosdd * cosff * ct1) / w;
            y = (cosdd * st1 * st2 * ct3 - sindd * sinff * st1 * ct2 - sindd * cosff * ct1) / w;
            z = (cosff * st1 * ct2 - sinff * ct1) / w;
            glVertex3d(x,y,z);
        }
        glEnd();
    }
    else if(x2==-1)
    {
        n=t2sp*mulrate;
        glColor3f(0,0.5,0);
        glBegin(GL_LINE_LOOP);
        for(i=0;i<=n;++i)
        {
            tmp=(i*pi/double(n));
            st1 = sin(tt[0][x1]);
            st2 = sin(tmp);
            st3 = sin(tt[2][x3]);
            ct1 = cos(tt[0][x1]);
            ct2 = cos(tmp);
            ct3 = cos(tt[2][x3]);
            w = 1 - sincc * st1 * st2 * st3 - coscc * sindd * st1 * st2 * ct3 - coscc * cosdd * sinff * st1 * ct2 - coscc * cosdd * cosff * ct1;
            if(w==0) continue;
            x = (coscc * st1 * st2 * st3 - sincc * sindd * st1 * st2 * ct3 - sincc * cosdd * sinff * st1 * ct2 - sincc * cosdd * cosff * ct1) / w;
            y = (cosdd * st1 * st2 * ct3 - sindd * sinff * st1 * ct2 - sindd * cosff * ct1) / w;
            z = (cosff * st1 * ct2 - sinff * ct1) / w;
            glVertex3d(x,y,z);
        }
        glEnd();
    }
    else if(x3==-1)
    {
        n=t3sp*mulrate;
        glColor3f(0,0,0.5);
        glBegin(GL_LINE_LOOP);
        for(i=0;i<=n;++i)
        {
            tmp=(i*pi2/double(n));
            st1 = sin(tt[0][x1]);
            st2 = sin(tt[1][x2]);
            st3 = sin(tmp);
            ct1 = cos(tt[0][x1]);
            ct2 = cos(tt[1][x2]);
            ct3 = cos(tmp);
            w = 1 - sincc * st1 * st2 * st3 - coscc * sindd * st1 * st2 * ct3 - coscc * cosdd * sinff * st1 * ct2 - coscc * cosdd * cosff * ct1;
            if(w==0) continue;
            x = (coscc * st1 * st2 * st3 - sincc * sindd * st1 * st2 * ct3 - sincc * cosdd * sinff * st1 * ct2 - sincc * cosdd * cosff * ct1) / w;
            y = (cosdd * st1 * st2 * ct3 - sindd * sinff * st1 * ct2 - sindd * cosff * ct1) / w;
            z = (cosff * st1 * ct2 - sinff * ct1) / w;
            glVertex3d(x,y,z);
        }
        glEnd();
    }
}

void s3s::gentt()
{
    tt[0].clear();
    tt[1].clear();
    tt[2].clear();
    for(int i=0;i<=t1sp;i++)
    {
        tt[0].push_back(i*pi/double(t1sp));
        tt[1].push_back(i*pi/double(t1sp));
    }

    for(int i=0;i<=t3sp;i++)
    {
        tt[2].push_back(i*pi2/double(t3sp));
    }
}

void s3s::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_A) adown=true;
    if(ev->key() == Qt::Key_D) ddown=true;
    if(ev->key() == Qt::Key_Q) qdown=true;
    if(ev->key() == Qt::Key_E) edown=true;
    if(ev->key() == Qt::Key_S) sdown=true;
    if(ev->key() == Qt::Key_W) wdown=true;
    if(ev->key() == Qt::Key_R) rdown=true;
    if(ev->key() == Qt::Key_F) fdown=true;
    if(ev->key() == Qt::Key_T) tdown=true;
    if(ev->key() == Qt::Key_G) gdown=true;
    if(ev->key() == Qt::Key_M) mdown=true;
    if(ev->key() == Qt::Key_N) ndown=true;
    if(ev->key() == Qt::Key_J) jdown=true;
    if(ev->key() == Qt::Key_K) kdown=true;
    if(ev->key() == Qt::Key_Up) updown=true;
    if(ev->key() == Qt::Key_Down) downdown=true;
    if(ev->key() == Qt::Key_Left) leftdown=true;
    if(ev->key() == Qt::Key_Right) rightdown=true;
    if(ev->key() == Qt::Key_Period) plusdown=true;
    if(ev->key() == Qt::Key_Comma) mindown=true;
    if(ev->key() == Qt::Key_Backspace)
    {
        sc=0,sd=0,sf=0;
    }
    if(ev->key() == Qt::Key_Z) sw1=!sw1;
    if(ev->key() == Qt::Key_X) sw2=!sw2;
    if(ev->key() == Qt::Key_C) sw3=!sw3;
}

void s3s::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_A) adown=false;
    if(ev->key() == Qt::Key_D) ddown=false;
    if(ev->key() == Qt::Key_Q) qdown=false;
    if(ev->key() == Qt::Key_E) edown=false;
    if(ev->key() == Qt::Key_S) sdown=false;
    if(ev->key() == Qt::Key_W) wdown=false;
    if(ev->key() == Qt::Key_R) rdown=false;
    if(ev->key() == Qt::Key_F) fdown=false;
    if(ev->key() == Qt::Key_T) tdown=false;
    if(ev->key() == Qt::Key_G) gdown=false;
    if(ev->key() == Qt::Key_M) mdown=false;
    if(ev->key() == Qt::Key_N) ndown=false;
    if(ev->key() == Qt::Key_J) jdown=false;
    if(ev->key() == Qt::Key_K) kdown=false;
    if(ev->key() == Qt::Key_Up) updown=false;
    if(ev->key() == Qt::Key_Down) downdown=false;
    if(ev->key() == Qt::Key_Left) leftdown=false;
    if(ev->key() == Qt::Key_Right) rightdown=false;
    if(ev->key() == Qt::Key_Period) plusdown=false;
    if(ev->key() == Qt::Key_Comma) mindown=false;
}
