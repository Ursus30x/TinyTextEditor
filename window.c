#include <ncurses.h>

//headers window size
#define HEADER_SIZE_Y 1

//key lookup window size
#define LOOKUP_SIZE_Y 2

//header title in right upper corner
#define HEADER_TITLE_STR "Tiny Editor"
#define HEADER_TITLE_SIZE 11

void initHeaderWin(WINDOW* headerWin, char* filename){
    wbkgd(headerWin, COLOR_PAIR(0xff));
    wattron(headerWin,A_BOLD|A_STANDOUT);
    
    wprintw(headerWin,"%s",filename);
    mvwprintw(headerWin,0,getmaxx(headerWin)-HEADER_TITLE_SIZE,HEADER_TITLE_STR);

    
    wrefresh(headerWin);
}

void initWorkspaceWin(WINDOW* workspaceWin,char** textBuffer){
    
}

void windowInit(){
    bool    closeEditor = false;

    int     rowsMax = getmaxy(stdscr),  
            colsMax = getmaxx(stdscr),
            keyPressed = 0;

    printw("%d %d\n",rowsMax,colsMax);
            
    WINDOW  *headerWin = newwin(HEADER_SIZE_Y,colsMax,0,0),
            *workspaceWin = newwin(rowsMax-LOOKUP_SIZE_Y-HEADER_SIZE_Y,colsMax,HEADER_SIZE_Y,0),
            *lookupWin = newwin(2,colsMax,rowsMax-LOOKUP_SIZE_Y,0);
    refresh();

    initHeaderWin(headerWin,"LoremIpsum.cpp");


    
    while(!closeEditor){
        keyPressed = getch();
        
    }
    

}