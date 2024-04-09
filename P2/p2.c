#include <ncurses.h>
#include <unistd.h>

#define DELAY 40000

int j1_points = 0, j2_points = 0;
int rows, cols;

WINDOW *pantallaInicial()
{
    initscr();
    curs_set(FALSE);

    start_color();
    noecho();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    refresh();

    getmaxyx(stdscr, rows, cols);
    WINDOW *window = newwin(rows, cols, 0, 0);
    box(window, '|', '-');

    mvprintw(rows / 2 - rows / 4, 0, "\t           oooooooooo                                        \n"
                                     "\t           888    888  ooooooo    ooooooo    oooooooo8       \n"
                                     "\t           888oooo88 888     888 888   888  888    88o       \n"
                                     "\t           888       888     888 888   888   888oo888o       \n"
                                     "\t          o888o        88ooo88  o888o o888o 888     888      \n"
                                     "\t                                             888ooo888     \n\n"
                                     "\t \t\t JUGADOR 1 your controls are 'w' and 's' \n"
                                     "\t \t\t JUGADOR 2 your controls are 'o' and 'l' \n"
                                     "\t \t\t Pulsa cualquiera tecla");

    wrefresh(window);

    return window;
}

void estadoInicial(WINDOW *window)
{
    wbkgd(window, COLOR_PAIR(1));
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    mvwprintw(window, rows / 2 - 2, 1, "|");
    mvwprintw(window, rows / 2 - 1, 1, "|");
    mvwprintw(window, rows / 2, 1, "|");

    mvwprintw(window, rows / 2 - 2, cols - 2, "|");
    mvwprintw(window, rows / 2 - 1, cols - 2, "|");
    mvwprintw(window, rows / 2, cols - 2, "|");

    mvwprintw(window, rows / 2 - 1, cols / 2, "o");

    mvwprintw(window, 3, 40, "0");
    mvwprintw(window, 3, 60, "0");

    wrefresh(window);
}

void puntuacion(WINDOW *window, int j_points, int y, int x)
{
    mvwprintw(window, y, x, "%d", j_points);
}

void finPartida(WINDOW *window)
{
    werase(window);
    nodelay(stdscr, false);

    box(window, '|', '-');

    mvprintw(5, 5, "JUGADOR 1 : %d", j1_points);

    mvprintw(8, 5, "JUGADOR 2 : %d", j2_points);

    wrefresh(window);

    getch();
}

int main(int argc, char *argv[])
{


    WINDOW *window = pantallaInicial();
    keypad(stdscr, true);

    getch();

    werase(window);

///////////////////////////////////////////////

    int xBall = cols / 2,
        yBall = rows / 2 - 1,
        jug1 = rows / 2 - 1,
        jug2 = rows / 2 - 1,
        next_y = -1, 
        next_x = -1;

    estadoInicial(window);

    int direction_x = 1, direction_y = 1, ant_X, ant_Y;

    while (1)
    {
        mvvline(0, cols / 2, ACS_VLINE, cols);


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
        case 'p':
        case 'P':
            getchar();
            break;
        }

        // Colision con los jugadores
        if (xBall == 2 && (yBall >= jug1 - 1 && yBall <= jug1 + 1))
            direction_x *= -1;
        else if (xBall == cols - 3 && (yBall >= jug2 - 1 && yBall <= jug2 + 1))
            direction_x *= -1;


        // Movimiento de la pelota
        next_x = xBall + direction_x;
        next_y = yBall + direction_y;
        ant_X = xBall;
        ant_Y = yBall;

        if (next_x > cols || next_x < -1)
            direction_x *= -1;
        else
            xBall += direction_x;

        if (next_y >= rows || next_y < 0)
            direction_y *= -1;
        else
            yBall += direction_y;

        // Puntuacion
        if (xBall == -1)
        {
            j2_points++;
            mvwprintw(window, 3, 60, "%d", j2_points);
            xBall = cols / 2;
            yBall = rows / 2 - 1;
            direction_x *= -1;
            usleep(10000);
        }

        if (xBall == cols)
        {
            j1_points++;
            mvwprintw(window, 3, 40, "%d", j1_points);
            xBall = cols / 2;
            yBall = rows / 2 - 1;
            direction_x *= -1;
            usleep(10000);
        }

        // Pintamos la pelota
        mvwprintw(window, ant_Y, ant_X, " ");
        mvwprintw(window, yBall, xBall, "o");
        usleep(DELAY);

        if (j1_points == 3 || j2_points == 3)
            finPartida(window);

        wrefresh(window);
    }

    endwin();
}