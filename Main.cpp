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
    g.clean();
    list<Bullet *> Bullets;
    list<Bullet *>::iterator itB;
    sc.paint();
    sc.paintHearts();

    while (!gameOver)
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 'c' && Bullets.size() < 2)
                Bullets.push_back(new Bullet(sc.getX() + 2, sc.getY() - 1));
        }

        for (itB = Bullets.begin(); itB != Bullets.end(); itB++)
        {
            if (!(*itB)->move())
            {
                delete (*itB);
                itB = Bullets.erase(itB);
            }
        }

        sc.move();

        for (itA = Asteroids.begin(); itA != Asteroids.end(); itA++)
        {
            (*itA)->move();
            (*itA)->collision(sc);
        }

        Sleep(20);
        int p = 1;

        for (itA = Asteroids.begin(); itA != Asteroids.end(); itA++)
        {
            for (itB = Bullets.begin(); itB != Bullets.end(); itB++)
            {
                if ((*itA)->getX() == (*itB)->getX() &&
                    ((*itA)->getY() == (*itB)->getY() ||
                     (*itA)->getY() + 1 == (*itB)->getY()))
                {
                    t.gotoxy((*itA)->getX(), (*itA)->getY());
                    printf(" ");
                    delete (*itA);
                    itA = Asteroids.erase(itA);
                    g.addPoints();

                    t.gotoxy((*itB)->getX(), (*itB)->getY());
                    printf(" ");
                    delete (*itB);
                    itB = Bullets.erase(itB);
                }
            }
        }

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