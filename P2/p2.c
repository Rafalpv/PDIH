#include <ncurses.h>
#include <unistd.h>
#define DELAY 30000

int main(int argc, char *argv[])
{

    int rows, cols;

    // Pantalla Inicial

    initscr();
    curs_set(FALSE);

    start_color();
    noecho();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

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

    werase(window);

    //  Comienzo del Juego

    int xBall = cols / 2,
        yBall = rows / 2 - 1,
        jug1 = rows / 2 - 1, 
        jug2 = rows / 2 - 1;
    
    int next_y, next_x;

    wbkgd(window, COLOR_PAIR(2));
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    cbreak();

    mvwprintw(window, rows / 2 - 2, 1, "|");
    mvwprintw(window, rows / 2 - 1, 1, "|");
    mvwprintw(window, rows / 2, 1, "|");

    mvwprintw(window, rows / 2 - 2, cols - 2, "|");
    mvwprintw(window, rows / 2 - 1, cols - 2, "|");
    mvwprintw(window, rows / 2, cols - 2, "|");

    mvwprintw(window, rows / 2 - 1, cols / 2, "O");

    wrefresh(window);

    int direction_x = 1, direction_y = 1, ant_X, ant_Y;

    while (1)
    {
        switch (getch()){
        case 'w':;
            if (jug1 - 1 > 0)
            {
                mvwprintw(window, jug1 + 1, 1, " ");
                mvwprintw(window, jug1 - 2, 1, "|");
                jug1--;
            }
            break;
        case 's':
            if (jug1 + 2 < rows)
            {
                mvwprintw(window, jug1 - 1, 1, " ");
                mvwprintw(window, jug1 + 2, 1, "|");
                jug1++;
            }
            break;
        case 'o':
            if (jug2 - 1 > 0)
            {
                mvwprintw(window, jug2 + 1, cols - 2, " ");
                mvwprintw(window, jug2 - 2, cols - 2, "|");
                jug2--;
            }

            break;
        case 'l':
            if (jug2 + 2 < rows)
            {
                mvwprintw(window, jug2 - 1, cols - 2, " ");
                mvwprintw(window, jug2 + 2, cols - 2, "|");
                jug2++;
            }
            break;
        }

        // Movimiento de la pelota
        mvwprintw(window, ant_Y ,ant_X, " ");
        mvwprintw(window, yBall, xBall, "O");
        usleep(DELAY);

        next_x = xBall + direction_x;
        next_y = yBall + direction_y;
        ant_X = xBall; ant_Y = yBall;

        if(next_x >= cols || next_x < 0)
            direction_x *= -1;
        else
            xBall += direction_x;

        if(next_y >= rows || next_y < 0)
            direction_y *= -1;
        else
            yBall += direction_y;
    
        wrefresh(window);
    }

    endwin();
}