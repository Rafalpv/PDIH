#include <ncurses.h>
#include <unistd.h>
#define DELAY 3000

int main(int argc, char *argv[]){

    int rows, cols;

    initscr();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    clear();

    refresh();

    getmaxyx(stdscr,rows, cols);
    WINDOW * window = newwin(rows,cols,0,0);
    wbkgd(window, COLOR_PAIR(1));

    mvwprintw(window,10,10,"o");
    wrefresh(window);

    getch();
    endwin();
}