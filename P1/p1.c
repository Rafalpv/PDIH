#include <stdio.h>
#include <dos.h>

union REGS inregs, outregs;


void mi_pausa(){
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

// Coloca el cursor en una posición determinada
void gotoxy(){
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = 20;
	inregs.h.dl = 3;
	int86(0x10,&inregs,&outregs);
	return;
}

// Fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL Y GRUESO
void setcursortype(int type_cursor){
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
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

int main(){

	gotoxy();
    setcursortype(1);
    mi_pausa();
    setvideomode(3);


	return 0;
}
