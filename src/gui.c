#include <ncurses.h>
#include <string.h>
#include <math.h>
#include "textBuffer.h"
#include "misc.h"


#define PROGRAM_NAME "TinyTextEditor"
#define PROGRAM_NAME_LEN 14

#define HEADER_SIZE_ROW 1
#define TOOLTIP_SIZE_ROW 3


WINDOW  *headerWin,
        *workspaceWin,
        *tooltipWin;

void updateHeader(const char *filename){
    wbkgd(headerWin,COLOR_PAIR(1));
    mvwprintw(headerWin,0,0,"%s",filename);
    mvwprintw(headerWin,0,getmaxx(headerWin)-PROGRAM_NAME_LEN,"%s",PROGRAM_NAME);

    wrefresh(headerWin);
}

void updateWorkspace(const struct textBuffer_t *textBuffer){
    int maxNumLen = getNumOfDigits(getmaxy(workspaceWin));

    wclear(workspaceWin);

    for(int i = 0;i<getmaxy(workspaceWin);i++){
        if(i == 0){
            mvwprintw(workspaceWin,i,maxNumLen-1,"1 %s",textBuffer->buffer[i]);
        }
        else if(textBuffer->buffer[i][0] == '\0' && textBuffer->lastCharPos[i-1] != '\n'){
            mvwprintw(workspaceWin,i,0,"~ %s",textBuffer->buffer[i]);
        }
        else{
            mvwprintw(workspaceWin,i,maxNumLen-getNumOfDigits(i),"%d %s",i+1,textBuffer->buffer[i]);
        }

    }

    wrefresh(workspaceWin);
}

//TODO: remove row and col and make it a struct

void updateCursorPos(const int row,const int col){
    move(row+HEADER_SIZE_ROW,col+3);
}

void updateGUI(const char *filename,const struct textBuffer_t *textBuffer,const int row,const int col){
    updateHeader(filename);
    updateWorkspace(textBuffer);

    updateCursorPos(row,col);

    refresh();
}

void initGUI(const char* filename, const struct textBuffer_t *textBuffer,const int row,const int col){
    int     rowMax = getmaxy(stdscr),  
            colMax = getmaxx(stdscr);

    headerWin = newwin(HEADER_SIZE_ROW,colMax,0,0);
    workspaceWin = newwin(rowMax-HEADER_SIZE_ROW,colMax,HEADER_SIZE_ROW,0);

    refresh();
    updateGUI(filename,textBuffer,row,col);

    
}
