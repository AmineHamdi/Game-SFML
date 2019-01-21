#include<SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct Point{int x; int y;}a[4]={{1,0},{1,1},{1,2},{1,3}} , copi_a[4];

Point form[7][4]=
{
 {{1,0},{1,1},{1,2},{1,3}},// I
 {{0,1},{1,1},{1,2},{2,2}},
 {{0,1},{1,1},{2,1},{1,2}},
 {{0,0},{1,0},{1,1},{1,2}},
 {{0,1},{1,1},{0,2},{1,2}},
 {{0,2},{1,1},{1,2},{2,1}},
 {{1,0},{1,1},{1,2},{2,0}} // z
};

const int L= 20;
const int C= 10;

int Tab[L][C]={0};

bool verif()
{
  for(int i=0; i<4 ; i++)
  {
    if(a[i].x < 0 || a[i].x >=C || a[i].y >= L) return 0;
    if(Tab[a[i].y][a[i].x] != 0) return 0;
  }
 return 1;
}


int main()
{
  srand(time(0));
  int dx=0;
  bool Rt =false;
  float timer = 0 , delay = 0.5;

 RenderWindow window(VideoMode(400,600),"titris_Amine_Tunis ^_^");
 Texture t,t1;
 t1.loadFromFile("images/BackG.png");
 t.loadFromFile("images/tiles.png");
 Sprite s(t), back(t1);

int color=1;

Clock clock;
 while(window.isOpen())
 {

  float t=clock.getElapsedTime().asSeconds();
   clock.restart();
   timer += t;

  Event e;
  while(window.pollEvent(e))
  {
    if(e.type == Event::Closed) window.close();
    if(e.type == Event:: KeyPressed)

      if(e.key.code == Keyboard::Up) Rt=true;
      else if(e.key.code == Keyboard::Left) dx=-1;
      else if(e.key.code == Keyboard::Right) dx=1;

  }

if(Keyboard::isKeyPressed(Keyboard::Down)) delay=0.1;

//----------MOVE------------
 for(int i=0;i<4;i++)  {copi_a[i]=a[i] ; a[i].x += dx;}
 if(!verif())
 {
    for(int i=0;i<4; i++)
      a[i]=copi_a[i];
  }
//------------rotaion---------
if(Rt)
{
  Point pt=a[1];
  for(int i=0;i<4;i++)
  {
    int x = a[i].y - pt.y;
    int y = a[i].x - pt.x;
    a[i].x = pt.x - x;
    a[i].y = pt.y + y;
  }
  if(!verif())
   {
     for(int i=0;i<4; i++)
       a[i]=copi_a[i];
   }
}
//-----------Down------------
if(timer > delay)
{
  for(int i=0; i<4 ; i++ )
  {
    copi_a[i]=a[i];
    a[i].y +=1;
  }
  if(!verif())
   {
     for(int i=0;i<4;i++)
     {
       Tab[copi_a[i].y][copi_a[i].x]=color;
     }
     color= 1 + rand()%7;
     int n=rand()% 7;
     for(int i=0;i<4;i++)
     {
       a[i].x=form[n][i].x;
       a[i].y=form[n][i].y;
     }
   }

  timer = 0;
}
//---------Verifier ligne----------
int max=L-1;
for(int i=L-1 ; i>0 ; i--)
{
  int compt=0;
  for(int j=0 ; j<C ;j++)
     {
        if(Tab[i][j] != 0) compt++;
        Tab[max][j]=Tab[i][j];
     }
     if(compt<C)
     max--;
}
 //--------------Building---------

 window.clear(Color::Black);
 window.draw(back);
 for(int i=0;i<L;i++)
   for(int j=0;j<C;j++)
  {
    if(Tab[i][j] == 0) continue;
    s.setTextureRect(IntRect(Tab[i][j]*18,0,18,18));//color
    s.setPosition(j*18,i*18);
    s.move(24,24);
    window.draw(s);
  }

   dx=0; Rt=false; delay=0.5;


   for(int i=0;i<4;i++)
   {
     s.setTextureRect(IntRect(color*18,0,18,18));//color
     s.setPosition(a[i].x*18,a[i].y*18);
     s.move(24,24);
     window.draw(s);
   }
   window.display();
 }
return 0;
}
