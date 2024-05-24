# Instalar paquetes necesarios
 install.packages('tuneR', dep=TRUE)
 install.packages('seewave', dep=TRUE)

# Cargar librerías
library(tuneR)
library(seewave)
library(audio)

# Cambiar directorio de trabajo
setwd("/home/rafalpv/Escritorio/Practicas/PDIH/P5")

# Leer archivos
nombre <- readWave('nombre.wav')
apellido <- readWave('apellido.wav')

# Informacion de las cabeceras
nombre
apellido

setWavPlayer("audacious")
listen(nombre)
listen(apellido)

oscillo(nombre)
oscillo(apellido)

# Calcular y redondear duración de los audios en segundos
print(paste("Duración de nombre.wav:", round(length(nombre@left) / nombre@samp.rate, 3), "segundos"))
print(paste("Duración de apellido.wav:", round(length(apellido@left) / apellido@samp.rate, 3), "segundos"))

# Unir ambos sonidos
nombre_completo <- pastew(apellido, nombre,output='Wave')
nombre_completo

listen(nombre_completo)
oscillo(nombre_completo)

# Pasar filtro de frecuencia
from_frequency <- 100
to_frequency <- 200
nombre_completo_filtrado <- bwfilter(wave = nombre_completo,channel = 1,n = 1,from = from_frequency, to=to_frequency,bandpass = TRUE,listen = FALSE,output = 'Wave')
listen(nombre_completo_filtrado)
oscillo(nombre_completo_filtrado)

# Guardar en disco
writeWave(nombre_completo_filtrado, file.path('mezcla.wav'))

# Cargar mezcla.wav
listen(nombre)

# Aplicar ECO
nombre_eco <- echo(nombre,f=22050,amp=c(0.7,0.4,0.2),delay=c(1,2,3),output="Wave")
listen(nombre_eco)
oscillo(nombre_eco)
nombre_eco_reverse <- revw(nombre_eco,output="Wave")
listen(nombre_eco_reverse)
oscillo(nombre_eco_reverse)
writeWave(nombre_eco_reverse, file.path('alreves'))

