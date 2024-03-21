#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

BYTE FG_COLOR = 2;
BYTE BG_COLOR = 0;

void mi_pausa()
{
	union REGS inregs, outregs;
	inregs.h.ah = 8;
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

void setvideomode(unsigned char modo)
{
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = modo;
	int86(0x10, &inregs, &outregs);
	return;
}

// Obtiene el modo de video actual
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

void textcolor(int color)
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

void textbackgroundcolor(int color)
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

void rectangulo(int x1, int y1, int x2, int y2, int foreground, int background)
{
	union REGS inregs, outregs;

	clrscr();

	inregs.h.ah = 0x06;
	inregs.h.al = 0;
	inregs.h.ch = x1;
	inregs.h.cl = y1;

	textcolor(foreground);
	textbackground(background);
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
	
	return 0;
}
