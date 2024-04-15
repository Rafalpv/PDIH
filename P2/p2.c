#include <ncurses.h>
#include <unistd.h>

#define DELAY 35000
#define PUNTOS 5

bool end = false;
int j1_points = 0, j2_points = 0,
    max_Y, max_X,
    jug1, jug2,
    ball_X, ball_Y,
    next_X, next_Y,
    direction_X = 1, direction_Y = 1,
    ant_X, ant_Y;

WINDOW *newWindow()
{
    initscr();
    curs_set(FALSE);
    start_color();
    noecho();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    refresh();

    getmaxyx(stdscr, max_Y, max_X);
    WINDOW *window = newwin(max_Y, max_X, 0, 0);
    box(window, '|', '-');
    return window;
}

void printTitle(WINDOW *window)
{
    mvprintw(max_Y / 2 - max_Y / 3, 0, "\t\t oooooooooo                                        \n"
                                       "\t\t 888    888  ooooooo    ooooooo    oooooooo8       \n"
                                       "\t\t 888oooo88 888     888 888   888  888    88o       \n"
                                       "\t\t 888       888     888 888   888   888oo888o       \n"
                                       "\t\t o888o        88ooo88  o888o o888o 888     888      \n"
                                       "\t\t                                   888ooo888     \n\n"
                                       "\t\t -> JUGADOR 1 (izquierda) tus controles son 'w/W' y 's/S' \n"
                                       "\t\t -> JUGADOR 2 (derecha) tus controles son 'o/O' y 'l/L' \n"
                                       "\t\t -> p/P' para poner en pausa \n\n"
                                       "\t\t  EL JUGADOR QUE ANOTE 5 PUNTOS GANA LA PARTIDA. SUERTE!\n\n"
                                       "\t\t  PULSA CUALQUIER TECLA PARA COMENZAR");
}

void resetBall(WINDOW *window)
{
    ball_X = max_X / 2,
    ball_Y = max_Y / 2 - 1,
    mvwprintw(window, max_Y / 2 - 1, max_X / 2, "o");
}

void resetPlayers(WINDOW *window)
{
    jug1 = max_Y / 2 - 1,
    jug2 = max_Y / 2 - 1;
    for (int i = 0; i < 3; i++)
    {
        mvwprintw(window, max_Y / 2 - i, 1, "|");
        mvwprintw(window, max_Y / 2 - i, max_X - 2, "|");
    }
}

void resetMarcador(WINDOW *window)
{
    j1_points = 0,
    j2_points = 0,
    mvwprintw(window, 3, max_X / 2 + max_Y / 10, "0");
    mvwprintw(window, 3, max_X / 2 - max_Y / 10, "0");
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
    if (ball_X == -1)
        j2_points++;
    else
        j1_points++;

    resetBall(window);
    direction_X *= -1;
    usleep(20000);
}

void moveBall(WINDOW *window)
{
    next_X = ball_X + direction_X;
    next_Y = ball_Y + direction_Y;

    if (next_X == 1 && (next_Y >= jug1 - 1 && next_Y <= jug1 + 1) || next_X == max_X - 2 && (next_Y >= jug2 - 1 && next_Y <= jug2 + 1))
        direction_X *= -1;

    ant_X = ball_X;
    ant_Y = ball_Y;

    if (next_X > max_X || next_X < -1)
        direction_X *= -1;
    else
        ball_X += direction_X;

    if (next_Y >= max_Y || next_Y < 0)
        direction_Y *= -1;
    else
        ball_Y += direction_Y;

    mvwprintw(window, ant_Y, ant_X, " ");
    mvwprintw(window, ball_Y, ball_X, "o");
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
        if (jug1 + 2 < max_Y)
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
            mvwprintw(window, jug2 + 1, max_X - 2, " ");
            mvwprintw(window, jug2 - 2, max_X - 2, "|");
            jug2--;
        }

        break;
    case 'l':
    case 'L':
        if (jug2 + 2 < max_Y)
        {
            mvwprintw(window, jug2 - 1, max_X - 2, " ");
            mvwprintw(window, jug2 + 2, max_X - 2, "|");
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

    mvprintw(max_Y / 2 - max_Y / 3, 0,
             "\t\t\t *******************\n"
             "\t\t\t *                 *\n"
             "\t\t\t *    ¡GANADOR!    *\n"
             "\t\t\t *                 *\n"
             "\t\t\t *    Jugador %d    *\n"
             "\t\t\t *                 *\n"
             "\t\t\t *  ¡ENHORABUENA!  *\n"
             "\t\t\t *                 *\n"
             "\t\t\t *******************\n"
             "\n\n"
             "\t\t\t -> Pulse la Tecla 'R' para Reiniciar\n"  
             "\t\t\t -> Pulse la Tecla 'E' para Salir",
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
        mvvline(0, max_X / 2, ACS_VLINE, max_X);
        mvwprintw(window, 3, max_X / 2 - max_Y / 10, "%d", j2_points);
        mvwprintw(window, 3, max_X / 2 + max_Y / 10, "%d", j1_points);
        movePlayer(window);
        moveBall(window);

        if (ball_X == -1 || ball_X == max_X)
            puntuacion(window);

        if (j1_points == PUNTOS || j2_points == PUNTOS)
            endGame(window);

        wrefresh(window);
    }

    endwin();
    return 0;
}
