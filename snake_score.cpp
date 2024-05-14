#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <cmath>

using namespace std;

void gotoxy(int column, int line);

class Snake {
    int length;
    vector<pair<int, int>> snake;

public:
    int score = 0;
    static int h;

    Snake() {
        length = 3;
        snake.resize(length);
        snake[0].first = 10; snake[0].second = 10;
        snake[1].first = 9; snake[1].second = 10;
        snake[2].first = 8; snake[2].second = 10;
    }

    void Draw(pair<int, int> x) {
        gotoxy(x.first, x.second); // vi tri cua phan tu cuoi cung trong con ran
        cout << " ";
        for (const auto& body : snake) {
            gotoxy(body.first, body.second);
            cout << "x";
        }
    }

    void Move(int direction, pair<int, int>& x) {
        if (abs(h - direction) == 2) direction = h;
        h = direction;
        x.first = snake[length - 1].first;
        x.second = snake[length - 1].second;
        for (int i = length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        if (direction == 0)  snake[0].first = snake[0].first + 1;
        if (direction == 1)  snake[0].second = snake[0].second + 1;
        if (direction == 2)  snake[0].first = snake[0].first - 1;
        if (direction == 3)  snake[0].second = snake[0].second - 1;
    }

    void IncreasingLength() {
        pair<int, int> new_body;
        if (snake[length - 1].first == snake[length - 2].first) {
            if (snake[length - 1].second < snake[length - 2].second) {
                new_body = { snake[length - 1].first, snake[length - 1].second - 1 };
            }
            else {
                new_body = { snake[length - 1].first, snake[length - 1].second + 1 };
            }
        }
        else {
            if (snake[length - 1].first < snake[length - 2].first) {
                new_body = { snake[length - 1].first - 1, snake[length - 1].second };
            }
            else {
                new_body = { snake[length - 1].first + 1, snake[length - 1].second };
            }
        }
        snake.push_back(new_body);
        length++;
    }

    bool IsOnBody()
    {
        for (int i = 1; i < length; i++)
        {
            if (snake[0] == snake[i])
                return true;
        }
        return false;
    }

    friend class Food;
    friend class Border;
};

class Food {
private:
    int x, y;

public:
    Food(Snake snake_tmp) {
    an:
        x = rand() % 72 + 1;
        y = rand() % 17 + 1;
        for (int i = 0; i < snake_tmp.length; i++) {
            if (x == snake_tmp.snake[i].first && y == snake_tmp.snake[i].second) {
                goto an;
            }
        }
    }

    void Draw() {
        gotoxy(x, y);
        cout << "0";
    }

    bool IsOnFood(Snake& snake_tmp) {
        if (snake_tmp.snake[0].first == x && snake_tmp.snake[0].second == y) {
            snake_tmp.score += 1;
            return true;
        }
        return false;
    }

    void DeletingOldFood(Snake snake_tmp) {
        gotoxy(x, y);
        cout << " ";
        an:
        x = rand() % 72 + 1;
        y = rand() % 17 + 1;
        for (int i = 0; i < snake_tmp.length; i++) {
            if (x == snake_tmp.snake[i].first && y == snake_tmp.snake[i].second) {
                goto an;
            }
        }
    }
};

class Border {
public:
    void Draw() {
        for (int i = 0; i < 75; ++i) {
            gotoxy(i, 0);
            cout << "@";
            gotoxy(i, 20);
            cout << "@";
        }
        for (int j = 0; j < 21; ++j) {
            gotoxy(0, j);
            cout << "@";
            gotoxy(74, j);
            cout << "@";
        }
    }

    bool IsOnBorder(Snake snake_tmp) {
        if (snake_tmp.snake[0].first >= 74 || snake_tmp.snake[0].first <= 0 || 
            snake_tmp.snake[0].second <= 0 || snake_tmp.snake[0].second >= 20) {
            return 1;
        }
        return 0;
    }
};

void showScore(const Snake& snake_tmp) {
    gotoxy(76, 1);
    cout << "Score: " << snake_tmp.score;
}
int Snake::h = -22;

int main() {
    Snake s;
    int direction = 0;
    Food food(s);
    char t;
    Border border;
    pair<int, int> x(100, 100);
    border.Draw();

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') direction = 2;
            if (t == 'w') direction = 3;
            if (t == 'd') direction = 0;
            if (t == 's') direction = 1;
        }
        if (border.IsOnBorder(s)) {
            system("cls");
            gotoxy(50, 5);
            cout << " GAME OVER !!! ";
            break;
        }

        if (s.IsOnBody())
        {
            system("cls");
            gotoxy(50, 5);
            cout << " GAME OVER !!! ";
            break;
        }

        s.Draw(x);
        food.Draw();
        showScore(s);
        s.Move(direction, x);

        if (food.IsOnFood(s)) {
            s.IncreasingLength();
            food.DeletingOldFood(s);
        }

        Sleep(150);
    }
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}