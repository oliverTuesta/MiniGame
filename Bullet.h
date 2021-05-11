
class Bullet
{
    int x, y;
    Terminal t;

    void erase();

public:
    Bullet(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    boolean move();
};

boolean Bullet::move()
{
    erase();

    if (y > 1)
        y--;
    if (y == 2)
        return false;

    t.gotoxy(x, y);
    printf("*");
    return true;
}
void Bullet::erase()
{
    t.gotoxy(x, y);
    printf(" ");
}