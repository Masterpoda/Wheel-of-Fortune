/*************************************************************************//**
 * @file 
 *
 * @mainpage Program 1 - Prog1WoF
 * 
 * @section CSC300 Data Structures
 *
 * @author Zac Christy, Jeremy Gamet, Adam Bollinger, Ryan Hinrichs
 * 
 * @date February 19, 2016
 * 
 * @par Professor: 
 *         Dr. Hinker
 * 
 * @par Course: 
 *         CSC100 - M001 - 10:00 a.m.
 * 
 * @par Location: 
 *         McLaury - Room 205
 *
 * @section program_section Program Information 
 * 
 * @details 
 * 
 * Generic Program Description:
 * 
 * This program is designed to allow the user to play a version of the 
 * popular game Wheel of Fortune using a variety of GUI displays on the
 * monitor. It uses mouse events as well as keyboard events to let the
 * user guess individual letters as well as attempt to guess the entire
 * puzzle at once.
 *
 * Detailed Program Description:
 * 
 * This program utilizes OpenGL and GLUT commands in tandem with team-
 * created structures and classes to create a GUI window for the user.
 * There are a variety of different classes that utilize bitmap images to 
 * create the user interface window and OpenGL-created bitmap images to display
 * text to the screen.
 *
 * The game consists of a guess grid and a puzzle board, with a variety of 
 * strings of text throughout the program displaying multiple different 
 * portions of information and data that the user needs throughout the game.
 *  It also includes a clickable spin button that generates a random value 
 * for the user which represents the amount of money they can earn by 
 * choosing a correct letter, as well as a BANKRUPT and LOSE A TURN options,
 * which increase the number of strikes for the user and in the case of 
 * BANKRUPT cause the user's wallet of available money to become 0.
 *
 * The game has few methods of finishing: if the user guesses the puzzle, 
 * fills in the entire puzzle with the individual letters, or accumulates
 * three strikes. Upon causing any of these three events, the puzzle allows 
 * the user to click the spin button again to start a new game with a new 
 * puzzle.
 *
 * This program utilizes a make file to increase ease of compilation for the
 * user.  Because of this, you are not required to type in all of the cpp or
 * input files, just the term "make".  This will create an executable entitled
 * "Wheel of Fortune".
 *
 * @par Usage: 
 * @verbatim  
 * c:\> make 
 * d:\> c:\bin\make
 * @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug If the window is resized, the bitmaps become pixelated and unreadable.
 * @bug **
 *
 * @todo **
 * 
 * @par Modifications and Development Timeline: 
 @verbatim 
 Date          Modification 
 ------------  -------------------------------------------------------------- 
 Jan 31, 2016  Week 1 - Begin first commits and gave all users access to the
 git repository, allowing everyone to clone the working repository into their
 local repository.
 Feb 07, 2016  Week 2 - Created the Draw Sector Function to allow for quick
 bitmap building.  Added clickable grid spaces for the guess grid. Began 
 working to display the gameboard for the user and created the game class.
 Feb 14, 2016  Week 3 - Fixed several bugs, created display strings for wallet
 and the spin values.  Made the strike bmp and created a background for the 
 game.  Final documentation and display tweaks were added.
 
 @endverbatim
 *
 *****************************************************************************/

// include files
#include <iostream>
#include <stdlib.h>
#include "util.h"
#include "graphics.h"
#include <GL/glut.h>



using namespace std;

/// OpenGL callback function prototypes
/// Display handler
void display( void );
/// Handler for reshape events
void reshape( int w, int h );
/// Handler for keyboard events
void keyboard( unsigned char key, int x, int y );
/// Handler for mouse click events
void mouseClick(int button, int state, int x, int y);
/// Handler for mouse motion (i.e. drag) events
void mouseMotion(int x, int y);
/// Displays letter clicked
void displayGuess(int x, int y);
///returns boolean value indicating if the value is a vowel
bool isVowel(char letter);

// other function prototypes
/// Function to do the initialization of the openGL event handlers
void initOpenGL( const char *filename, int nrows, int ncols);



/***************************************************************************//**
 * @author Paul Hinker
 *
 * @par Description:
 * A barebones main to demonstrate the use of OpenGL and it's callback
 * functionality.
 *
 * @param[in] argc - a value denoting the number of arguments declared in the
 * command line
 * @param[in] argv - a pointer array full of the character strings signifying
 * the files and function calls needed by the user
 *
 * @returns 0 program ran successful.
 * @returns 1 the program failed or there was an error.
 ******************************************************************************/
int main( int argc, char *argv[] )
{

  glutInit( &argc, argv );
  initOpenGL( argv[1], 520, 1000);

  // go into OpenGL/GLUT main loop, never to return
  glutMainLoop();

  // Keep the compiler from complaining
  return 0;
}


/***************************************************************************//**
 * Initialize a variety of glut callback functions
 *
 * @param[in] windowTitle - The title to place on the window
 * @param[in] nrows       - Number of pixels for the window height
 * @param[in] ncols       - Number of pixels for the window width
 ******************************************************************************/
///various commands to initialize OpenGL and GLUT
void initOpenGL( const char *windowTitle, int nrows, int ncols)
{
  //int imgCols = 0, imgRows = 0;
  // 32-bit graphics and single buffering
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

  glutInitWindowSize( 1000, 500 );  // initial window size
  glutInitWindowPosition( 100, 50 );   // initial window  position
  glutCreateWindow("");   // window title

  utilityCentral(Event(nrows, ncols));
  glClearColor( 0.0, 0.6, 0.3, 0.0 );         // use black for glClear command

  // callback routines
  glutDisplayFunc( display );   // how to redisplay window
  glutReshapeFunc( reshape );   // how to resize window
  glutKeyboardFunc( keyboard ); // how to handle key presses
  glutMouseFunc(mouseClick);          // how to handle mouse clicks
  glutMotionFunc(mouseMotion);        // how to handle mouse movements
}

/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/

///callback function that tells OpenGL how to redraw window
void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT);

  utilityCentral(Event());
  
  //insertChar(lastGuessedChar);

  glutSwapBuffers();
}

/******************************************************************************/

///callback function that tells OpenGL how to resize window
///note that this is called when the window is first created
void reshape( int w, int h )
{
  // how to project 3-D scene onto 2-D
  glMatrixMode( GL_PROJECTION );    // use an orthographic projection
  glLoadIdentity();         // initialize transformation matrix
  gluOrtho2D( 0.0, w, 0.0, h );
  glViewport( 0, 0, w, h );       // adjust viewport to new window
  glutPostRedisplay();
}

/******************************************************************************/

///callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
  if (key == 27) //escape key
    exit(0);

  utilityCentral(Event(key, x, y));
  //glutPostRedisplay();
}

///Transfer mouse click events to the central processing function
void mouseClick(int button, int state, int x, int y)
{
   utilityCentral(Event(button, state, x, y));

	string temp;
}

///Transfer mouse movement events to the central processing function
void mouseMotion(int x, int y)
{
  utilityCentral(Event(MOUSEDRAG, x, y));
  glutPostRedisplay();
}

