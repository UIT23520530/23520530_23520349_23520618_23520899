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
     pair<int,int> getSnakeHead()
     {
      return a[0];
     }
     int getSnakeLength()
     {
      return length;
     }
     vector<pair<int,int>> getSnake()
     {
      return a;
     }
     void incrementLength(int n) //increases length
     {
      length += n;
      a.resize(length);
      a[length-1].first=a[length-2].first;
      a[length-1].second=a[length-2].second;
     }


};
int Snake::h=-22;


class Food
{
    private:
    pair< int , int > coordinate;
    public:
    // int state = 1; // 1->normal, 0->eaten, set this to eaten when snake head have same coordinate as food || run CheckEaten each draw cycle
    void Draw()
    {
        gotoxy( coordinate.first, coordinate.second );
        printf ("O");
    }
    void Spawn( Snake a)
    {

        srand(a.getSnakeLength()); 
        int occupied = 1;
        
        while (occupied == 1)
        {
            pair< int , int > prev = coordinate;
            coordinate = { rand() % 104 + 1, rand() % 26 + 1}; //replace with game resolution
            for (int i=0; i < a.getSnakeLength(); i++)//
            {
                if ( a.getSnake()[i]!= coordinate || coordinate != prev )//
                {
                    occupied = 0;
                    break;
                }
            }
        }
        Draw();
    }
    
    int CheckEaten( Snake a)
    {
        if ( a.getSnakeHead() == coordinate )
        {
          return 1;
        }
        return 0;
    }
};

int main(){
    Snake a;
    Food f;
    f.Spawn(a);
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
      if(f.CheckEaten(a) == 1)
      {
        //player_score++;//
            a.incrementLength(1);//
            f.Spawn(a);
      }
      f.Draw();

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