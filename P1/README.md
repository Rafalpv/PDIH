# Práctica 1: Entrada/Salida a Bajo Nivel 

## Funciones Principales

>  Coloca el cursor en una posición determinada

```c
void gotoxy(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = 20;
	inregs.h.dl = 3;
	int86(0x10,&inregs,&outregs);
	return;
}
```
> // Fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL Y GRUESO
```c
void  setcursortype(char  type_cursor){
	union  REGS  inregs, outregs;
	inregs.h.ah  =  0x01;
	switch(type_cursor){
		case  '0': //invisible
			inregs.h.ch  =  010;
			inregs.h.cl  =  000;
			break;
		case  '1': //normal
			inregs.h.ch  =  010;
			inregs.h.cl  =  010;
			break;
		case  '2': //grueso
			inregs.h.ch  =  000;
			inregs.h.cl  =  010;
			break;
	}
int86(0x10, &inregs, &outregs);
}
```
