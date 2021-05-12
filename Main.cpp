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
#include "Game.h"

Terminal t;
Game g;

main()
{
    t.hideCursor();
    g.paintLimits();

    SpaceCraft sc = SpaceCraft(55, 27);

    list<Asteroid *> Asteroids;
    list<Asteroid *>::iterator itA;

    for (int i = 0; i < 3; i++)
    {
        Asteroids.push_back(new Asteroid());
    }

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
                it = B.erase(it);
            }
        }

        sc.move();

        for (itA = Asteroids.begin(); itA != Asteroids.end(); itA++)
        {
            (*itA)->move();
            (*itA)->collision(sc);
        }

        Sleep(20);
        if (g.levelUp())
            Asteroids.push_back(new Asteroid());
    }
    g.gameOver();
    _getch();
    _getch();
    _getch();
    _getch();

    return 0;
}