#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <iostream>

class _ball
{
  private:
    int x0,y0,x,y;
    double r,l,a,a0,omega;
  public:
    void put_x0(int);
    void put_y0(int);
    void put_x(int);
    void put_y(int);
    void put_r(double);
    void put_l(double);
    void put_a(double);
    void put_a0(double);
    void put_omega(double);
    int get_y0();
    int get_x();
    double get_r();
    double get_l();
    double get_a0();
    void draw();
    void clean();
    void change_pos(double);
};

void _ball::put_x0(int x0) {this->x0=x0;}

void _ball::put_y0(int y0) {this->y0=y0;}

void _ball::put_x(int x) {this->x=x;}

void _ball::put_y(int y) {this->x=y;}

void _ball::put_r(double r) {this->r=r;}

void _ball::put_l(double l) {this->l=l;}

void _ball::put_a(double a) {this->a=a;}

void _ball::put_a0(double a0) {this->a0=a0;}

void _ball::put_omega(double omega) {this->omega=omega;}

int _ball::get_y0() {return y0;}

double _ball::get_a0() {return a0;}

double _ball::get_l() {return l;}

double _ball::get_r() {return r;}

int _ball::get_x() {return x;}

void _ball::draw()
{
  circle(x,y,r);
  circle(x,y,r-1);
  circle(x,y,r-2);
  line(x0,y0,x,y);
  line(x0-1,y0,x-1,y);
  line(x0+1,y0,x+1,y);
}

void _ball::clean()
{
  setcolor(getbkcolor());
  draw();
  setcolor(1);
}
void _ball::change_pos(double t)
{
  clean();
  a=a0*cos(omega*t);
  x=x0+l*sin(a);
  y=y0+l*cos(a);
  draw();
}

int main()
{
  int gdriver=DETECT, gmode;
  initgraph(&gdriver,&gmode, "");
  setbkcolor(15);
  setcolor(1);
  const double g=180;
  const char n=5;
  char nA=2;
  _ball ball[n];

  for (int i=0; i<n; i++)
  {
    ball[i].put_l(300);
	ball[i].put_r(25);
	ball[i].put_x0(230+i*2*ball[i].get_r());
	ball[i].put_y0(30);
	ball[i].put_omega(sqrt(g/ball[i].get_l()));
	if (i<nA) ball[i].put_a0(-M_PI/6);
	else ball[i].put_a0(0);
	ball[i].put_a(ball[i].get_a0());
	ball[i].change_pos(0);
  }

  line(0,ball[0].get_y0()-1,getmaxx(),ball[0].get_y0()-1);
  line(0,ball[0].get_y0()-2,getmaxx(),ball[0].get_y0()-2);
  line(0,ball[0].get_y0()-3,getmaxx(),ball[0].get_y0()-3);
  char direction=1;

  for (double t=0; !kbhit(); t+=0.05)
  {
    for (int i=0; i<n; i++) ball[i].change_pos(t);
    if(nA!=n)
    {
      if(direction==1)
      {
        if(ball[nA].get_x()-ball[nA-1].get_x()<=
          ball[nA].get_r()+ball[nA-1].get_r())
	      {
	        direction=-1;
	        for(int i=n-1; i>=0; i--)
	        if (i>=n-nA) ball[i].put_a0(ball[0].get_a0());
	        else ball[i].put_a0(0);
	      }
      }
      else
      {
        if(ball[n-nA].get_x()-ball[n-nA-1].get_x()<=
          ball[n-nA].get_r()+ball[n-nA-1].get_r())
	      {
	        direction=1;
	        for(int i=0; i<n; i++)
	        if (i<nA) ball[i].put_a0(ball[n-1].get_a0());
	        else ball[i].put_a0(0);
	      }
	  }
    }
  }
  return 0;
}
