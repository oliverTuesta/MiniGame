class Asteroid
{
    int x, y;

    Terminal t;

    void reset()
    {
        x = rand() % 107 + 4;
        if (x % 2 == 0)
            x++;
        y = 4;
    }

public:
    Asteroid();
    void paint();
    void move();
    void collision(class SpaceCraft &sc);
    int getX() { return x; }
    int getY() { return y; }
};

Asteroid::Asteroid()
{
    x = rand() % 105 + 4;
    if (x % 2 == 0)
        x++;
    y = rand() % 10 + 4;
}
void Asteroid::paint()
{
    t.gotoxy(x, y);
    printf("%c", 184);
}
void Asteroid::move()
{
    t.gotoxy(x, y);
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
    if (x >= sc.getX() + 1 && x <= sc.getX() + 3 && (y == sc.getY() + 1 || y == sc.getY() + 2))
    {
        t.gotoxy(sc.getX(), sc.getY());
        if (sc.isDead())
            gameOver = true;
        else
            sc.paint();
        reset();
    }
}