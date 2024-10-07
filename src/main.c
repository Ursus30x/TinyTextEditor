#include <ncurses.h>
#include "inputHandler.h"
#include "textBuffer.h"
#include "gui.h"


void initColors(){
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
}

void initSettings(){
    initscr();
    cbreak();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    noecho();
}

int main(){
    struct workspacePos_t workspacePos = {0,0};

    int exit        = 0,
        keyPress    = 0;
    
    char filename[256] = "null.txt";


    initSettings();
    initColors();
    initTextBuffer();
    initGUI(filename,getTextBufferHandle(),workspacePos.row,workspacePos.col);

    updateGUI(filename,getTextBufferHandle(),workspacePos.row,workspacePos.col);
    while(!exit){
        keyPress = getch();
        handleInput(keyPress,&workspacePos);
        updateGUI(filename,getTextBufferHandle(),workspacePos.row,workspacePos.col);
        //printw("%d %d %d\n",keyPress,workspacePos.col, workspacePos.row);
        refresh();
    }

    freeTextBuffer();
    endwin();

    return 0;
}