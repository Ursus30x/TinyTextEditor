#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "inputHandler.h"
#include "textBuffer.h"

//TEMP DEFINES FOR DEBUG

#define MAX_ROW 20
#define MAX_COL 100

enum modeTypes{Insert,Move,newLine,Delete,Menu,Error};

enum modeTypes checkMode(const int keyPress){
    if(32 <= keyPress && keyPress <= 126)                   return Insert;
    else if(KEY_DOWN <= keyPress && keyPress <= KEY_RIGHT)  return Move;
    else if(keyPress == '\n')                               return newLine;
    else if(keyPress == KEY_DC)                             return Delete;
    else if(true)                                           return Menu;
    else                                                    return Error;
}

//wsPos is abrevieation for workspacePosition
int handleInput(const int keyPress, struct workspacePos_t *wsPos){
    struct textBuffer_t *buffHandle = getTextBufferHandle();

    switch (checkMode(keyPress))
    {
    case Insert:
        writeCharToTextBuffer((char)(keyPress),wsPos->row,wsPos->col);
        buffHandle->lastCharPos[wsPos->row] = wsPos->col; 
        wsPos->col++;
        break;
    case Move:
        if(keyPress == KEY_DOWN && wsPos->row < MAX_ROW 
        && !checkIfNullTextBuffer(wsPos->row+1,0)){
            wsPos->row++;
        }
        else if(keyPress == KEY_UP && wsPos->row > 0){
            wsPos->row--;
        }
        else if(keyPress == KEY_LEFT && wsPos->col > 0){
            wsPos->col--;
        }
        else if(keyPress == KEY_RIGHT && wsPos->col < MAX_COL 
        && !checkIfNullTextBuffer(wsPos->row,wsPos->col)){
            wsPos->col++;
        }

        break;
    case newLine:
        buffHandle->lastCharPos[wsPos->row] = wsPos->col; 
        writeCharToTextBuffer('\n',wsPos->row,wsPos->col);
        writeCharToTextBuffer('\0',wsPos->row,wsPos->col+1);

        wsPos->row++;
        wsPos->col = 0;

        break;
    case Delete:
        break;
    case Menu:
        break;
    default:
        break;
    }
    
    return 0;
}