/*************************************************************************//**
 * @file game.h
 *
 * @section depends_on Depends On
 * @verbatim

   must include:

#include "game.h"
#include "graphics.h"
#include <iostream>
#include <unistd.h>

  *****************************************************************************/
#include "game.h"
#include "graphics.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Game::Game(string filename)
{
    // fin - file to be opened from command line args
    ifstream fin; 
    //error - will track any file or argument related errors for debuging
    int error = 1;
    //setting max load factor for hash tabel
    gameMap.max_load_factor(0.50);
    
    if ((error = openFile(filename,fin))) // 1. if error with fin or args

       exit(error); //return the error code

    hashRecords(fin,gameMap); // 2. store records in hash table gameMap

    set_newGame(); // 3. calls and resets Gamestate with the newGame() function
    int rows = 54, cols = 40;
    chdir("Letters");
    loadBMP("Strike.bmp", rows, cols, strikedata);
    chdir("..");
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     This function will read in the records to be parsed and insert them
 * into the hash map with key value pairs (new_game title, list of guess_words)
 *
 * @param[in,out] fin - file input stream
 * @param[in,out] gameMap - hash table for storage for guess_words by new_game title
 ******************************************************************************/
void Game::hashRecords(ifstream& fin, unordered_map<unsigned int, new_rec> &gameMap)
{
   string record; // record - contains single line records read in from file
   string cata; // cata - contains the catagory to be stored in gameMap
   string guess_words; // guess_words - the next game/guess/new word 
   deque<string> fifo; // fifo - will have each string from a single record
   unsigned int key = 0; //starting key value for the records 
   new_rec nr;

    //While you have not read in
    //all records from the file get a new record
    //then split up the records and emplace them
    while (getline(fin, record))
    {
        //for each of two records store strings into the fifo
        if (!record.empty())
        {
            grabRecord(record, fifo);
            try {if (!getline(fin, record)) throw 2;}
            catch (int e) {
                cerr << "Unexpected exception " << e
                     << ", record not found.\n"
                     << endl;
            }
            grabRecord(record, fifo);
        }
        else break;

        //the first string popped will be the key (new hint/cat)
        cata = fifo.back();
        fifo.pop_back();
        guess_words = fifo.front();
        fifo.pop_front();
        nr.cat = cata;
        nr.word = guess_words;

        //insert the key value pair (new_game, guess_words)
        key++;
        gameMap.insert(make_pair(key, nr));

        fifo.empty();
        cata.clear();
        guess_words.clear();

    }


    /*for(auto &itr: gameMap)
      clog << itr.first << endl <<
      itr.second.cat << endl <<
      itr.second.word << endl; */

    return;
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     This is the routine which will validate command line params
 *
 * @param[in] argc - this is the argc directly from main()
 * @param[in,out] argv - this is a pointer to the argv c string from main
 * @param[in,out] fin - input file stream
 * @param[in,out] foutWrd - output file stream for the .wrd file
 * @param[in,out] foutCsv - output file stream for the .csv file
 * 
 * @returns 1 Errors Occurred in opening the file
 * @returns 0 Function ran without error
 ******************************************************************************/
int Game::openFile(string filename,ifstream &fin)
{

    /*verstion 2.0 has phased out command line usage */
    /*  
    //a. Validate the existence of command line arguments
    if (argc != 2 && argc != 1)
    {
        //i. issue general usage statement for wrong args
        cerr <<
             "Incorrect number of command line arguments. \n\n" <<

             "This program takes a single input argument.\n" <<
             "The argument should be a games.dat file.\n" <<
             "The input file should contain game records. \n" <<
             "Syntax: game /<input file path>/games.dat\n\n" <<

             "Example: game " << argv[0] << " games.dat\n\n" <<

             "The *.dat file must be an available resource.\n"

             "Please try again. \n\n" <<
             endl;

        return -1;
    } */

    //b. Validate opening of the file
    try {fin.open(filename); if (!fin)throw 1;}
    catch (int e) {if (e == 1)fin.open("games.dat");}


    if (!fin)
    {
        cerr << "Could not open file with games.dat as name\n\n"

             "The input file should contain game records. \n" <<
             "Syntax: game /<input file path>/games.dat\n\n" <<

             "Example: relative path -> games.dat\n\n" <<

             "The *.dat file must also be an available resource.\n"

             "Please try again. \n\n" <<
             endl;

        return 1;
    }
    return 0;
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     This function will seperate out information contained in a single
 * new_game record i.e. new_game(year)/actor name/actor name... etc
 *
 * @param[in] rec - original record being parsed
 * @param[in,out] fifo - queue containing record data
 *
 * @returns void
 ******************************************************************************/
void Game::grabRecord(const string rec, deque<string> &fifo)
{
    auto length = rec.length();
    string temp;

    if (!rec.empty())
    {
        for (unsigned int i = 0; i < length; i++)
        {
            if (rec[i] != '\n')
                temp.push_back(rec[i]);
            else
            {
                temp.clear();
            }
        }
    }

    if (temp.length() > 0)
        fifo.push_front(temp);

    if (fifo.empty())
        fifo.push_front(rec);

    return;
}



/***************************************************************************//**
 * @author Jeremy Gamet and Zac Christy
 *
 *
 * @par Description
 *     This function begins a new game when the user chooses to start another
 * game.
 *
 * @returns void
 ******************************************************************************/
void Game::set_newGame()
{
    //gameMap iterator to access the records from the gameMap
    unordered_map<unsigned int, new_rec >::const_iterator itr;

    wallet = 0;
    money = 0;
    strikes = 0;
    firstmove = false;
    canspin = true;

    //declare and set a random number
    srand(time(NULL));
    int random = rand();

    random = random % gameMap.size();

    if (random == 0) random++;

    //set itr to a random number within the range of the table
    itr = gameMap.find(random);

    gameNum = itr->first;
    gameCat = itr->second.cat;
    gameWord = itr->second.word;

    return;
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's word.
 *
 * @returns string returns the current game's word
 ******************************************************************************/
string Game::get_gameWord()
{
    return gameWord;
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's category.
 *
 * * @returns string returns the current game's category
 ******************************************************************************/
string Game::get_gameCat()
{
    return gameCat;
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's number.
 *
 * @returns int returns the current game's number
 ******************************************************************************/
int Game::get_gameNum()
{
    return gameNum;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public mutator for canguess.
 *
 * @returns void
 ******************************************************************************/
void Game :: set_canguess(bool newstate)
{
    canguess = newstate;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public mutator for the current game's canspin.
 *
 * @returns void
 ******************************************************************************/
void Game :: set_canspin(bool newstate)
{
    canspin = newstate;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's canguess.
 *
 * @returns void
 ******************************************************************************/
bool Game :: get_canguess()
{
    return canguess;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's canspin.
 *
 * @returns void
 ******************************************************************************/
bool Game :: get_canspin()
{
    return canspin;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's wallet.
 *
 * @returns void
 ******************************************************************************/
int Game :: get_wallet()
{
    return wallet;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public mutator for the current game's wallet.
 *
 * @returns void
 ******************************************************************************/
void Game :: set_wallet( int newvalue )
{
    wallet = newvalue;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public mutator for the current game's money.
 *
 * @returns void
 ******************************************************************************/
void Game :: set_money( int newvalue )
{
    firstmove = false;
    money = newvalue;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's money.
 *
 * @returns void
 ******************************************************************************/
int Game :: get_money()
{
    return money;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public mutator for the current game's strikes.
 * It increments the current game's strikes value.
 *
 * @returns void
 ******************************************************************************/
void Game :: add_strike()
{
    strikes++;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function is a public accessor for the current game's strikes.
 *
 * @returns int returns the number of strikes
 ******************************************************************************/
//returns amount of strikes
int Game :: check_strikes()
{
    return strikes;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function checks if the game has been lost.
 *
 * @returns true  game has been lost
 * @returns false game has not been lost yet
 ******************************************************************************/
bool Game :: gameOver()
{
    if(strikes >= 3)
        return true;
    else
        return false;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function draws the bitmap images for the strike bitmaps when the user
 * recieves a strike.
 *
 * @returns void
 ******************************************************************************/
void Game :: drawstrikes()
{
    for (int i = 0; i < strikes && i < 3; i++)
        DrawSector(154 + i*2, strikedata);
}

/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function checks if the guess entered by the user is the solution to
 * the puzzle.
 *
 * @returns true  guess was correct
 * @returns false guess was not correct
 ******************************************************************************/
bool Game :: check_solution(string guess)
{
    if(guess == get_gameWord())
        return true;
    return false;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function creates the text strings for the wallet and the amoutnt of
 * money spun.
 *
 * @returns void
 ******************************************************************************/
void Game :: drawStats()
{
    const float color[3] = {0.0f, 0.0f, 0.0f};
    string output = "";
    DrawTextString(output, 5, 5, color);
    DrawTextString(output, 5, 5, color);
}
