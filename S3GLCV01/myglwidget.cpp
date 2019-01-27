#include "myglwidget.h"

const double pi = acos(-1.0);
const double pi2 = acos(-1.0)*2.0;
const double p18 = acos(-1.0)/180.0;

Matrix44::Matrix44()
{
    memset(v,0,sizeof(v));
    v[0][0]=1,v[1][1]=1;
    v[2][2]=1,v[3][3]=1;
    int n=0;
    for(int i=0;i<4;i++)
    {
        for(int j=i+1;j<4;j++)
        {
            xy[n][0]=i;
            xy[n][1]=j;
            ++n;
        }
    }
}

void Matrix44::setval(int x, int y, double _v)
{
    v[x][y]=_v;
}

double Matrix44::getval(int x, int y)
{
    return v[x][y];
}

void Matrix44::transpose()
{
    for(int i=0;i<4;i++)
    {
        for(int j=i+1;j<4;j++)
        {
            swap(v[i][j],v[j][i]);
        }
    }
}

Matrix44& Matrix44::operator =(const Matrix44 &b)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            v[i][j]=b.v[i][j];
        }
    }
    return *this;
}

void Matrix44::ror(int t, double ang)
{
    memset(v,0,sizeof(v));
    v[0][0]=1,v[1][1]=1;
    v[2][2]=1,v[3][3]=1;
    v[xy[t][0]][xy[t][0]]=cos(ang);
    v[xy[t][1]][xy[t][1]]=cos(ang);
    v[xy[t][0]][xy[t][1]]=-sin(ang);
    v[xy[t][1]][xy[t][0]]=sin(ang);
}

void Matrix44::multm(Matrix44 &b)
{
    double tmp[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            tmp[i][j]=v[i][0]*b.v[0][j]+v[i][1]*b.v[1][j]+v[i][2]*b.v[2][j]+v[i][3]*b.v[3][j];
        }
        for(int j=0;j<4;j++)
        {
            v[i][j]=tmp[i][j];
        }
    }
}

s3s::s3s(QWidget *parent):
    QOpenGLWidget(parent),tm(this),
    sw1(false),sw2(false),sw3(false),
    adown(false),sdown(false),ddown(false),
    qdown(false),wdown(false),edown(false),
    updown(false),downdown(false),leftdown(false),
    rightdown(false),rdown(false),fdown(false),
    tdown(false),gdown(false),mdown(false),ndown(false),
    plusdown(false),mindown(false),jdown(false),kdown(false),
    t1sp(12),t2sp(12),t3sp(24),lnw(5),sa(0),sb(0),se(0),
    sc(0),sd(0),sf(0),xrt(0),yrt(0),zrt(0),mulrate(4),prodis(0)
{
    grabKeyboard();
    vangle=45.0;
    cdis=20.0;
    for(int i=0;i<6;i++) down16[i]=false;
    vdown=false, bdown=false, pdown=false;
    pudown=false, pddown=false;
    brldown=false, brrdown=false;
    pw=16.0,ph=9.0,eyx=0,esgn=1;

    gentt();

    connect(&tm,SIGNAL(timeout()),this,SLOT(update()));
    tm.start(40);
}

void s3s::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(vangle,pw/ph,0.1,500);
    gluLookAt(eyx,0,cdis,0,0,0,0,1,0);
}

void s3s::paintGL()
{
    glRotatef(0.0 + (int(updown) - int(downdown)), 1, 0, 0);
    glRotatef(0.0 + (int(rightdown) - int(leftdown)), 0, 1, 0);
    glRotatef(0.0 + int(pudown) - int(pddown), 0, 0, 1);
    xrt = xrt + int(updown) - int(downdown);
    yrt = yrt + int(rightdown) - int(leftdown);
    zrt = zrt + int(pudown) - int(pddown);
    cdis = cdis+int(fdown)-int(rdown);
    vangle = vangle+(int(gdown)-int(tdown));
    sc = (sc + int(ddown) - int(adown) + 360)%360;
    sd = (sd + int(edown) - int(qdown) + 360)%360;
    sf = (sf + int(wdown) - int(sdown) + 360)%360;
    sa = (sa + int(down16[1]) - int(down16[0]) + 360)%360;
    sb = (sb + int(down16[3]) - int(down16[2]) + 360)%360;
    se = (se + int(down16[5]) - int(down16[4]) + 360)%360;
    eyx = eyx + (int(brrdown)-int(brldown))*0.05*esgn;
    if(fdown or rdown or tdown or gdown or brrdown or brldown)
    {
        glLoadIdentity();
        gluPerspective(vangle, pw/ph, 0.1, 500.0);
        gluLookAt(eyx, 0, cdis, 0, 0, 0, 0, 1, 0);
        glRotatef(xrt, 1, 0, 0);
        glRotatef(yrt, 0, 1, 0);
        glRotatef(zrt, 0, 0, 1);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lnw = lnw+(int(plusdown)-int(mindown));
    if(lnw<=0) lnw=1;
    glLineWidth(lnw);
    sprintf(stts,"a=%d b=%d c=%d d=%d e=%d f=%d xa=%.1f ya=%.1f za=%.1f va=%.1f dis=%.1f ln=%d mul=%d sp=%d prd=%.1f ex=%.2f", sa, sb, sc, sd, se, sf, xrt, yrt, zrt, vangle,cdis,lnw,mulrate,t1sp,prodis,fabs(eyx));
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
    if(vdown or bdown)
    {
        prodis= prodis + (int(bdown) - int(vdown))*0.1;
        if(prodis<0.0) prodis=0.0;
    }
    if(pdown) prodis=0;
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
    pw=width,ph=height;
    glLoadIdentity();
    gluPerspective(vangle, pw/ph, 0.1, 500.0);
    gluLookAt(eyx, 0, cdis, 0, 0, 0, 0, 1, 0);
    glRotatef(xrt, 1, 0, 0);
    glRotatef(yrt, 0, 1, 0);
    glRotatef(zrt, 0, 0, 1);
}

void s3s::drawpic()
{
    if(sa==0&&sb==0&&sc==0&&sd==0&&se==0&&sf==0)
    {
        totst.ror(0,0),totrv.ror(0,0);
    }
//    else if((0+(sa==0)+(sb==0)+(sc==0)+(sd==0)+(se==0)+(sf==0))==5)
//    {
//        totst.ror((sa!=0)*0+(sb!=0)*1+(sc!=0)*2+(sd!=0)*3+(se!=0)*4+(sf!=0)*5,(sa+sb+sc+sd+se+sf)*p18);
//        totrv=totst;totrv.transpose();
//    }
    rrrr.ror(0,0);
    if(down16[1] or down16[0]) rrrr.ror(0,(int(down16[1]) - int(down16[0]))*p18);
    if(down16[3] or down16[2]) rrrr.ror(1,(int(down16[3]) - int(down16[2]))*p18);
    if(ddown or adown) rrrr.ror(2,(int(ddown) - int(adown))*p18);
    if(edown or qdown) rrrr.ror(3,(int(edown) - int(qdown))*p18);
    if(down16[5] or down16[4]) rrrr.ror(4,(int(down16[5]) - int(down16[4]))*p18);
    if(wdown or sdown) rrrr.ror(5,(int(wdown) - int(sdown))*p18);
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
    totst.multm(rrrr);
    totrv=totst;
    totrv.transpose();
}

void s3s::draweach(int x1, int x2, int x3)
{
    int i,n;
    double st1,st2,st3,ct1,ct2,ct3;
    double x,y,z,w,tmp;
    double xt,yt,zt,wt;
    double epp=exp(prodis);
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
            w=ct1,x=st1*st2*st3,y=st1*st2*ct3,z=st1*ct2;
            xt=x*rrrr.v[0][0]+y*rrrr.v[0][1]+z*rrrr.v[0][2]+w*rrrr.v[0][3];
            yt=x*rrrr.v[1][0]+y*rrrr.v[1][1]+z*rrrr.v[1][2]+w*rrrr.v[1][3];
            zt=x*rrrr.v[2][0]+y*rrrr.v[2][1]+z*rrrr.v[2][2]+w*rrrr.v[2][3];
            wt=x*rrrr.v[3][0]+y*rrrr.v[3][1]+z*rrrr.v[3][2]+w*rrrr.v[3][3];
            x=xt*totst.v[0][0]+yt*totst.v[0][1]+zt*totst.v[0][2]+wt*totst.v[0][3];
            y=xt*totst.v[1][0]+yt*totst.v[1][1]+zt*totst.v[1][2]+wt*totst.v[1][3];
            z=xt*totst.v[2][0]+yt*totst.v[2][1]+zt*totst.v[2][2]+wt*totst.v[2][3];
            w=xt*totst.v[3][0]+yt*totst.v[3][1]+zt*totst.v[3][2]+wt*totst.v[3][3];
            if(w==1.0) continue;
            xt=x*epp/(epp-w),yt=y*epp/(epp-w),zt=z*epp/(epp-w);
            glVertex3d(xt,yt,zt);
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
            w=ct1,x=st1*st2*st3,y=st1*st2*ct3,z=st1*ct2;
            xt=x*rrrr.v[0][0]+y*rrrr.v[0][1]+z*rrrr.v[0][2]+w*rrrr.v[0][3];
            yt=x*rrrr.v[1][0]+y*rrrr.v[1][1]+z*rrrr.v[1][2]+w*rrrr.v[1][3];
            zt=x*rrrr.v[2][0]+y*rrrr.v[2][1]+z*rrrr.v[2][2]+w*rrrr.v[2][3];
            wt=x*rrrr.v[3][0]+y*rrrr.v[3][1]+z*rrrr.v[3][2]+w*rrrr.v[3][3];
            x=xt*totst.v[0][0]+yt*totst.v[0][1]+zt*totst.v[0][2]+wt*totst.v[0][3];
            y=xt*totst.v[1][0]+yt*totst.v[1][1]+zt*totst.v[1][2]+wt*totst.v[1][3];
            z=xt*totst.v[2][0]+yt*totst.v[2][1]+zt*totst.v[2][2]+wt*totst.v[2][3];
            w=xt*totst.v[3][0]+yt*totst.v[3][1]+zt*totst.v[3][2]+wt*totst.v[3][3];
            if(w==1.0) continue;
            xt=x*epp/(epp-w),yt=y*epp/(epp-w),zt=z*epp/(epp-w);
            glVertex3d(xt,yt,zt);
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
            w=ct1,x=st1*st2*st3,y=st1*st2*ct3,z=st1*ct2;
            xt=x*rrrr.v[0][0]+y*rrrr.v[0][1]+z*rrrr.v[0][2]+w*rrrr.v[0][3];
            yt=x*rrrr.v[1][0]+y*rrrr.v[1][1]+z*rrrr.v[1][2]+w*rrrr.v[1][3];
            zt=x*rrrr.v[2][0]+y*rrrr.v[2][1]+z*rrrr.v[2][2]+w*rrrr.v[2][3];
            wt=x*rrrr.v[3][0]+y*rrrr.v[3][1]+z*rrrr.v[3][2]+w*rrrr.v[3][3];
            x=xt*totst.v[0][0]+yt*totst.v[0][1]+zt*totst.v[0][2]+wt*totst.v[0][3];
            y=xt*totst.v[1][0]+yt*totst.v[1][1]+zt*totst.v[1][2]+wt*totst.v[1][3];
            z=xt*totst.v[2][0]+yt*totst.v[2][1]+zt*totst.v[2][2]+wt*totst.v[2][3];
            w=xt*totst.v[3][0]+yt*totst.v[3][1]+zt*totst.v[3][2]+wt*totst.v[3][3];
            if(w==1.0) continue;
            xt=x*epp/(epp-w),yt=y*epp/(epp-w),zt=z*epp/(epp-w);
            glVertex3d(xt,yt,zt);
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

void s3s::seteyx(double _e,int sgn)
{
    eyx=_e*sgn;
    esgn=sgn;
}

void s3s::callkeypress(QKeyEvent *ev)
{
    keyPressEvent(ev);
}

void s3s::callkeyup(QKeyEvent *ev)
{
    keyReleaseEvent(ev);
}

void s3s::letgo()
{
    releaseKeyboard();
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
    if(ev->key() == Qt::Key_V) vdown=true;
    if(ev->key() == Qt::Key_B) bdown=true;
    if(ev->key() == Qt::Key_P) pdown=true;
    if(ev->key() == Qt::Key_1) down16[0]=true;
    if(ev->key() == Qt::Key_2) down16[1]=true;
    if(ev->key() == Qt::Key_3) down16[2]=true;
    if(ev->key() == Qt::Key_4) down16[3]=true;
    if(ev->key() == Qt::Key_5) down16[4]=true;
    if(ev->key() == Qt::Key_6) down16[5]=true;
    if(ev->key() == Qt::Key_Up) updown=true;
    if(ev->key() == Qt::Key_Down) downdown=true;
    if(ev->key() == Qt::Key_Left) leftdown=true;
    if(ev->key() == Qt::Key_Right) rightdown=true;
    if(ev->key() == Qt::Key_Period) plusdown=true;
    if(ev->key() == Qt::Key_Comma) mindown=true;
    if(ev->key() == Qt::Key_PageUp) pudown=true;
    if(ev->key() == Qt::Key_PageDown) pddown=true;
    if(ev->key() == Qt::Key_BracketLeft) brldown=true;
    if(ev->key() == Qt::Key_BracketRight) brrdown=true;
    if(ev->key() == Qt::Key_Backspace)
    {
        sa=0,sb=0,se=0;
        sc=0,sd=0,sf=0;
        totst.ror(0,0);
        totrv.ror(0,0);
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
    if(ev->key() == Qt::Key_V) vdown=false;
    if(ev->key() == Qt::Key_B) bdown=false;
    if(ev->key() == Qt::Key_P) pdown=false;
    if(ev->key() == Qt::Key_1) down16[0]=false;
    if(ev->key() == Qt::Key_2) down16[1]=false;
    if(ev->key() == Qt::Key_3) down16[2]=false;
    if(ev->key() == Qt::Key_4) down16[3]=false;
    if(ev->key() == Qt::Key_5) down16[4]=false;
    if(ev->key() == Qt::Key_6) down16[5]=false;
    if(ev->key() == Qt::Key_Up) updown=false;
    if(ev->key() == Qt::Key_Down) downdown=false;
    if(ev->key() == Qt::Key_Left) leftdown=false;
    if(ev->key() == Qt::Key_Right) rightdown=false;
    if(ev->key() == Qt::Key_Period) plusdown=false;
    if(ev->key() == Qt::Key_Comma) mindown=false;
    if(ev->key() == Qt::Key_PageUp) pudown=false;
    if(ev->key() == Qt::Key_PageDown) pddown=false;
    if(ev->key() == Qt::Key_BracketLeft) brldown=false;
    if(ev->key() == Qt::Key_BracketRight) brrdown=false;
}
