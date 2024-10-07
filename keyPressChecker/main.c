#include <ncurses.h>

int main(){
    cbreak();
    initscr();
    intrflush(stdscr,FALSE);
    keypad(stdscr,TRUE);
    noecho();
    int ch;
    while(true){
        ch = getch();
        wclear(stdscr);
        wrefresh(stdscr);
        printw("KEY NAME: %s - %d\n", keyname(ch),ch);
    }
}