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
     static int h;  
     Snake()
     {
        length=3;
        a.resize(length);
        a[0].first=10;a[0].second=10;
        a[1].first=11;a[1].second=10;
        a[2].first=12;a[2].second=10;
        
     }
     void Draw()
     {
        for(int i=0;i<length;i++)
        {
            gotoxy(a[i].first,a[i].second);
            printf("x");
        }

     }
     void Move(int direction)
     {   if(abs(h-direction)==2) direction=h;
         h=direction;
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
};
class apple
{  
   int x,y;
   public:
   apple(Snake b)
   {
   an:x=rand()%31;
      y=rand()%31;
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
       cout<<"O";
   }
   int eat_apple(Snake b)
   {
       if(b.a[0].first==x && b.a[0].second==y)
       {
         return 1;
       }
       return 0;
   }
   void delete_apple(Snake b)
   {
      an: x=rand()%31;
      y=rand()%31;
      for(int i=0;i<b.length;i++)
      {
        if(x==b.a[i].first && y==b.a[i].second)
        {
            goto an;
        }
      }
   }
};
int Snake::h=-22;
int main(){
    Snake a;
    int direction=0;
    apple b(a);
    char t;
    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') direction = 2;
            if (t=='w') direction = 3;
            if (t=='d') direction = 0;
            if (t=='x') direction= 1;
        }
       
        system("cls");
      a.Draw();
      b.Draw();
      a.Move(direction);
      if(b.eat_apple( a))
      { a.up_length();
        b.delete_apple(a);
      }
      
        Sleep(50);
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
//move