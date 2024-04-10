#include <ncurses.h>
#include <unistd.h>

#define DELAY 35000
#define PUNTOS 5

bool end = false;
int j1_points = 0, j2_points = 0;
int rows, cols;
int jug1, jug2;
int xBall, yBall, next_x, next_y;
int direction_x = 1, direction_y = 1, ant_X, ant_Y;

WINDOW *newWindow()
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
    return window;
}

void printTitle(WINDOW *window)
{
    mvprintw(rows / 2 - rows / 3, 0, "\t    oooooooooo                                        \n"
                                     "\t    888    888  ooooooo    ooooooo    oooooooo8       \n"
                                     "\t    888oooo88 888     888 888   888  888    88o       \n"
                                     "\t    888       888     888 888   888   888oo888o       \n"
                                     "\t    o888o        88ooo88  o888o o888o 888     888      \n"
                                     "\t                                      888ooo888     \n\n"
                                     "\t \t JUGADOR 1 your controls are 'w' and 's' \n"
                                     "\t \t JUGADOR 2 your controls are 'o' and 'l' \n"
                                     "\t \t Pulsa cualquiera tecla");
}

void resetBall(WINDOW *window)
{
    xBall = cols / 2,
    yBall = rows / 2 - 1,
    mvwprintw(window, rows / 2 - 1, cols / 2, "o");
}

void resetPlayers(WINDOW *window)
{
    jug1 = rows / 2 - 1,
    jug2 = rows / 2 - 1;
    for (int i = 0; i < 3; i++)
    {
        mvwprintw(window, rows / 2 - i, 1, "|");
        mvwprintw(window, rows / 2 - i, cols - 2, "|");
    }
}

void resetMarcador(WINDOW *window)
{
    j1_points = 0,
    j2_points = 0,
    mvwprintw(window, 3, cols / 2 + rows / 6, "0");
    mvwprintw(window, 3, cols / 2 - rows / 6, "0");
}

void initializeGame(WINDOW *window)
{
    werase(window);
    wbkgd(window, COLOR_PAIR(1));
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    resetBall(window);
    resetPlayers(window);
    resetMarcador(window);

    wrefresh(window);
}

void puntuacion(WINDOW *window)
{

    if (xBall == -1 || xBall == cols)
    {
        if (xBall == -1)
        {
            j2_points++;
            mvwprintw(window, 3, cols / 2 - rows / 6, "%d", j2_points);
        }
        else
        {
            j1_points++;
            mvwprintw(window, 3, cols / 2 + rows / 6, "%d", j1_points);
        }
        xBall = cols / 2;
        yBall = rows / 2 - 1;
        direction_x *= -1;
        usleep(20000);
    }
}

void moveBall(WINDOW *window)
{
    next_x = xBall + direction_x;
    next_y = yBall + direction_y;

    if (next_x == 1 && (next_y >= jug1 - 1 && next_y <= jug1 + 1) || next_x == cols - 2 && (next_y >= jug2 - 1 && next_y <= jug2 + 1))
        direction_x *= -1;

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

    mvwprintw(window, ant_Y, ant_X, " ");
    mvwprintw(window, yBall, xBall, "o");
    usleep(DELAY);
}

void movePlayer(WINDOW *window)
{
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
}

void endGame(WINDOW *window)
{
    werase(window);
    nodelay(stdscr, false);
    box(window, '|', '-');

    int ganador = j1_points == PUNTOS ? 1 : 2;

    mvprintw(rows / 2 - rows / 3, 0,
             "\t\t         *******************\n"
             "\t\t         *                 *\n"
             "\t\t         *    ¡GANADOR!    *\n"
             "\t\t         *                 *\n"
             "\t\t         *    Jugador %d    *\n"
             "\t\t         *                 *\n"
             "\t\t         *******************\n",
             ganador);

    wrefresh(window);

    switch (getch())
    {
    case 'e':
    case 'E':
        end = true;
        break;
    case 'r':
    case 'R':
        initializeGame(window);
        break;
    }
}
int main(int argc, char *argv[])
{

    WINDOW *window = newWindow();
    keypad(stdscr, true);
    printTitle(window);
    wrefresh(window);
    getch();
    initializeGame(window);

    while (!end)
    {
        mvvline(0, cols / 2, ACS_VLINE, cols);
        movePlayer(window);
        moveBall(window);
        puntuacion(window);

        if (j1_points == PUNTOS || j2_points == PUNTOS)
            endGame(window);

        wrefresh(window);
    }

    endwin();
    return 0;
}
