#include <stdio.h>
#include <dos.h>

void mi_pausa(){
	union REGS inregs, outregs;
 	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

// Coloca el cursor en una posición determinada
void gotoxy(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = 20;
	inregs.h.dl = 3;
	int86(0x10,&inregs,&outregs);
	return;
}

// Fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL Y GRUESO
void setcursortype(char type_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(type_cursor){
		case '0': //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case '1': //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case '2': //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

// Fija el modo de video deseado
void setvideomode(unsigned char modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs);
	return;
}

// Obtiene el modo de video actual
int getvideomode(){
	union REGS inregs, outregs;
	inregs.h.ah = 15; 
	int86(0x10,&inregs,&outregs); 
	return outregs.h.al;
}

unsigned char ctexto;
unsigned char cfondo;

// Modifica el color de primer plano con se mostrarán los caracteres
void textcolor(char color){
	ctexto = color;
}

// Modifica el color de fondo con que se mostrarán los caracteres
void textbackgroundcolor(char color){
	cfondo = color;
}

// Borra toda la pantalla
void clrscr(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// Escribe un carácter en pantalla con el color indicado actualemente
void cputchar(char c){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;    //una funcion más general debe recibir el caracter a imprimir
	inregs.h.bl = cfondo << 4 | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
	return;
}

// Obtiene un carácter de teclado y lo muestra en pantalla
char getche(){
	union REGS inregs, outregs;

	inregs.h.ah = 1;
	int86(0x21,&inregs, &outregs);

	return outregs.h.al;
}

int main(){

	unsigned char tmp;

	clrscr();
	
	printf("\nAspecto del cursor INVISIBLE(0), NORMAL(1), GRUESO(2): ");
	tmp=getche();
	setcursortype(tmp);

	printf("\nSelecciona el color de fuente...");
	tmp=getche();
	textcolor(tmp);
	
	printf("\nSelecciona el color de fondo...");
	tmp=getche();
	textbackgroundcolor(tmp);

	printf("\nPulsa una tecla...");
	tmp=getche();

	printf("\nHas pulsado: ");
	cputchar(tmp);

	mi_pausa();
	
	return 0;
}
