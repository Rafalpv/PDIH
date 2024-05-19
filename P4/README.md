# El Lenguaje de Postcript

## Cohete

Establece el grosor de las líneas a 3 unidades.
  ```postscript
  3 setlinewidth
  ```
Establece el color de las líneas usando el modelo de color RGB con los valores (0.3, 0.3, 0.3), lo que resulta en un tono de gris oscuro.
```postscript
0.3 0.3 0.3 setrgbcolor
```

Para realizar los rectangulos hemos seguido este patron de código:

```postscript
newpath
250 650 moveto
50 100 rlineto
50 -100 rlineto
closepath
stroke
```

Para realizar los circulos hemos seguido este patron de código:

```postscript
newpath
% x  y   R  angI angF
 300 600 27   0   360   arc
closepath
stroke
```
![Captura desde 2024-05-19 21-05-23](https://github.com/Rafalpv/PDIH/assets/116666555/6549f16a-f4b2-4cf1-9c48-7d74c6c04655)

## Diploma
Establece el tamaño de la página a 842x595 unidades (A4 horizontal).
```postscript
<< /PageSize [842 595] >> setpagedevice
```

Para cambiar la fuente de letra y el tamaño utilizamos la siguiente orden:

```postscript
/Legend findfont 15 scalefont setfont
```

Para añadir el texto principal, hemos utilizado este patrón de código:

```postscript
newpath
190 450 moveto
(Rafa Luque) show
190 400 moveto
(Perez-Vico) show
stroke

newpath
/Legend findfont 25 scalefont setfont
130 300 moveto
(Graduado en Perifericos y Dispositivos ) show
130 270 moveto
(de Interfaz Humana por la UGR) show
stroke
```

Para añadir el círculo relleno de color gris:
- `fill`: Rellena la figura con el color establecido.
```postscript
0.7 0.7 0.7 setrgbcolor
newpath
% x  y   R  angI angF
 670 440 70   0   360   arc
closepath
fill
stroke
```
![Captura desde 2024-05-19 21-09-31](https://github.com/Rafalpv/PDIH/assets/116666555/fcf355ae-802b-4cee-bb5d-ab6a1a3952cd)

## Corazón

Para la configuración de esta imágen hemos utilizado el siguiente trozo de codigo, donde ajustamos el tamaño de la página, el grosor de las líneas y la fuente:
```postscript
<< /PageSize [842 595] >> setpagedevice
2 setlinewidth
/Times-Roman findfont 18 scalefont setfont
```
Para mostrar el poema con las distinas tonalidades de gris:
```postscript
newpath
0.0 setgray
405 350 moveto
(Entre cables y conexiones, los perifericos se alzan,) show
stroke

newpath
0.3 setgray
405 300 moveto
(Teclado y raton, en la mesa danzan.) show
stroke

newpath
0.6 setgray
405 250 moveto
(Impresoras y escaneres, arte en cada impresion,) show
stroke

newpath
0.8 setgray
405 200 moveto
(En el mundo digital, son la extension de la creacion.) show
stroke
```


![Captura desde 2024-05-19 21-16-39](https://github.com/Rafalpv/PDIH/assets/116666555/21859f4a-8639-45a1-872e-3abdfa908e27)
