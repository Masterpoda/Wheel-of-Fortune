/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef _newButton_H_
#define _newButton_H_

#include "tile.h"

class newButton : public Tile
{

protected:
    std::string filename = "new.bmp";        /*!< contains the filename for the 
    buttons image*/
    unsigned char * data; 	        /*!< signifies the bitmap file being used*/
    int width = 54, height = 52;     /*!< specifies the width and height of the
     bitmap images*/
    int s = 217;			   /*!< specifies the location of the spin button*/
    float x1, y1, x2, y2; 				     /*!< location for the new button*/


public:
    newButton() {}   					  /*!< constructor for the new button*/
    
    ~newButton() {}   					   /*!< destructor for the new button*/

    void drawTile();  			    /*!< draws the tile in the correct sector*/

    void initposition();    /*!< specifies the initial position of the button*/
    
    void loadnewBMP(); 					  /*!< load a new bmp into the screen*/
    
    bool clicked(int x, int y);    /*!< checks if the button has been clicked*/
    
    void drawnew(); 				  /*!< draws the new bitmap to the screen*/
};

#endif
