
#include "spinButton.h"
#include "graphics.h"
#include <unistd.h>
#include "loadBMP.h"

void spinButton :: drawTile()
{
    DrawSector(s, color);
}

void spinButton::loadspinBMP()
{
    int rows = 52, cols = 40;
    chdir("Letters");
    loadBMP(filename, rows, cols, data);
    chdir("..");
}

int spinButton ::amountWon()
{
    int winnings = 0;
    srand(time(NULL));
    winnings = rand() % 12 - 1;
    if(winnings > 0)
        return 100 * winnings;
    return winnings;
}

void spinButton ::drawSpin()
{
    drawTexture(x1, y1, x2, y2, data, width, height);
}

// FIX THIS HERE FUNCTION
void spinButton :: initposition()
{

    x1 = 600;
    y1 = 100;
    x2 = x1 + 54;
    y2 = y1 - 52;

}

bool spinButton :: clicked(int x, int y)
{
    if(x > x1 && x < x2 )
    {
        if(glutGet(GLUT_WINDOW_HEIGHT) - y < y1 &&
           glutGet(GLUT_WINDOW_HEIGHT) - y > y2)
        {
            return true;
        }
    }
    return false;
}
