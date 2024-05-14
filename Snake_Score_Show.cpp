#include<iostream>
#include<vector>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<cmath>

using namespace std;
void gotoxy( int column, int line );
class  Snake{
     int length;
     vector<pair<int,int>>a;
     public:
     int score=0; //them score=0
     static int h;
     Snake()
     {
        length=3;
        a.resize(length);
        a[0].first=10;a[0].second=10;
        a[1].first=11;a[1].second=10;
        a[2].first=12;a[2].second=10;
     }

     void Draw(pair <int,int> x)
     {
            gotoxy(x.first,x.second);
            cout<<" ";
            gotoxy(a[0].first,a[0].second);
            printf("x");


     }
     void Move(int direction,pair<int,int> & x)
     {   if(abs(h-direction)==2) direction=h;
         h=direction;
         x.first=a[length-1].first;
         x.second=a[length-1].second;
         for(int i=length-1;i>0;i--)
         {
            a[i]=a[i-1];
         }
         if(direction==0)  a[0].first=a[0].first+1;
         if(direction==1)  a[0].second=a[0].second+1;
         if(direction==2)  a[0].first=a[0].first-1;
         if(direction==3)  a[0].second=a[0].second-1;
     }
     void up_length()
     {
        if(a[length-1].first==a[length-2].first)
        {
            if(a[length-1].second<a[length-2].second)
            {
                length++;
                a[length-1].first=a[length-2].first;
                a[length-1].second=a[length-2].second-1;
            }
            else {
                 length++;
                a[length-1].first=a[length-2].first;
                a[length-1].second=a[length-2].second+1;
            }

        }
        else {
             if(a[length-1].first<a[length-2].first)
            {
                length++;
                a[length-1].first=a[length-2].first-1;
                a[length-1].second=a[length-2].second;
            }
            else{
                length++;
                a[length-1].first=a[length-2].first+1;
                a[length-1].second=a[length-2].second;
            }
        }
     }



     friend class apple;
     friend class border;
};
class apple
{
   int x,y;
   public:
   apple(Snake b)
   {
   an:x=rand()%72+1;
      y=rand()%17+1;
      for(int i=0;i<b.length;i++)
      {
        if(x==b.a[i].first && y==b.a[i].second)
        {
            goto an;
        }
      }


   }
   void Draw()
   {
       gotoxy(x,y);
       cout<<"0";
   }
   int eat_apple(Snake& b)  //truyen tham chieu toi doi tuong Snake
   {
       if(b.a[0].first==x && b.a[0].second==y)
       {
        b.score+=1;
         return 1;
       }
       return 0;
   }
   void delete_apple(Snake b)
   {  gotoxy(x,y);
      cout<<" ";
      an: x=rand()%72+1;
      y=rand()%17+1;
      for(int i=0;i<b.length;i++)
      {
        if(x==b.a[i].first && y==b.a[i].second)
        {
            goto an;
        }
      }
   }

};
class border{

  public:
  void Draw()
  {
    int i=0;int j=0;
    for( i=0,j=0;j<20;j++)
    {  gotoxy(i,j);
        cout<<"@";
    }

    for(i=74,j=0;j<20;j++)
    {   gotoxy(i,j);
       cout<<"@";
    }
    for(i=0,j=0;i<75;i++)
    {   gotoxy(i,j);
        cout<<"@";
    }
    for(i=0,j=20;i<75;i++)
    {    gotoxy(i,j);
        cout<<"@";
    }

  }
  int check_border(Snake b)
  {
        if(b.a[0].first==74 || b.a[0].first==0 || b.a[0].second==0 || b.a[0].second==19)
       {
         return 1;
       }
       return 0;
  }

};

void showScore(const Snake& x); //them ham showScore
int Snake::h=-22;
int main(){

    Snake a;
    int direction=0;
    apple b(a);
    char t;
    border c;
    pair<int,int> x(100,100);
    c.Draw();

    while (1){

        if (kbhit()){
            t = getch();
            if (t=='a') direction = 2;
            if (t=='w') direction = 3;
            if (t=='d') direction = 0;
            if (t=='s') direction= 1;
        }
      if(c.check_border(a))
      {
          system("cls");
          gotoxy(50,5);
          cout<<" Game over :)) ";
          break;
      }

      a.Draw(x);
      b.Draw();
      c.Draw();
      showScore(a);
      a.Move(direction,x);

      if(b.eat_apple( a))
      { a.up_length();
        b.delete_apple(a);
      }

        Sleep(150);
    }
}
void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }
  
//them ham showScore
void showScore(const Snake& x) {
    gotoxy(55, 1);
    cout << "Score: " << x.score;
}
