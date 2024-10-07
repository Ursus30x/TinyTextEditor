#include <ncurses.h>
#include "window.h"

void initColors(){
    start_color();
    use_default_colors();
    init_pair(0xFF, COLOR_BLACK, COLOR_WHITE);
}

void initSettings(){
    initscr();
    cbreak();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    noecho();
}


int main(){
    initSettings();
    initColors();

    windowInit();

    endwin();

    return 0;
}