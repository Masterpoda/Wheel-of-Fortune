#ifndef _spinButton_H_
#define _spinButton_H_

#include "tile.h"

class spinButton : public Tile
{

protected:
    //contains the filename for the buttons image
    std::string filename = "Spin2.bmp";
    unsigned char * data;
    int width = 54, height = 52;
    //contains sector number for spin button
    int s = 7*25 + 13;
    int lastwinnings = 0;

    float x1, y1, x2, y2;


public:
    spinButton() {}
    ~spinButton() {}

    void drawTile();

    void initposition();
    void loadspinBMP();
    bool clicked(int x, int y);
    void drawSpin();
    void drawWinnings();
    int amountWon();
  

};

#endif
