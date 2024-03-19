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
void setcursortype(int type_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(type_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
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


unsigned char cfondo;
unsigned char ctexto;

// Modifica el color de primer plano con se mostrarán los caracteres
void textcolor(){
	ctexto = 11;
}

// Modifica el color de fondo con que se mostrarán los caracteres
void textbackgroundcolor(){
	cfondo = 5;
}


// Borra toda la pantalla
void clrscr(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// Escribe un carácter en pantalla con el color indicado actualemente
void cputchar(char c){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;    
	inregs.h.bl = cfondo << 4 | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
	return;
}

// Obtiene un carácter de teclado y lo muestra en pantalla
int getche(){
	union REGS inregs, outregs;

	inregs.h.ah = 1;
	int86(0x21,&inregs, &outregs);

	return outregs.h.al;
}

int main(){

	char tmp;

	printf("\nPulsa una tecla...");
	tmp = getche();
	printf("\nHas pulsado: ");
	cputchar(tmp);

	mi_pausa();
	

	return 0;
}
