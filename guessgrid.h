/***************************************************************************//**
 * @file
 ******************************************************************************/
#include <iostream>
#include <string>
#include "GL/glut.h"


typedef unsigned char byte;

/***************************************************************************//**
 * @class Guess Grid
 *
 * @brief
 *    This class designates an area of the GUI as the guess grid and
 *    handles the user interaction with the guesses
 *
 * @par Description
 *    Holds the data concerning the space of the GUI
 ******************************************************************************/

class GuessGrid
{
  /// an array containing the spaces character value
  const char guesses[6][5] =
  {
    {'A', 'B', 'C', 'D', 'E'},
    {'F', 'G', 'H', 'I', 'J'},
    {'K', 'L', 'M', 'N', 'O'},
    {'P', 'Q', 'R', 'S', 'T'},
    {'U', 'V', 'W', 'X', 'Y'},
    {'~', '~', 'Z', '~', '~'},
  };
  ///an array containing booleans describing if the spaces have been guessed
  bool guessed [6][5] =
  {
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {true, true, false, true, true}
  };
  ///an array containing the picture info in memory

  byte* data[30];

public:
  /// Constructor
  GuessGrid() {}
  /// Destructor
  ~GuessGrid() {

      for(int i=0; i < 30; i++)
          delete data[i];
  }

  /// Draws the guess grid
  void drawGrid();
  /// Takes in click info to see what has been clicked
  char clicked(int x, int y);
  /// Sets the height of one space
  void setHeight(float h);
  /// Sets the width of one space
  void setWidth(float w);
  /// Sets the x value of upper left coordinate
  void setX(float x);
  /// Sets the y value of upper right coordinate
  void setY(float y);
  /// Returns whether or not a space has been guessed
  bool isGuessed(int x, int y);
  /// Sets a space as 'guessed'
  void guess(int x, int y);
  /// Sets a space as 'Not Guessed'
  void unguess(int x, int y);
  void outputguessed();
  /// Reset the Board for a new game
  void resetBoard();
  ///loads all bmp files into byte array
  void loadbmps();
};
