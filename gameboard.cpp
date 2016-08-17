#include "gameboard.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "graphics.h"
#include "game.h"
#include "tile.h"
#include "loadBMP.h"
#include "globals.h"

using namespace std;

#include <GL/glut.h>
void gameboard :: display_message(string message)
{
	const float color[3] = {0.0f, 0.0f, 0.0f};
	    
	DrawTextString( message, 200, glutGet(GLUT_WINDOW_HEIGHT)-50, color);
}

void gameboard :: make_board()
{
    const float color[3] = {0.0f, 0.0f, 0.0f};
    string Hint = "Hint: ";
    int i;


        //drawing line clue across top
	for(i = 0; i < 12; i ++)
        {
            if(guessed[0][i] || display[0][i] == '~')
                DrawSector(52 + i, data[0][i]);
            else
                DrawSector(52 + i, unguessed);
        }

        //drawing second line
        for(i = 0; i < 12; i++)
        {
            if(guessed[1][i] || display[1][i] == '~')
                DrawSector(77 + i, data[1][i]);
            else
                DrawSector(77 + i, unguessed);
        }



        for(i = 0; i < 12; i++)
	{
            if(guessed[2][i] || display[2][i] == '~')
                DrawSector(102 + i, data[2][i]);
            else
                DrawSector(102 + i, unguessed);
        }

	
        for(i = 0; i < 12; i++)
        {
            if(guessed[3][i] || display[3][i] == '~')
                DrawSector(127 + i, data[3][i]);
            else
                DrawSector(127 + i, unguessed);
        }

        DrawSector(76, blank);
        DrawSector(89, blank);
        DrawSector(101, blank);
        DrawSector(114, blank);

        DrawSector(-1, unguessed);
        Hint = (Hint + hint);
        DrawTextString( Hint, 200, glutGet(GLUT_WINDOW_HEIGHT)-100, color);
}

void gameboard :: draw(float x1, float y1, float x2, float y2, const float color[])
{
   
	glColor3fv(White);
	glBegin( GL_POLYGON);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
	
	glFlush();
}

void gameboard :: insertChar( char letter)
{
	int i = 52;
	
	const float color[3] = {0.0, 0.0, 0.0};
	
	if(letter != '~')	
	DrawSector(i, color);
	
}

void gameboard :: loadBmps()
{
    chdir("Letters");
    string filename;
    for(int i = 0; i<4; i++){
        for(int j = 0; j<12; j++)
        {
            if(isalpha(display[i][j]))
            {
                filename = "WheelA.bmp";
                filename[5] = display[i][j];
            }
            else
                filename = "WheelBackground.bmp";
            int rows = 54, cols = 40;
            loadBMP(filename, rows, cols, data[i][j]);
        }
    }
    int rows = 54, cols = 40;
    loadBMP("WheelBackground.bmp", rows, cols, blank);
    rows = 54, cols = 40;
    loadBMP("Wheel~.bmp", rows, cols, unguessed);
    chdir("..");

}

void gameboard :: outputDisplay()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 12; j++)
            cout<<display[i][j];
        cout<<endl;
    }
}

void gameboard :: setpuzzle(string puzzle)
{
    answer = puzzle;
    int numlines = 0, currline = 0, linelen[4] = {0};
    unsigned int linespace = 12, line = 0; // line to write to
    string word = "";

    getdim(numlines, linelen);

    if(numlines <= 3)
        line = 1;

    for(unsigned int i = 0; i < answer.length(); i++)
    {
        if(isalpha(answer[i]))
        {
            word = word + answer[i];
        }
        if(answer[i] == ' ' || i == answer.length()-1)
        {
            if(word[word.length() - 1] == ' ')
                word.pop_back();

            int offset = (12 - linelen[currline])/2;


            if(linespace > word.length())
            {

                for(unsigned int j = 0; j < word.length(); j++)
                    display[line][(12 - linespace) + j + offset] = word[j];

                linespace -= word.length();
            }
            else
            {
                line++;
                currline++;
                if(line > 3)
                    break;
                linespace = 12;
                offset = (12 - linelen[currline])/2;
                for(unsigned int j = 0; j < word.length(); j++)
                    display[line][(12 - linespace) + j + offset] = word[j];

                linespace -= word.length();
            }
            word.clear();
            if(linespace > 0)
            {
                display[line][12-linespace + offset] = '~';
                linespace --;
            }
        }
        if(line > 3)
            canfit = false;
    }

    if(line > 3)//returning false if the puzzle wont fit
        canfit = false;
}


bool gameboard :: checkguess(char guess, int &occurrence)
{
    occurrence = 0;
    guess = toupper(guess);
    if(!isalpha(guess))
        return false;

    bool found = false;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            if(display[i][j] == guess)
            {
                found = true;
                guessed[i][j] = true;
                occurrence++;
            }
        }
    }
    return found;
}

bool gameboard :: puzzle_solved()
{
    bool solved = true;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            if(guessed[i][j] == false && display[i][j] != '~')
                solved = false;
        }
    }
    return solved;
}

bool gameboard :: puzzle_solved(string guess)
{
    if(guess == answer)
        return true;
    else
        return false;
}

void gameboard :: set_hint(string newhint)
{
    hint = newhint;
}

bool gameboard :: set_puzzle_solved()
{
    bool solved = true;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            guessed[i][j] = true;
        }
    }
    return solved;
}

void gameboard :: resetboard()
{
    for(int i =0; i<4; i++)
    {
        for(int j = 0; j <12; j++)
        {
            display[i][j] = '~';
            data[i][j] = blank;
            guessed[i][j] = false;
        }
    }

}

void gameboard :: getdim(int &numlines, int linelen[])
{
    string word = "";
    unsigned int line = 0;
    unsigned int linespace = 12;
    for(unsigned int i = 0; i < answer.length(); i++)
    {
        if(isalpha(answer[i]))
        {
            word = word + answer[i];
        }
        if(answer[i] == ' ' || i == answer.length()-1)
        {
            if(word[word.length() - 1] == ' ')
                word.pop_back();
            if(linespace > word.length())
            {

                linespace -= word.length();
            }
            else
            {
                linelen[line] = 11 - linespace;
                linespace = 12;
                line++;
                numlines += 1;
                linespace -= word.length();
            }
            word.clear();
            if(linespace > 0)
            {
                linespace --;
            }
        }
    }
    numlines += 1;
    linelen[line] = 11-linespace;
}

bool gameboard :: get_canfit()
{
    return canfit;
}
