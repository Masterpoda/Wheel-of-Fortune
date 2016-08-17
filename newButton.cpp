/***************************************************************************//**
 * @file
 ******************************************************************************/
#include "newButton.h"
#include "graphics.h"
#include <unistd.h>
#include "loadBMP.h"



/***************************************************************************//**
 * @author Jeremy
 *
 *
 * @par Description
 *     This function uses the DrawSector function to draw the new button.
 *
 * @returns void
 ******************************************************************************/
void newButton :: drawTile()
{
    DrawSector(s, color);
}



/***************************************************************************//**
 * @author Jeremy
 *
 *
 * @par Description
 *     This function loads in the new BMP using the loadBMP function
 *
 * @returns void
 ******************************************************************************/
void newButton::loadnewBMP()
{
    int rows = 52, cols = 40;
    chdir("Letters");
    loadBMP(filename, rows, cols, data);
    chdir("..");
}



/***************************************************************************//**
 * @author Jeremy
 *
 *
 * @par Description
 *     This function draws the new button.
 *
 * @returns void
 ******************************************************************************/
void newButton ::drawnew()
{
    drawTexture(x1, y1, x2, y2, data, width, height);
}



/***************************************************************************//**
 * @author Jeremy
 *
 *
 * @par Description
 *     This function sets the initial position of the new button.
 *
 * @returns void
 ******************************************************************************/
void newButton :: initposition()
{
    x1 = 656;
    y1 = 100;
    x2 = x1 + 54;
    y2 = y1 - 52;

}



/***************************************************************************//**
 * @author Jeremy
 *
 *
 * @par Description
 *     This function checks if the button has been clicked and returns the state
 * of the button.
 *
 * @param[in] x - the x coordinate of the button
 * @param[in] y - the y coordinate of the button
 *
 * @returns true  returns true if the button is clicked
 * @returns false returns false if the button is not clicked
 ******************************************************************************/
bool newButton :: clicked(int x, int y)
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
