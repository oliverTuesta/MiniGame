#include <stdio.h>
#include <windows.h>
#include <conio.h>

const HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

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

class SpaceCraft
{
    int x, y;
    int hearts;

public:
    SpaceCraft(int _x, int _y, int hearts);
    void paint();
    void remove();
    void move();
    void paintHearts();
};

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
    paintHearts();
}

void SpaceCraft::paintHearts()
{

    for (int i = 0; i < hearts; i++)
    {
        gotoxy(117, 2 + i);
        printf("%c", 3);
    }
}

SpaceCraft::SpaceCraft(int _x, int _y, int _hearts)
{
    x = _x;
    y = _y;
    hearts = _hearts;
}

main()
{
    hideCursor();
    paintLimits();

    SpaceCraft sc = SpaceCraft(55, 27, 5);

    sc.paint();
    sc.paintHearts();
    bool gameOver = false;

    while (!gameOver)
    {
        sc.move();
    }
    _getch();

    return 0;
}