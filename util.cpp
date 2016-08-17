/*************************************************************************//**
* @file
*****************************************************************************/
#include <iostream>
#include <unistd.h>
#include "util.h"
#include "mouse.h"
#include "graphics.h"
#include "globals.h"

using namespace std;
void set_white(byte * &white);
void set_bg(byte * &bg);
bool isVowel(char letter);

/**************************************************************************//**
 * @author Paul Hinker
 *
 * @par Description:
 * This function gets called when an event happens in callbacks. Depending on
 * the enum and data passed in it will do different things. When a mouse click
 * is passed in, it sends that data to the click function in the container
 * class screen. When a mouse drag is sent in, it sends it to the clickAndDrag
 * function in screen.  It does the same for keyboard presses, sending them to
 * keyboardAction in screen.
 *
 * @param[in] event - structure that contains data about the event to handle
 *****************************************************************************/
void utilityCentral(Event eventstruct)
{
    static bool voweljustguessed, firstturn;
    static Mouse mouse;
    static byte * white;
    static byte * bg;


    //switch the enum containing type of event
    //call appropriate function in container
    switch (eventstruct.eventtype)
    {
    case INIT:
    {
        //add functions for resetting class values
        //do it for full points
        set_white(white);
        set_bg(bg);
        currentGame.set_newGame();
        guesses.loadbmps();
        guesses.resetBoard();
        newB.loadnewBMP();
        newB.drawnew();
        spin.loadspinBMP();
        spin.drawSpin();
        total_input.clear();
        voweljustguessed = false;
        firstturn = true;

        newB.initposition();
        spin.initposition();
        board.resetboard();
        board.setpuzzle(currentGame.get_gameWord());
        board.set_hint(currentGame.get_gameCat());
        board.loadBmps();
        currentGame.set_money(-2);

        if(!board.get_canfit())
            utilityCentral(Event(0,0));


        break;
    }
    case DISPLAY:
    {
        glClear( GL_COLOR_BUFFER_BIT);

        drawTexture(0, 0, 1000, 520, bg, 1920, 1080);
        string wallet;
        string spinval;
        int nrows = 0, ncols = 0;
        guesses.drawGrid();
        spin.drawSpin();
        newB.drawnew();
        board.make_board();
        currentGame.drawstrikes();
        DrawSector(-1, white);
        wallet = "Wallet: $" + to_string(currentGame.get_wallet());
        DrawTextString(wallet, 200, glutGet(GLUT_WINDOW_HEIGHT)-50, White);
        spinval = "$" + to_string(currentGame.get_money());

        if(currentGame.get_money() == -2)
            spinval = "Press Spin to Begin!";

        if(currentGame.get_money() == -1)
            spinval = "BANKRUPT";

        if(currentGame.get_money() == 0)
            spinval = "LOSE A TURN";

        if(board.puzzle_solved())
            spinval = "";

        DrawTextString(spinval, 600, glutGet(GLUT_WINDOW_HEIGHT)-400, White);
        
        if(board.puzzle_solved())
        {
                currentGame.set_canguess(false);
                currentGame.set_canspin(false);
                DrawTextString("Puzzle Solved!", 750, glutGet(GLUT_WINDOW_HEIGHT)-450, White);
                DrawTextString("(Click New Game to continue.)", 650, glutGet(GLUT_WINDOW_HEIGHT)-500, White);
        }
        else if(currentGame.gameOver())
        {
            DrawTextString("You have lost!", 750, glutGet(GLUT_WINDOW_HEIGHT)-450, White);
            DrawTextString("Press New Game to continue.", 750, glutGet(GLUT_WINDOW_HEIGHT)-500, White);
            utilityCentral(Event(nrows, ncols));
        }

        DrawSector(-1, white);
        string final = "Your Guess: ";
        DrawTextString((final + total_input), 50, glutGet(GLUT_WINDOW_HEIGHT)-500, White);
        glutSwapBuffers();

        break;
    }
    case KEYBOARD:
    {
        char input = eventstruct.key;
        input = toupper(input);
        if(int(input) == 13)
        {
            //treat this as a guess.
            if( currentGame.check_solution(total_input))
            {
                board.set_puzzle_solved();
                utilityCentral(Event());
            }
            else
            {
                total_input.clear();
                currentGame.add_strike();
                currentGame.set_money(0);
            }
        }
        else if(int(input) == 8 && (total_input.length() > 0))
        {
            //backspace has been pressed
            total_input.pop_back();
        }
        else if((isalpha(input) || input == ' ') && total_input.length() < 53)
        {
            total_input += input;
            utilityCentral(Event());
        }
        string final = "Your Guess: ";
        DrawTextString((final + total_input), 100, glutGet(GLUT_WINDOW_HEIGHT)-450, White);
        glutPostRedisplay();
    }
        break;
    case MOUSECLICK:
        if(eventstruct.button == GLUT_LEFT_BUTTON && eventstruct.state == GLUT_DOWN)
        {
            //change this state to check if game state is prepared for guess

            if(newB.clicked(eventstruct.x,eventstruct.y))
                utilityCentral(Event(0,0));
            int spinresult = 0;

            char player_guess = guesses.clicked(eventstruct.x,eventstruct.y);
            bool vowel = isVowel(player_guess), canguess = currentGame.get_canguess();

             if(player_guess != '~' && isalpha(player_guess))
             {
                 if(canguess || (!voweljustguessed && !firstturn)){
                     firstturn = false;

                 if((vowel && currentGame.get_wallet() >= 250) || (!vowel && canguess))//if the player can afford the letter
                 {
                     currentGame.set_canspin(true); //allow player to spin again after guess
                     guesses.guess(eventstruct.x, eventstruct.y); // set the letter to guessed

                     if(vowel && !voweljustguessed && !firstturn)
                     {
                         currentGame.set_wallet(currentGame.get_wallet()-250);
                         voweljustguessed = true;
                     }
                     else
                     {
                        voweljustguessed = false;
                        currentGame.set_canguess(false);
                     }

                     int occurrence = 0, wallet = currentGame.get_wallet(),
                         money = currentGame.get_money();

                     if(board.checkguess(player_guess, occurrence))
                     {
                         if(!vowel)
                             currentGame.set_wallet(wallet+(occurrence*money));
                         board.make_board();

                     }
                     else
                     {
                         if(!vowel)
                            currentGame.add_strike();
                     }
                 }
                 currentGame.set_canguess(false);
                 glutPostRedisplay();
             }
            }
            //change this state to allow spinning
            if(currentGame.get_canspin() && spin.clicked(eventstruct.x,eventstruct.y))
            {
                string output;
                currentGame.set_canguess(true);
                currentGame.set_canspin(false);
                spinresult = spin.amountWon();
                currentGame.set_money(spinresult);
                if(spinresult == 0)//result of 'Lose a turn'
                {
                    currentGame.set_money(0);
                    output = "LOSE A TURN";
                    currentGame.set_canguess(false);
                    currentGame.add_strike();
                    currentGame.set_canspin(true);
                }
                else if(spinresult == -1)
                {
                    output = "BANKRUPT";
                    currentGame.set_money(-1);
                    currentGame.set_canguess(false);
                    currentGame.set_canspin(true);
                    currentGame.set_wallet(0);
                    currentGame.add_strike();
                    //check for loss here
                }
                else
                {
                    string output = "$" + to_string(currentGame.get_money());
                }
            }
            glutPostRedisplay();
        }
        break;
    case MOUSEDRAG:

        break;
    }
}

//returns true if letter is a vowel
bool isVowel(char letter)
{
    letter = toupper(letter);
    if(letter == 'A' || letter == 'E' || letter == 'I' ||
       letter == 'O' || letter == 'U')
        return true;
    else
        return false;
}

void set_white(byte * &white)
{
    int rows = 54, cols = 40;
    chdir("Letters");
    loadBMP("Wheel~.bmp", rows, cols, white);
    chdir("..");

}

void set_bg(byte * &bg)
{
    int rows = 1080, cols = 1920;
    chdir("Letters");
    loadBMP("space.bmp", rows, cols, bg);
    chdir("..");
}
