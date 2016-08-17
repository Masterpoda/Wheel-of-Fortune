/***************************************************************************//**
 * @file
 ******************************************************************************/
#include <iostream>
#include "GL/glut.h"

/// MouseClicked enum
enum MouseClicked
{
   RIGHT_CLICKED = 1,
   LEFT_CLICKED = 2,
};

/***************************************************************************//**
 * @class Mouse
 *
 * @brief
 *    This class keeps track of mouse information.
 *
 * @par Description
 *    Keeps the mouse state between events.
 ******************************************************************************/
class Mouse
{
   bool leftDown;					  /*!< Checks if left mouse button is down*/
   bool rightDown;			    	 /*!< Checks if right mouse button is down*/
   int clicked;							      /*!< Checks if mouse mas clicked*/
   int downX;						     /*!< X-coordinate of the button press*/
   int downY;						     /*!< Y-coordinate of the button press*/

public:

   Mouse(){}						 	        /*!< Constructor for the class*/
   ~Mouse(){}						     		 /*!< Destructor for the class*/

   void mouseClick(int button, int state, int x, int y);  /*!< Function to track
    a mouse click state and location*/
   void mouseDrag(int x, int y);						  /*!< Function to track
    when the mouse is dragged*/
   int mouseClicked() { return clicked ; }				  /*!< Function for when
    mouse if clicked*/
};
