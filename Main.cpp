#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <list>

using namespace std;

//for rand() method
#include <stdlib.h>

#include "Terminal.h"

bool gameOver = false;

#include "SpaceCraft.h"
#include "Asteroid.h"
#include "Bullet.h"

Terminal t = Terminal();

void paintLimits()
{
    //horizontal
    for (int i = 2; i < 115; i++)
    {
        t.gotoxy(i, 1);
        printf("%c", 205);
        t.gotoxy(i, 30);
        printf("%c", 205);
    }
    //vertical
    for (int i = 2; i < 30; i++)
    {
        t.gotoxy(1, i);
        printf("%c", 186);
        t.gotoxy(115, i);
        printf("%c", 186);
    }

    t.gotoxy(1, 1);
    printf("%c", 201);

    t.gotoxy(1, 30);
    printf("%c", 200);

    t.gotoxy(115, 1);
    printf("%c", 187);

    t.gotoxy(115, 30);
    printf("%c", 188);
}

void clean()
{
    for (int i = 1; i <= 30; i++)
    {
        t.gotoxy(1, i);
        printf("%*c", 117, 32);
    }
}

main()
{
    t.hideCursor();
    paintLimits();

    SpaceCraft sc = SpaceCraft(55, 27);

    Asteroid at = Asteroid();
    Asteroid at1 = Asteroid();
    Asteroid at2 = Asteroid();
    Asteroid at3 = Asteroid();
    Asteroid at4 = Asteroid();

    list<Bullet *> B;
    list<Bullet *>::iterator it;
    sc.paint();
    sc.paintHearts();

    while (!gameOver)
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 'c')
                B.push_back(new Bullet(sc.getX() + 2, sc.getY() - 1));
        }

        for (it = B.begin(); it != B.end(); it++)
        {
            if (!(*it)->move())
            {
                delete (*it);
                it = B.erase(it);
            }
        }

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