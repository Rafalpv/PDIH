# Experimentación con el sistema de salida de sonido

Primero, cargamos las librerías necesarias para la práctica:
```R
library(tuneR)
library(seewave)
library(audio)
```
Definimos el directorio de trabajo:
```R
setwd("/home/rafalpv/Escritorio/Practicas/PDIH/P5")
```
Leemos dos archivos de sonido con extensión .wav:
```R
nombre <- readWave('nombre.wav')
apellido <- readWave('apellido.wav')
```
Mostramos información sobre ambos archivos:
```R
print(nombre)
print(apellido)
```
![Informacion nombre+apellido](https://github.com/Rafalpv/PDIH/assets/116666555/ac927e68-d7f7-48b3-ad27-0b60703e116b)

Establecemos el reproductor de sonido, en nuestro caso, utilizamos Audacious en Linux:
```R
setWavPlayer("audacious")
```

Para reproducir los archivos, utilizamos la función listen:
```R
listen(nombre)
listen(apellido)
```
[Nombre+Apellido.webm](https://github.com/Rafalpv/PDIH/assets/116666555/b672aedd-c310-414e-9a97-9732ec0ac1b4)

Para dibujar la forma de onda de los sonidos:
```R
oscillo(nombre)
oscillo(apellido)
```
![Nombre](https://github.com/Rafalpv/PDIH/assets/116666555/a86ee346-76ac-4600-89fb-fe6bac018936)
![Apellidos](https://github.com/Rafalpv/PDIH/assets/116666555/28edb2b4-9d7b-4bb1-a3e3-6e2c564f0b52)

Unimos ambos sonidos con la función `pastew` y mostramos su información:
```R
nombre_completo <- pastew(apellido, nombre,output='Wave')
nombre_completo
```
![Informacion nombre_completo](https://github.com/Rafalpv/PDIH/assets/116666555/88a01751-d76b-4604-ac6b-3fb09952b868)

Dibujamos la forma de la gráfica resultante de haber unido ambos sonidos:
![Nombre Completo](https://github.com/Rafalpv/PDIH/assets/116666555/c06daf43-a25f-4fe2-b6c0-fa4b554508d1)

Para pasaarle un filtro de frecuencia para eliminar las frecuencias entre 100Hz y 200Hz:
```R
from_frequency <- 100
to_frequency <- 200
nombre_completo_filtrado <- bwfilter(wave = nombre_completo,channel = 1,n = 1,from = from_frequency, to=to_frequency,bandpass = TRUE,listen = FALSE,output = 'Wave')
```
![Nombre completo filtrado](https://github.com/Rafalpv/PDIH/assets/116666555/1ba6d67b-6f26-4078-9930-ad6157a0e2c4)

Para guardar la señal anterior en un fichero WAV, utilizamos `writeWave`:
```R
writeWave(nombre_completo_filtrado, file.path('mezcla.wav'))
```

Utilizamos el primer archivo que cargamos donde se reproducia el nombre. A este archivo vamos a aplicarle eco:
```R
```



