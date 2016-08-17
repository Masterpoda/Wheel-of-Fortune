/*************************************************************************//**
 * @file
 ****************************************************************************/
#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "gameboard.h"
#include "game.h"
#include "guessgrid.h"
#include "spinButton.h"
#include "newButton.h"
#include <iostream>
#include <string>

using namespace std;

/// convenience typedef
typedef unsigned char byte;

///object containing the grid of letter guesses
static GuessGrid guesses;
/// object containing spinbutting and functions
static spinButton spin;
/// object containing game board
static gameboard board("");
/// object containing current game data
static Game currentGame("games.dat");
/// object containing new game button
static newButton newB;
/// string containing player keyboard input
static string total_input = "";

/// Event enum to describing events
enum EventType
{
    INIT,
    DISPLAY,
    KEYBOARD,
    MOUSECLICK,
    MOUSEDRAG,
};

/*!
* @brief Contains information about the event that is happening
* and constructors that assign enums and data depending on what is
* passed in.  Depending on the complexity of the application, the event
* structure might need to be extended.
*/
struct Event
{


    /** \brief type of event to handle */
    EventType eventtype;
    /** \brief keyboard key pressed by user */
    unsigned char key;
    /** \brief mouse button pressed */
    int button;
    /** \brief mouse button position (up or down) */
    int state;
    /** \brief x-coordinate of mouseclick */
    int x;
    /** \brief x-coordinate of mouseclick */
    int y;
    /** \brief object containing GuessGrid data*/


    /** \brief if there are no other params, display routine */
    Event() :
        eventtype(DISPLAY) {}
    /** \brief the call from initOpenGL */
    Event(int rows, int cols) :
        eventtype(INIT), x(rows), y(cols) {}
    /** \brief keyboard event */
    Event(unsigned char k, int xPos, int yPos) :
        eventtype(KEYBOARD), key(k), x(xPos), y(yPos) {}
    /** \brief mouse click in place */
    Event(int b, int s, int xPos, int yPos) :
        eventtype(MOUSECLICK), button(b), state(s), x(xPos), y(yPos) {}
    /** \brief mouse drag across screen */
    Event(EventType e, int xStart, int yStart) :
        eventtype(e), x(xStart), y(yStart) {}
};

/// The main hub for collecting the various events into a central location
void utilityCentral(Event eventstruct);
#endif // UTIL_H_INCLUDED
