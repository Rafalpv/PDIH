# Práctica 1: Entrada/Salida a Bajo Nivel 

Cuando ejecutemos el programa, lo primero que veremos será un menú que lista todas las funciones disponibles. Seleccionaremos el número correspondiente a la función que queremos ejecutar y se mostrará un ejemplo de su ejecución.

![Captura desde 2024-04-02 14-35-25](https://github.com/Rafalpv/PDIH/assets/116666555/eea74684-38a2-41e6-860d-435f1f3c11eb)


## Funciones Principales

>  Coloca el cursor en una posición determinada

```c
void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = x;
	inregs.h.dl = y;
	int86(0x10,&inregs,&outregs);
	return;
}
```
![Captura desde 2024-04-02 14-56-59](https://github.com/Rafalpv/PDIH/assets/116666555/6bf69d5b-5285-4573-8db5-26e5568b3e3e)

---
> Fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL Y GRUESO
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
---
> Fija el modo de video deseado
```c
void setvideomode(unsigned char modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs);
	return;
}
```
---
> Obtiene el modo de video actual
```c
int getvideomode(){
	union REGS inregs, outregs;
	inregs.h.ah = 15; 
	int86(0x10,&inregs,&outregs); 
	return outregs.h.al;
}
```
---
> Modifica el color de primer plano o el color de fondo con que se mostrarán los caracteres
```c
void textcolor(char color){
	FG_COLOR = color;
}
```
![Captura desde 2024-04-02 14-45-42](https://github.com/Rafalpv/PDIH/assets/116666555/b7c6ea8a-0b21-439d-a8b0-243ee80c6b85)

> Modifica el color de fondo con que se mostrarán los caracteres
```c
void textbackgroundcolor(char color){
	BG_COLOR = color;
}
```
![Captura desde 2024-04-02 14-46-18](https://github.com/Rafalpv/PDIH/assets/116666555/135993d0-02d4-47cb-a6cf-321738fa4c14)

---
> Borra toda la pantalla
```c
void clrscr()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
```
Otra implementación alternativa de esta función es
```c
void clrscr(void) {
    union REGS inregs, outregs;

    inregs.h.ah = 0x06;
    inregs.h.al = 0;
    inregs.h.ch = 0;
    inregs.h.cl = 0;

    inregs.h.bh = (BACK_COLOR << 4) | TEXT_COLOR;

    inregs.h.dh = 100;
    inregs.h.dl = 100;

    int86(0x10, &inregs, &outregs);

    gotoxy(0, 0);
}
```
---
> Escribe un carácter en pantalla con el color indicado actualemente
```c
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
```
![Captura desde 2024-04-02 14-45-01](https://github.com/Rafalpv/PDIH/assets/116666555/43549b2f-d744-4195-954c-475b86f234ad)


---
> Obtiene un carácter de teclado y lo muestra en pantalla
```c
char getche(){
	union REGS inregs, outregs;
	inregs.h.ah = 1;

	int86(0x21,&inregs, &outregs);
	return outregs.h.al;
}
```
![Captura desde 2024-04-02 14-44-04](https://github.com/Rafalpv/PDIH/assets/116666555/460aa3be-0e5e-4b53-817f-81d287e29222)

---
## Función Rectangulo

> Implementar una función que permita dibujar un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y
el color de fondo.

```c
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
```

![Captura desde 2024-03-26 12-26-41](https://github.com/Rafalpv/PDIH/assets/116666555/f0496a30-1c53-4c49-996b-4a6c5605d667)
![Captura desde 2024-03-26 12-33-27](https://github.com/Rafalpv/PDIH/assets/116666555/15b759da-f784-4229-a46b-33d83fd35004)

---
## Función Pixel Art

> Implementar en lenguaje C un programa que establezca modo gráfico CGA (modo=4) para crear dibujos
sencillos en pantalla.

```c
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
```

![Captura desde 2024-03-26 12-34-31](https://github.com/Rafalpv/PDIH/assets/116666555/4cd4f922-4e3a-4b69-b8bf-510d17b21c83)




