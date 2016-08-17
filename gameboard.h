#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <string>
#include <iostream>

using namespace std;
typedef unsigned char byte;


//We need to allot third Rows

class gameboard{
    string answer;
    string hint;
    char display[4][12];
    bool isletter[4][12];
    bool guessed[4][12];
    byte * data[4][12];
    byte * blank;
    byte * unguessed;
    bool canfit = true;

    void getdim(int &numlines, int linelen[]);

public:
    gameboard(string puzzle) {
        for(int i =0; i<4; i++)
        {
            for(int j = 0; j <12; j++)
            {
                display[i][j] = '~';
                guessed[i][j] = false;
            }
        }
        setpuzzle(puzzle);
    }
    ~gameboard(){

    }

    //draws the board
    void display_message(string message);
    void make_board();
    void draw(float x1, float y1, float x2, float y2, const float color[]);
    void insertChar( char letter);
    void setguessed(int i);
    void loadBmps();
    void outputDisplay();
    void setpuzzle(string puzzle);
    bool checkguess(char guess, int &occurrence);
    bool puzzle_solved();
    bool set_puzzle_solved();
    bool puzzle_solved(string guess);
    void set_hint(string newhint);
    void resetboard();
    bool get_canfit();


};



#endif
