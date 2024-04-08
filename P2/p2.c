#include <ncurses.h>
#include <unistd.h>

#define DELAY 40000

int j1_points = 0, j2_points = 0;

void puntuacion(WINDOW *window, int j_points, int y, int x)
{

    char points[2];
    sprintf(points, "%d", j_points);
    mvwprintw(window, y, x, points);
}

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

    mvwprintw(window, 3, 10, "0");
    mvwprintw(window, 3, 80, "0");

    wrefresh(window);

    int direction_x = 1, direction_y = 1, ant_X, ant_Y;

    while (1)
    {
        // Movimiento Jugadores
        switch (getch())
        {
        case 'w':
        case 'W':
            if (jug1 - 1 > 0)
            {
                mvwprintw(window, jug1 + 1, 1, " ");
                mvwprintw(window, jug1 - 2, 1, "|");
                jug1--;
            }
            break;
        case 's':
        case 'S':
            if (jug1 + 2 < rows)
            {
                mvwprintw(window, jug1 - 1, 1, " ");
                mvwprintw(window, jug1 + 2, 1, "|");
                jug1++;
            }
            break;
        case 'o':
        case 'O':
            if (jug2 - 1 > 0)
            {
                mvwprintw(window, jug2 + 1, cols - 2, " ");
                mvwprintw(window, jug2 - 2, cols - 2, "|");
                jug2--;
            }

            break;
        case 'l':
        case 'L':
            if (jug2 + 2 < rows)
            {
                mvwprintw(window, jug2 - 1, cols - 2, " ");
                mvwprintw(window, jug2 + 2, cols - 2, "|");
                jug2++;
            }
            break;
        }

        // Movimiento de la pelota

        next_x = xBall + direction_x;
        next_y = yBall + direction_y;
        ant_X = xBall;
        ant_Y = yBall;

        if (next_x > cols || next_x < -1)
            direction_x *= -1;
        else
            xBall += direction_x;

        // if (next_y >= rows || next_y < 0)
        //     direction_y *= -1;
        // else
        //     yBall += direction_y;

        // Puntuacion
        if (xBall == -1)
        {
            j2_points++;
            puntuacion(window, j2_points, 3, 80);
            xBall = cols / 2;
            yBall = rows / 2 - 1;
            direction_x *= -1;
            usleep(1000000);
        }

        if (xBall == cols)
        {
            j1_points++;
            puntuacion(window, j1_points, 3, 10);
            xBall = cols / 2;
            yBall = rows / 2 - 1;
            direction_x *= -1;
            usleep(1000000);
        }

        // Colision con los jugadores

        if(xBall == 2 && (yBall >= jug1-1 && yBall <= jug1+1))
            direction_x *= -1;
        else if(xBall == cols-3 && (yBall >= jug2-1 && yBall <= jug2+1))
            direction_x *= -1;
        

        // Pintamos la pelota
        mvwprintw(window, ant_Y, ant_X, " ");
        mvwprintw(window, yBall, xBall, "O");
        usleep(DELAY);

        wrefresh(window);
    }

    endwin();
}