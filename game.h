/*************************************************************************//**
 * @file game.h
 *
 * @subpage game.cpp
 *
 * @class Game.h <game.h>
 *
 * @section depends_on Depends On
 * @verbatim

   must include:

#include <unordered_map>
#include <map>
#include <deque>
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#include <climits>
#include <map>
#include <time.h>
#include <stdlib.h>

 * 
 * @section course_section Course Information 
 *
 * @author Jeremy Gamet and Zac Christy
 * 
 * @date Feb 9, 2016
 * 
 * @par Professor: 
 *         Paul Hinker
 * 
 * @par Course: 
 *         CSC300
 * 
 * @par Location: 
 *         McLaury SDSM&T
 *
 * @section program_section Program Information 
 * 
 * @details This program 
 *
 *
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions:
 * @verbatim
 * 
 *      Compile with main.cpp and it's dependancies.
 *      Make sure LIBS = -lGL -lglut -lGLU -lm
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 

 * 
 * @par Modifications and Development Timeline: 
   @verbatim 

Format: Change date - notes

Changes
--------------------------------------------------------------------------------

Change Feb 4 - added the main argument testing, and slection loop

Change Feb 4 - added parsing and hash storage

Change Feb 7 - added newGame(), and all accessor methods

Change Feb 8 - completed documentation and formated as a class

Change Feb 9 - split Gameclass into a header file and .cpp file

   @endverbatim
 *
 *****************************************************************************/
#include <unordered_map>
#include <map>
#include <deque>
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#include <climits>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <string>
#include "loadBMP.h"

using namespace std;

class Game
{
private:
/*! \privatesection 
 *  \brief Private section of Game class.
 */

    int wallet = 0;				   /*!< the amount of money a player has won*/
    int money = -2; 			/*!< the money a player can buy letters with*/
    int strikes = 0; 			 /*!< the amount of striked against a player*/
    bool canspin = true;					  /*!< checks if player can spin*/
    bool canguess = false;					 /*!< checks if player can guess*/
    bool firstmove = true;				 /*!< checks if it is the first move*/
    byte * strikedata;						/*!< bitmap for the strike image*/
    byte * test;									 /*!< bitmap for testing*/

 /*! \struct new_rec 
 *  \brief This is a record struct.
 *
 * This struct will be used to read in
 * each new records from a games file
 * i.e. games.dat... and store
 * new instances of that struct
 * into a table by number. 
 */
struct new_rec {
	
    string cat; 				  /*!< will store the catagory from a record*/
    string word;				  /*!< will store the Gameword from a record*/
};


public:
/*! \publicsection 
 *  \brief Private section of Gameclass.
 */

/**************************************************************************//** 
 * @author Jeremy Gamet
 *         
 * 
 * @par Description:
 * 
 * Core Algorithm
 *  1. Start program checks
 *      (a. check main argument)
 *          (i. if file name bad issue statement)
 *      (b. check file)
 *
 *  2. store all records from file using a hash table
 *
 *
 *  3. call and test the newGame() function  
 * 
 * @param[in]      argc - a count of the command line arguments used to start
 *                        the program.
 * @param[in]     argv - a 2d character array of each argument.  Each token
 *                        occupies one line in the array.
 *
 * @returns 0 program ran without problems
 * @returns 1 for problems opening a file
 * @returns -1 commandline argument failure
 *
 *****************************************************************************/

Game(string filename);/*!< Game() default Game constructor normally this would
 take argc and argv but I'm using a string intermediately*/

~Game(){}												/*!< Game destructor*/

void set_newGame();				/*!< void set_newGame() resets the Gamestate*/

string get_gameWord(); /*!< string get_gameWord returns the current Gameword*/

string get_gameCat();	   /*!< string get_gameCat(); returns the current Game
 Category*/

int get_gameNum();		   /*!< returns the current number of the Gamerecord*/

void set_canspin(bool newstate);	   /*!< sets whether the player can spin*/

void set_canguess(bool newstate);	  /*!< sets whether the player can guess*/

bool get_canspin();						   /*!< returns the state of canspin*/

bool get_canguess();					  /*!< returns the state of canguess*/

int get_wallet();									/*!< return wallet value*/

void set_wallet( int newvalue );		   /*!< returns amount of money held*/

void set_money( int newvalue );			 /*!< sets player money to new level*/

int get_money();						   /*!< returns amount of money held*/

void add_strike();										  /*!< adds a strike*/

int check_strikes();						  /*!< returns amount of strikes*/

bool gameOver();				   /*!< returns true if current game is over*/

void drawStats();							 /*!< draws the money and wallet*/

void drawstrikes();						 /*!< draws the strikes on the board*/

bool check_solution(string guess);	  /*!< Checks to see if the string entered
 is a solution*/

unordered_map<unsigned int, new_rec > gameMap;	  /*!< a private hash table to 
store Game records*/

string gameWord;		  /*!< a private string to hold current game's word.*/

string gameCat;		  /*!< a private string to hold current game's category.*/

int gameNum;		/*!< a private int to hold current game's record number.*/

void grabRecord(const string word, deque<string> &fifo);   /*!< takes a single 
line from a record from a file*/

int openFile(string filename, ifstream &fin); 	  /*!< looks for a Gamerecords 
file i.e. games.dat*/

void hashRecords(ifstream& fin, unordered_map<unsigned int, 
new_rec> &gameMap); 	  /*!< stores records as new_rec structs in a table by 
number*/
};
