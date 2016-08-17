/*******************************************************************************
                    ***** graphics.h *****

OpenGL graphics program, illustrating use of GLUT and callback functions.

Author: John M. Weiss, Ph.D.
Class:  CSC300 Data Structures
Date:   Fall 2015

Modifications:
*******************************************************************************/

// useful graphics function prototypes

// guard against multiple inclusions
#ifndef _Graphics_H_
#define _Graphics_H_

#include <GL/glut.h>
#include <string>
typedef unsigned char byte;

void initOpenGL( void );
void DrawLine( float x1, float y1, float x2, float y2, const float color[] );
void DrawRectangle( float x1, float y1, float x2, float y2,
                    const float color[] );
void DrawFilledRectangle( float x1, float y1, float x2, float y2,
                          const float color[] );
void DrawEllipse( float xRadius, float yRadius, int x, int y,
                  const float color[] );
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y,
                        const float color[] );
void DrawTextString( std::string text, int x, int y, const float color[] );
void DrawColorPallet ( float x1, float y1, float x2, float y2,
                       const float color[] );
void DrawGradedRect( float x1, float y1, float x2, float y2,
                     const float color[] );
//will fill in a sector of proper size with color. Plan to implement bmp later
void DrawSector(int s, const float color[]);

//will fill a sector with BMP of specified filename
void DrawSector(int s, byte* data);

void drawTexture(float x1, float y1, float x2, float y2, byte* data,
                 float width, float height);

#endif
