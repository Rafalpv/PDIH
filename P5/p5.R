# Instalar paquetes necesarios
install.packages('tuneR', dep=TRUE)
install.packages('seewave', dep=TRUE)

# Cargar librerías
library(tuneR)
library(seewave)
library(audio)

# Cambiar directorio de trabajo
setwd("/home/rafalpv/Escritorio/Practicas/PDIH/P5")

nombre <- readWave('nombre.wav')
apellido <- readWave('apellido.wav')

# Informacion de las cabeceras
print(nombre)
print(apellido)

# Reproducir archivos de audio
# lsiten(nombre)
# listen(apellido)

# Visualizar formas de onda
oscillo(nombre)
oscillo(apellido)

# Calcular y redondear duración de los audios en segundos
print(paste("Duración de nombre.wav:", round(length(nombre@left) / nombre@samp.rate, 3), "segundos"))
print(paste("Duración de apellido.wav:", round(length(apellido@left) / apellido@samp.rate, 3), "segundos"))

# Unir ambos sonidos
nombre_completo <- pastew(nombre,apellido,output='Wave')
nombre_completo

# Dibujar
oscillo(nombre_completo)

# Pasar filtro de frecuencia
nombre_completo_filtrado <- bwfilter(nombre_completo,channel=1,n=1,from=10000,to=20000,bandpass=TRUE,listen=FALSE,output='Wave')
oscillo(nombre_completo_filtrado)

# Guardar en disco
writeWave(nombre_completo_filtrado, file.path('mezcla.wav'))

# Cargar mezcla.wav
mezcla <- readWave('mezcla.wav')

