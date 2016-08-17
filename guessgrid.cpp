/***************************************************************************//**
 * @file
 ******************************************************************************/
#include "guessgrid.h"
#include "graphics.h"
#include "loadBMP.h"
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;

/***************************************************************************//**
 * @author Zac Christy
 *
 * @date Feb 4, 2016
 *
 * @par CSC300 - 2016
 *
 * @brief
 *    Member functions for GuessGrid class, handles player interaction
 *    and display of letters and whether they have been guessed.
 *
 * @param[in] <name> - <description>
 ******************************************************************************/

//NOT making right filename
void GuessGrid :: drawGrid()
{
    //const float color[3] = {3.0, 3.0, 3.0};
    //const float color2[3] = {2.0, 2.0, 0.0};
    int sectornum;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {

            sectornum = 25 + (i*25)+(18 + j);
            if(guessed[i][j])
            {
                DrawSector(sectornum, data[29]);
            }
            else
            {
                DrawSector(sectornum, data[i*5+j]);
            }
        }

    }
}

///ouputs the letter clicked on in the grid
char GuessGrid :: clicked(int x, int y)
{
    int tilewidth = (glutGet(GLUT_WINDOW_WIDTH) / 25);
    int tileheight = (glutGet(GLUT_WINDOW_HEIGHT) / 10);

    //Here.
    int xtile = (x / tilewidth) - 18;
    int ytile = (y / tileheight) - 1;

    if (xtile > 4 || ytile > 5 || xtile < 0 || ytile < 0)
        return '~';
    else if (guessed[ytile][xtile] == false) {
        //guessed[ytile][xtile] = true;
        glutPostRedisplay();
        return guesses[ytile][xtile];
    }
    return '~';
}


///function returns if space is guessed
bool GuessGrid :: isGuessed(int x, int y)
{
    if ( x <= 4 && x >= 0 && y <= 5 && y >= 0)
        return guessed[x][y];
    else
        return true;
}

///function to set space as guessed
void GuessGrid :: guess(int x, int y)
{
    int tilewidth = (glutGet(GLUT_WINDOW_WIDTH) / 25);
    int tileheight = (glutGet(GLUT_WINDOW_HEIGHT) / 10);

    //Here.
    int xtile = (x / tilewidth) - 18;
    int ytile = (y / tileheight) - 1;

    if (xtile > 4 || ytile > 5 || xtile < 0 || ytile < 0)
        return;
    else
    {
        guessed[ytile][xtile] = true;
        glutPostRedisplay();
    }
}

///function to set space as not guessed
void GuessGrid :: unguess(int x, int y)
{
    guessed[x][y] = false;
}

void GuessGrid :: outputguessed()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << guessed[i][j] << " ";

        cout << endl;
    }

}

void GuessGrid :: resetBoard()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            guessed[i][j] = false;
        }
    }
    guessed[5][2] = false;
}


void GuessGrid :: loadbmps()
{
    char filename[12] = "WheelA.bmp";
    chdir("Letters");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            filename[5] = guesses[i][j];
            int rows = 52, cols = 40;
            loadBMP(filename, rows, cols, data[i*5+j]);
        }
    }
    chdir("..");
}
