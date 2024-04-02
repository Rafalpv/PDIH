#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

BYTE FG_COLOR = 2;
BYTE BG_COLOR = 0;
BYTE MODO_VIDEO = 2;

void mi_pausa()
{
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

void mi_exit()
{
	union REGS inregs, outregs;
	inregs.x.ax = 0x4C00;
	int86(0x21, &inregs, &outregs);
}

/**
 * @brief  Mueve el cursor a una posicion determinada
 *
 * La funcion llama a la subfuncion 2 de la interrupcion numero 10. Dicha subfuncion mueve el cursor a la posicion que se le indique
 *
 * @param x Indica la columna donde se quiere colocar el cursor
 * @param y Indice la fila donde se quiere colocar el cursor
 */

void gotoxy(int x, int y)
{
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = x;
	inregs.h.dl = y;
	int86(0x10, &inregs, &outregs);
	return;
}

/**
 * @brief Fija el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO
 *
 * La funcion llama a la subfuncion 1 de la interrupcion numero 10. Dicha subfuncion
 * fija el aspecto del cursor en funcion de los numeros de linea que se le indiquen
 *
 * @param type_cursor Indica el tipo de cursor que desea establecer. (INVISIBLE,NORMAL o GRUESO)
 */

void setcursortype(char type_cursor)
{
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch (type_cursor)
	{
	case '0': // invisible
		inregs.h.ch = 010;
		inregs.h.cl = 000;
		break;
	case '1': // normal
		inregs.h.ch = 010;
		inregs.h.cl = 010;
		break;
	case '2': // grueso
		inregs.h.ch = 000;
		inregs.h.cl = 010;
		break;
	}
	int86(0x10, &inregs, &outregs);
}

/**
 * @brief Fija el modo de video deseado
 *
 * La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion fija el modo de video que se le indique.
 *
 * @param modo Es un caracter que indica el modo que se desea. Dicho caracter se debe traducir al decimal adecuado
 */

void setvideomode(BYTE modo)
{
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = modo;
	int86(0x10, &inregs, &outregs);
	return;
}

/**
 * @brief Devuelve el modo de video 
 */

int getvideomode()
{
	union REGS inregs, outregs;
	inregs.h.ah = 15;
	int86(0x10, &inregs, &outregs);
	return outregs.h.al;
}

/**
 * @brief Modifica el color de primer plano con que se mostrarán los caracteres
 *
 * La funcion modifica la variable global FG_COLOR, la cual almacena el color en el que se escribe el texto por consola.
 *
 * @param color Determina el color del texto
 */

void textcolor(BYTE color)
{
	FG_COLOR = color;
}

/**
 * @brief Modifica el color de fondo con que se mostrarán los caracteres
 *
 * La funcion modifica la variable global BG_COLOR, la cual almacena el color en el que se escribe el texto por consola.
 *
 * @param color Determina el color del fondo
 */

void textbackgroundcolor(BYTE color)
{
	BG_COLOR = color;
}

/**
 * @brief Borra toda la pantalla
 *
 */

void clrscr()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/**
 * @brief Escribe un caracter en pantalla con el color indicado actualmente
 *
 * La funcion llama a la subfuncion 9 de la interrupcion numero 10. Dicha subfuncion imprime un caracter por pantalla con el color indicado y el numero de veces que se desee.
 *
 * @param c Caracter que se desea imprimir
 * @param repeticiones Numero de veces que se desea imprimir el caracter
 */

void cputchar(char c, int repeticiones)
{
	union REGS inregs, outregs;

	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = BG_COLOR << 4 | FG_COLOR;
	inregs.h.bh = 0x00;
	inregs.x.cx = repeticiones;
	int86(0x10, &inregs, &outregs);
	return;
}

/**
 * @brief Obtiene el caracter de teclado y lo muestra en pantalla
 *
 * La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion lee un caracter desde el teclado y lo almacena en el registro al. En caso de ser una tecla especial queda almacenado en el ah.
 *
 * @return Decimal que representa el caracter introducido por teclado
 */

char getche()
{
	union REGS inregs, outregs;

	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);

	return outregs.h.al;
}

void rectangulo(int x1, int y1, int x2, int y2, int fg_color, int bg_color)
{
	union REGS inregs, outregs;

	clrscr();

	inregs.h.ah = 0x06;
	inregs.h.al = 0;
	inregs.h.ch = x1;
	inregs.h.cl = y1;

	textcolor(fg_color);
	textbackgroundcolor(bg_color);
	inregs.h.bh = (BG_COLOR << 4) | FG_COLOR;

	inregs.h.dh = x2;
	inregs.h.dl = y2;

	int86(0x10, &inregs, &outregs);
}

void pixel_art()
{

	gotoxy(15, 15);
	cputchar('@', 1);
	gotoxy(15, 16);
	cputchar('.', 2);
	gotoxy(15, 18);
	cputchar('@', 1);

	gotoxy(16, 14);
	cputchar('(', 1);
	gotoxy(16, 15);
	cputchar('-', 4);
	gotoxy(16, 19);
	cputchar(')', 1);

	gotoxy(17, 13);
	cputchar('(', 1);
	gotoxy(17, 15);
	cputchar('>', 1);
	gotoxy(17, 16);
	cputchar('_', 2);
	gotoxy(17, 18);
	cputchar('<', 1);
	gotoxy(17, 20);
	cputchar(')', 1);

	gotoxy(18, 13);
	cputchar('^', 2);
	gotoxy(18, 16);
	cputchar('~', 2);
	gotoxy(18, 19);
	cputchar('^', 2);
}

int main()
{
	int opcion, i;

	do
	{
		clrscr();
		printf("\nOpciones: ");
		printf("\n\t 1 - gotoxy");
		printf("\n\t 2 - setcursortype");
		printf("\n\t 3 - setvideomode");
		printf("\n\t 4 - getvideomode");
		printf("\n\t 5 - textcolor");
		printf("\n\t 6 - textbackgroundcolor");
		printf("\n\t 7 - clrscr");
		printf("\n\t 8 - cputchar");
		printf("\n\t 9 - getche");
		printf("\n\t 10 - rectangulo");
		printf("\n\t 11 - pixer_art");
		printf("\n\t 12 - salir\n");
		printf("\n\t Introduzca una opcion: ");
		scanf("%d", &opcion);

		clrscr();

		switch (opcion)
		{
		case 1:
			printf("Cursor movido a la posicion (6,17)\n");
			gotoxy(6,17);
			mi_pausa();
			break;
		case 2:
			printf("\nCursor invisible: ");
			setcursortype('0');
			mi_pausa();

			printf("\nCursor grueso: ");
			setcursortype('2');
			mi_pausa();

			printf("\nCursor normal: ");
			setcursortype('1');
			mi_pausa();
			break;
		case 3:
			setvideomode(0);
			printf("\nResolucion 40x25 - Tipo Texto");
			mi_pausa();

			setvideomode(2);
			printf("\nResolucion 80x25 - Tipo Texto");
			mi_pausa();

			setvideomode(4);
			printf("\nResolucion 320x200 - Tipo Grafico");
			mi_pausa();

			setvideomode(2);
			break;
		case 4:
			printf("Modo  <%u>, texto\n", getvideomode());
			mi_pausa();
			break;
		case 5:
			printf("\nDefinir el color del texto:");
			printf("\n\t(0)Negro, (1)Azul, (2)Verde, (3)Cyan, (4)Rojo, (5)Magenta\n");
			scanf("%d", &FG_COLOR);
			textcolor(FG_COLOR);
			cputchar('X', 5);
			mi_pausa();
			break;
		case 6:
			printf("\nDefinir el color del fondo:");
			printf("\n\t(0)Negro, (1)Azul, (2)Verde, (3)Cyan, (4)Rojo, (5)Magenta\n");
			scanf("%d", &BG_COLOR);
			textbackgroundcolor(BG_COLOR);
			cputchar('X', 5);
			mi_pausa();
			break;
		case 7:
			for (i = 0; i < 30; i++){
				printf("\nQue Sucio!!! Pulse cualquier tecla para limpiar la pantalla");
			}
			mi_pausa();
			clrscr();
			mi_pausa();
			break;
		case 8:
			gotoxy(15,1);
			cputchar('P',1);
			gotoxy(15,2);
			cputchar('D',2);
			gotoxy(15,3);
			cputchar('I',1);
			gotoxy(15,4);
			cputchar('H',1);
			gotoxy(15,6);
			cputchar('M',1);
			gotoxy(15,7);
			cputchar('O',1);
			gotoxy(15,8);
			cputchar('L',1);
			gotoxy(15,9);
			cputchar('A',1);
			mi_pausa();
			break;
		case 9:
			printf("Introduce un caracter: ");
			printf("\nEl caracter es: %c", getche());
			mi_pausa();
			break;
		case 10:
			rectangulo(4, 9, 18, 75, 3, 5);
			mi_pausa();
			rectangulo(8, 2, 15, 75, 2, 1);
			mi_pausa();
			break;
		case 11:
			setvideomode(4);
			pixel_art();
			mi_pausa();
			setvideomode(2);
			break;
		case 12:
			mi_exit();
			break;
		}
	} while (1);

	return 0;
}