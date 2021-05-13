class Game
{
    Terminal t;

    int points = 0;
    int additionalPoints = 0;

public:
    void paintLimits();
    boolean levelUp();
    void gameOver();
    void addPoints() { additionalPoints += 100; };
    void clean();
};

void Game::paintLimits()
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

void Game::gameOver()
{

    points += additionalPoints;

    clean();

    t.gotoxy(20, 5);
    printf("  ___    __    __  __  ____    _____  _  _  ____  ____ \n");
    printf("%*c / __)  /__\\  (  \\/  )( ___)  (  _  )( \\/ )( ___)(  _ \\ \n", 20, ' ');
    printf("%*c( (_-. /(__)\\  )    (  )__)    )(_)(  \\  /  )__)  )   /\n", 20, ' ');
    printf("%*c \\___/(__)(__)(_/\\/\\_)(____)  (_____)  \\/  (____)(_)\\_)\n", 20, ' ');
    t.gotoxy(20, 10);
    printf("Points: %d            Destroyed asteroids: %d", points, additionalPoints / 100);
}

void Game::clean()
{
    for (int i = 1; i <= 30; i++)
    {
        t.gotoxy(1, i);
        printf("%*c", 117, 32);
    }
}

boolean Game::levelUp()
{
    points++;
    return (points % 150 == 0);
}