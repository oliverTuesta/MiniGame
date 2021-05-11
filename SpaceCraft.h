class SpaceCraft
{
private:
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

    Terminal t;

    int x, y;
    int hearts = 5;

    void dead();
    void remove();

public:
    SpaceCraft(int _x, int _y);
    SpaceCraft();
    void move();
    void paintHearts();
    boolean isDead();
    void paint();
    int getX();
    int getY();
};

SpaceCraft::SpaceCraft() {}

SpaceCraft::SpaceCraft(int _x, int _y)
{
    x = _x;
    y = _y;
}

int SpaceCraft::getX() { return x; }

int SpaceCraft::getY() { return y; }

void SpaceCraft::dead()
{

    remove();
    t.gotoxy(x, y);
    printf("  **   ");
    t.gotoxy(x, y + 1);
    printf(" ****");
    t.gotoxy(x, y + 2);
    printf("  **");
    Sleep(200);

    t.gotoxy(x, y);
    printf(" * ** * ");
    t.gotoxy(x, y + 1);
    printf("  ****");
    t.gotoxy(x, y + 2);
    printf(" * ** * ");
    Sleep(200);
}

void SpaceCraft::paint()
{
    t.gotoxy(x, y);
    printf("  %c", 30);

    t.gotoxy(x, y + 1);
    printf(" %c%c%c", 40, 207, 41);

    t.gotoxy(x, y + 2);
    printf("%c%c %c%c", 30, 190, 190, 30);
}

void SpaceCraft::remove()
{
    t.gotoxy(x, y);
    printf("     ");

    t.gotoxy(x, y + 1);
    printf("    ");

    t.gotoxy(x, y + 2);
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
        t.gotoxy(117, 2 + i);
        printf("%c", 3);
    }
    for (int j = i; j < 5; j++)
    {
        t.gotoxy(117, 2 + i);
        printf("   ");
    }
}
boolean SpaceCraft::isDead()
{
    SpaceCraft::hearts--;
    paintHearts();
    if (hearts == 0)
    {
        dead();
        return true;
    }
    return false;
}