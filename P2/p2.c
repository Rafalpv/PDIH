#include <ncurses.h>
#include <unistd.h>
#define DELAY 8000

int main(int argc, char *argv[])
{

    int rows, cols;

    // Pantalla Inicial

    initscr();
    curs_set(FALSE);
    start_color();
    noecho();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    refresh();

    getmaxyx(stdscr, rows, cols);
    WINDOW *window = newwin(rows, cols, 0, 0);
    wbkgd(window, COLOR_PAIR(1));
    box(window, '|', '-');

    mvwprintw(window, 6, 13, "Jugador 1: Izquierda -> W(Arriba) S(Abajo)\n");
    mvwprintw(window, 7, 13, "Jugador 2: Derecha -> O(Arriba) L(Abajo)");
    mvwprintw(window, 10, 3, "PULSA UNA TECLA PARA INICIAR!!. GANA EL PRIMERO QUE LLEGUE A 5 PUNTOS.");
    wrefresh(window);
    getch();
    endwin();

    
    // Juego

    initscr();
    start_color();
    noecho();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);

    refresh();

    getmaxyx(stdscr, rows, cols);
    WINDOW *window2 = newwin(rows, cols, 0, 0);
    wbkgd(window2, COLOR_PAIR(1));

    mvwprintw(window2, rows/2-2, 0, "|");
    mvwprintw(window2, rows/2-1, 0, "|");
    mvwprintw(window2, rows/2, 0, "|");

    mvwprintw(window2, rows/2-2, cols-1, "|");
    mvwprintw(window2, rows/2-1, cols-1, "|");
    mvwprintw(window2, rows/2, cols-1, "|");

    mvwprintw(window2, rows/2-1, cols/2, "O");

    wrefresh(window2);
    getch();
    endwin();
}