# Práctica 2: Uso de bibliotecas de programación de interfaces de usuario en modo texto

![Diseño sin título](https://github.com/Rafalpv/PDIH/assets/116666555/277d01fa-379d-4827-9b19-215b901b2045)

### Introducción
Este programa implementa el juego Pong utilizando la biblioteca ncurses en C. El juego consiste en dos jugadores que controlan raquetas en cada extremo de la pantalla para golpear una pelota y evitar que atraviese su lado. El juego termina cuando un jugador consigue anotar 5 puntos.

### Librerías Utilizadas
El programa utiliza las siguientes librerías:

- `<ncurses.h>`: Proporciona funciones para manipular la pantalla del terminal y la entrada del usuario.
- `<unistd.h>`: Contiene la función `usleep()` para introducir retardos en el movimiento de la pelota.

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

---
#### Ventana de Bienvenida
![Captura desde 2024-04-12 19-52-41](https://github.com/Rafalpv/PDIH/assets/116666555/a7063cfd-746b-4565-b81d-d16cfc77f300)

#### Ventana Final 
![Captura desde 2024-04-12 19-53-28](https://github.com/Rafalpv/PDIH/assets/116666555/a54e963e-93ed-445f-9ec5-d6fbd69ac4f4)


