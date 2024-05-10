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


};
int Snake::h=-22;
int main(){
    Snake a;
    int direction=0;
    
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
      a.Move(direction);
      
        Sleep(300);
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
//Snake