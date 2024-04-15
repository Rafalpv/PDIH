# Práctica 2: Uso de bibliotecas de programación de interfaces de usuario en modo texto

### Introducción
En esta práctica, nos enfocaremos en la biblioteca ncurses, la cual ofrece una API para desarrollar interfaces basadas en texto.

ncurses añade una capa sobre las capacidades del terminal, permitiendo a los desarrolladores crear interfaces de usuario en modo texto. Esta biblioteca posibilita la creación sencilla de aplicaciones con ventanas, menús, paneles y formularios. Una característica destacada es la capacidad de gestionar las ventanas de forma independiente, lo que facilita su movimiento, así como la opción de ocultarlas o mostrarlas según sea necesario.

### Instalación y Compilacion

Para instalar la librería en Linux deberemos hacer uso del comando
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```

Para compilar los programas
```
gcc <nombre_archivo.c> -o <nombre_ejecutable> -lncurses
```

### Librerías Utilizadas
Los programas que veremos a continnuación utilizan las siguientes librerías:
- `<ncurses.h>`: Proporciona funciones para manipular la pantalla del terminal y la entrada del usuario.
- `<unistd.h>`: Contiene la función `usleep()` para introducir retardos en el movimiento de la pelota.

## EJEMPLO 1: Crear Ventana
En este ejemplo básico veremos los conceptos básicos para mostrar una ventana en la terminal con marcos y un color de fondo y mostrar contenido por la misma.
```c
#include <stdlib.h>
#include <ncurses.h>
int main(void)
{
    int rows, cols;
    initscr();
    if (has_colors() == FALSE)
    {
        endwin();
        printf("El terminal no tiene soporte de color \n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    // blanco sobre fondo azul
    clear();
    refresh();
    getmaxyx(stdscr, rows, cols);
    WINDOW *window = newwin(rows, cols, 0, 0);
    wbkgd(window, COLOR_PAIR(3));
    box(window, '|', '-');
    mvwprintw(window, 10, 10, "una cadena");
    wrefresh(window);
    getch();
    endwin();
    return 0;
}
```

![Captura desde 2024-04-15 14-01-05](https://github.com/Rafalpv/PDIH/assets/116666555/43bb7c2f-402c-45a5-b858-deeb18dc12ec)

## EJEMPLO 2: Mover Pelota 
En este segundo ejemplo veremos como se simular el movimiento horizontal de una pelota.

```c
#include <ncurses.h>
#include <unistd.h>
#define DELAY 30000
int main(int argc, char *argv[])
{
    int x = 0, y = 0;
    int max_y = 50, max_x = 50;
    int next_x = 0;
    int direction = 1;
    initscr();
    noecho();
    curs_set(FALSE);
    while (1)
    {
        clear();
        mvprintw(y, x, "o");
        refresh();
        usleep(DELAY);
        next_x = x + direction;
        if (next_x >= max_x || next_x < 0)
            direction *= -1;
        else
            x += direction;
    }
    endwin();
}
```
[move_ball_ejemplo.webm](https://github.com/Rafalpv/PDIH/assets/116666555/71ee03ee-2a18-4423-85be-e969a832be15)

## PONG

Este programa implementa el juego Pong utilizando la biblioteca ncurses en C. El juego consiste en dos jugadores que controlan raquetas en cada extremo de la pantalla para golpear una pelota y evitar que atraviese su lado. El juego termina cuando un jugador consigue anotar 5 puntos.

https://github.com/Rafalpv/PDIH/assets/116666555/31fceb29-5c35-43bb-82d0-706ea2332caa

#### Ventana de Bienvenida
![Captura desde 2024-04-15 12-30-33](https://github.com/Rafalpv/PDIH/assets/116666555/17a4cccc-9c52-4b7b-8ce7-1074ec342561)

#### Ventana Final 
![Captura desde 2024-04-12 19-53-28](https://github.com/Rafalpv/PDIH/assets/116666555/a54e963e-93ed-445f-9ec5-d6fbd69ac4f4)

### Definiciones y Variables Globales
- `DELAY`: Define el retardo entre cada movimiento de la pelota.
- `PUNTOS`: Define el número de puntos necesarios para ganar.
- `end`: Booleano que indica si el juego ha terminado.
- `j1_points`, `j2_points`: Almacenan los puntos de cada jugador.
- `max_Y`, `max_X`: Almacenan las dimensiones de la pantalla.
- `jug1`, `jug2`: Almacenan las posiciones verticales de las raquetas de los jugadores.
- `ball_X`, `ball_Y`: Almacenan la posición de la pelota.
- `next_X`, `next_Y`: Almacenan la próxima posición de la pelota.
- `direction_X`, `direction_Y`: Almacenan la dirección del movimiento de la pelota.
- `ant_X`, `ant_Y`: Almacenan las posiciones anteriores de la pelota.

### Funciones

#### `newWindow()`
- Inicializa la pantalla ncurses y crea una nueva ventana.
- Configura el color de fondo y los pares de colores.
- Devuelve la ventana creada.

#### `printTitle(WINDOW *window)`
- Imprime el título y las instrucciones del juego en la ventana especificada.

#### `resetBall(WINDOW *window)`
- Coloca la pelota en el centro de la pantalla.

#### `resetPlayers(WINDOW *window)`
- Coloca las raquetas de los jugadores en sus posiciones iniciales.

#### `resetMarcador(WINDOW *window)`
- Reinicia el marcador de puntos en la ventana especificada.

#### `initializeGame(WINDOW *window)`
- Inicializa el juego limpiando la ventana y configurando los elementos iniciales del juego.

#### `puntuacion(WINDOW *window)`
- Maneja el aumento de puntos cuando un jugador anota.
- Reinicia la posición de la pelota y cambia su dirección.
- Introduce un pequeño retardo para dar tiempo al jugador a reaccionar.

#### `moveBall(WINDOW *window)`
- Calcula la siguiente posición de la pelota y maneja las colisiones con las paredes y las raquetas.
- Actualiza la posición de la pelota en la ventana.

#### `movePlayer(WINDOW *window)`
- Maneja el movimiento de las raquetas de los jugadores en función de las teclas presionadas por el usuario.

#### `endGame(WINDOW *window)`
- Muestra un mensaje de fin de juego con el ganador y las instrucciones para reiniciar o salir.
- Espera la entrada del usuario para reiniciar el juego o salir.

### Función Principal (`main`)
- Inicializa la ventana y muestra el título del juego.
- Espera la entrada del usuario para comenzar el juego.
- Inicializa el juego y entra en un bucle principal que maneja el movimiento de la pelota y de los jugadores.
- Comprueba si se han anotado puntos o si se ha alcanzado el límite de puntos para terminar el juego.
- Sale del bucle principal cuando el juego termina.
- Limpia la pantalla y dependiendo de la tecla pulsada, reinicia el juego o finaliza el programa.



