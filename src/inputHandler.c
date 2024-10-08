#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <string.h>
#include "inputHandler.h"
#include "textBuffer.h"

//TEMP DEFINES FOR DEBUG

#define MAX_ROW 20
#define MAX_COL 100

enum modeTypes{Insert,Move,newLine,Tab,Delete,Menu,Error};

enum modeTypes checkMode(const int keyPress){
    if(32 <= keyPress && keyPress <= 126)                       return Insert;
    else if(KEY_DOWN <= keyPress && keyPress <= KEY_RIGHT)      return Move;
    else if(keyPress == '\n')                                   return newLine;
    else if(keyPress == 9)                                      return Tab;
    else if(keyPress == KEY_DC || keyPress == KEY_BACKSPACE)    return Delete;
    else if(true)                                               return Menu;
    else                                                        return Error;
}

//wsPos is abrevieation for workspacePosition
int handleInput(const int keyPress, struct workspacePos_t *wsPos){
    struct textBuffer_t *buffHandle = getTextBufferHandle();

    switch (checkMode(keyPress))
    {
    case Insert:
        moveTextBuffer(wsPos->row,wsPos->col,wsPos->row,wsPos->col+1,1);
        writeCharToTextBuffer((char)(keyPress),wsPos->row,wsPos->col);
        
        buffHandle->lastCharPos[wsPos->row]++;
        wsPos->col++;
        break;
    case Move:

        if(keyPress == KEY_DOWN && wsPos->row < MAX_ROW 
        && !checkIfNullTextBuffer(wsPos->row+1,0)){
            wsPos->row++;
            if(checkIfNullTextBuffer(wsPos->row,wsPos->col)){
                wsPos->col = buffHandle->lastCharPos[wsPos->row];
            }
        }
        else if(keyPress == KEY_UP && wsPos->row > 0){
            wsPos->row--;
            if(checkIfNullTextBuffer(wsPos->row,wsPos->col)){
                wsPos->col = buffHandle->lastCharPos[wsPos->row];
            }
        }
        else if(keyPress == KEY_LEFT && wsPos->col > 0){
            wsPos->col--;
        }
        else if(keyPress == KEY_LEFT && wsPos->col == 0 && wsPos->row > 0){
            wsPos->row--;
            wsPos->col = buffHandle->lastCharPos[wsPos->row];
        }
        else if(keyPress == KEY_RIGHT && !checkIfNullTextBuffer(wsPos->row,wsPos->col+1)){
            wsPos->col++;
        }
        else if(keyPress == KEY_RIGHT && !checkIfNullTextBuffer(wsPos->row+1,0) ){
            wsPos->col = 0;
            wsPos->row++;
        }

        break;
    case newLine:

        insertNewLineTextBuffer(wsPos->row,wsPos->col);

        wsPos->row++;
        wsPos->col = 0;
        
        //if(!checkIfNullTextBuffer(wsPos->row+1,0))writeCharToTextBuffer('\n',wsPos->row,wsPos->col);
        break;

    case Tab:
        //rn tab space amount is equal 3
        const int spaceAmount = 3;

        moveTextBuffer(wsPos->row,wsPos->col,wsPos->row,wsPos->col+spaceAmount,1);
        for(int i = 0;i<spaceAmount;i++)writeCharToTextBuffer(' ',wsPos->row,wsPos->col+i);
        wsPos->col+=spaceAmount;
            
        break;
    case Delete:
        moveTextBuffer(wsPos->row,wsPos->col,wsPos->row,wsPos->col-1,0);

        if(wsPos->col > 0)wsPos->col--;

        break;
    case Menu:
        break;
    default:
        break;
    }
    
    return 0;
}