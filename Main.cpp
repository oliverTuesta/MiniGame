#include <stdio.h>
#include <windows.h>
#include <conio.h>

//for rand() method
#include <stdlib.h>

const HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

bool gameOver = false;

void gotoxy(int x, int y)
{
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = false;
    cci.dwSize = 10;
    SetConsoleCursorInfo(hCon, &cci);
}

void paintLimits()
{
    //horizontal
    for (int i = 2; i < 115; i++)
    {
        gotoxy(i, 1);
        printf("%c", 205);
        gotoxy(i, 30);
        printf("%c", 205);
    }
    //vertical
    for (int i = 2; i < 30; i++)
    {
        gotoxy(1, i);
        printf("%c", 186);
        gotoxy(115, i);
        printf("%c", 186);
    }

    gotoxy(1, 1);
    printf("%c", 201);

    gotoxy(1, 30);
    printf("%c", 200);

    gotoxy(115, 1);
    printf("%c", 187);

    gotoxy(115, 30);
    printf("%c", 188);
}

void clean()
{
    for (int i = 1; i <= 30; i++)
    {
        gotoxy(1, i);
        printf("%*c", 117, 32);
    }
}

class SpaceCraft
{
    int x, y;
    int hearts;

    void dead();
    void remove();

public:
    SpaceCraft(int _x, int _y, int hearts);
    SpaceCraft();
    void move();
    void paintHearts();
    void decreaseHearts();
    void paint();
    int getX();
    int getY();
};

SpaceCraft::SpaceCraft() {}

SpaceCraft::SpaceCraft(int _x, int _y, int _hearts)
{
    x = _x;
    y = _y;
    hearts = _hearts;
}


int SpaceCraft::getX() { return x; }

int SpaceCraft::getY() { return y; }

void SpaceCraft::dead()
{

    remove();
    gotoxy(x, y);
    printf("  **   ");
    gotoxy(x, y + 1);
    printf(" ****");
    gotoxy(x, y + 2);
    printf("  **");
    Sleep(200);

    gotoxy(x, y);
    printf(" * ** * ");
    gotoxy(x, y + 1);
    printf("  ****");
    gotoxy(x, y + 2);
    printf(" * ** * ");
    Sleep(200);
    gameOver = true;
}

void SpaceCraft::paint()
{
    gotoxy(x, y);
    printf("  %c", 30);

    gotoxy(x, y + 1);
    printf(" %c%c%c", 40, 207, 41);

    gotoxy(x, y + 2);
    printf("%c%c %c%c", 30, 190, 190, 30);
}

void SpaceCraft::remove()
{
    gotoxy(x, y);
    printf("     ");

    gotoxy(x, y + 1);
    printf("    ");

    gotoxy(x, y + 2);
    printf("     ");
}

void SpaceCraft::move()
{
    if (kbhit())
    {
        char pressed = getch();
        remove();
        switch (pressed)
        {
        case LEFT:
            if (x > 2)
                x--;
            break;
        case RIGHT:
            if (x < 110)
                x++;
            break;
        case UP:
            if (y > 2)
                y--;
            break;
        case DOWN:
            if (y < 27)
                y++;
            break;
        }
        paint();
    }
}

void SpaceCraft::paintHearts()
{

    int i;
    for (i = 0; i < hearts; i++)
    {
        gotoxy(117, 2 + i);
        printf("%c", 3);
    }
    for (int j = i; j < 5; j++)
    {
        gotoxy(117, 2 + i);
        printf("   ");
    }
}
void SpaceCraft::decreaseHearts()
{
    SpaceCraft::hearts--;
    paintHearts();
    if (hearts == 0)
    {
        dead();
        clean();
    }
}

class Asteroid
{
    int x, y;

    void reset()
    {
        x = rand() % 107 + 4;
        y = 4;
    }

public:
    Asteroid();
    void paint();
    void move();
    void collision(class SpaceCraft &sc);
};

Asteroid::Asteroid()
{
    x = rand() % 107 + 4;
    y = rand() % 6 + 4;
}
void Asteroid::paint()
{
    gotoxy(x, y);
    printf("%c", 184);
}
void Asteroid::move()
{
    gotoxy(x, y);
    printf(" ");
    y++;
    if (y > 29)
    {
        reset();
    }
    Asteroid::paint();
}

void Asteroid::collision(class SpaceCraft &sc)
{
    if (x >= sc.getX() + 1 && x <= sc.getX()+3 && (y == sc.getY() + 1 || y == sc.getY() + 2))
    {
        gotoxy(sc.getX(), sc.getY());
        sc.decreaseHearts();
        reset();
    }
}

main()
{
    hideCursor();
    paintLimits();

    SpaceCraft sc = SpaceCraft(55, 27, 4);

    Asteroid at = Asteroid();
    Asteroid at1 = Asteroid();
    Asteroid at2 = Asteroid();
    Asteroid at3 = Asteroid();
    Asteroid at4 = Asteroid();

    sc.paint();
    sc.paintHearts();

    while (!gameOver)
    {

        sc.move();

        at.move();
        at.collision(sc);

        at1.move();
        at1.collision(sc);

        at2.move();
        at2.collision(sc);

        at3.move();
        at3.collision(sc);

        at4.move();
        at4.collision(sc);

        Sleep(20);
    }
    clean();
    _getch();

    return 0;
}