#include <windows.h>
#include <conio.h>

using namespace std;

class Terminal
{
private:
    const HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

public:
    Terminal() {}

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
};
