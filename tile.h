/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef _Tile_H_
#define _Tile_H_

#include <string>
#include "GL/glut.h"

/***************************************************************************//**
 * @class Tile
 *
 * @brief
 *    This class designates an area of the GUI to be interacted
 *    with or displayed
 *
 * @par Description
 *    Holds the data concerning the space of the GUI
 *    This class acts as a virtual class for each of the derived
 *    game object classes, with base functions necessary for most
 *    of the other buttons
 ******************************************************************************/

class Tile
{
   /// The value of the sector for the tile to appear

protected:
   unsigned int s;
   float color[3] = {0.0f, 0.0f, 0.0f};
   float x1, y1, x2, y2;

public:
   /// Tile Default Constructor
   /// Requires no arguments to initialize the class
   Tile();


   /// Tile Destructor
   virtual ~Tile();

   /// Change the color of the tile to appear
   ///draw the tile onscreen
   virtual void drawTile() =0;

   ///Set the initial position of the Tile Object
   virtual void initposition() =0;

   ///Check if the Tile is clicked
   virtual bool clicked(int x, int y) =0;

};

#endif
