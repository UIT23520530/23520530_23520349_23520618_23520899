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
     pair<int, int> getSnakeHead()
     {
         return a[0];
     }


};
int Snake::h=-22;

class Border
{
    int width, height; //dai x rong man hinh
public:
    Border(int w = 104, int h = 26) //width is set to 4 times heigth cuz if not would look weird
    {
        width = w;
        height = h;
    }
    void Draw()
    {
        for (int i = 0; i < height + 2; i++) //height + 2 to account for added space for border character itself -> full playable space= widthxHeight
        {
            if (i == 0 || i == height + 1)// check if it's top or bottom row, if so, draw "="
            {
                for (int j = 0; j < width + 2; j++) 
                {
                    gotoxy(j, i);
                    cout << "=";
                }
            }
            else //if not top or bottom, draw sides
            {
                gotoxy(0, i);
                cout << "|";
                gotoxy(width + 1, i);
                cout << "|";
            }
        }
        
    }
    int detect_snake(Snake a) //output 1 if touched by snake, else output 0, must be run every draw cycle
    {
        pair<int, int> head = a.getSnakeHead();
        int head_collumn = head.first;
        int head_line = head.second;
        if (head_line == 0 || head_line == height + 1 || head_collumn == 0 || head_collumn == width + 1)
        {
            return 1;
        }
        return 0;
    }
    
};

int main(){
    Snake a;
    Border b;
    int direction=0;
    
    char t;
    while (1){
        if (_kbhit()){
            t = _getch();
            if (t=='a') direction = 2;
            if (t=='w') direction = 3;
            if (t=='d') direction = 0;
            if (t=='x') direction= 1;
        }
       
        system("cls");
      a.Draw();
      b.Draw();
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
//Snake_move