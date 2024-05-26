# Instalar paquetes necesarios
install.packages('tuneR', dep = TRUE)
install.packages('seewave', dep = TRUE)

# Cargar librerías
library(tuneR)
library(seewave)
library(audio)

# Cambiar directorio de trabajo
setwd("/home/rafalpv/Escritorio/Practicas/PDIH/P5")

# Leer archivos de audio
nombre <- readWave('nombre.wav')
apellido <- readWave('apellido.wav')

# Mostrar información de las cabeceras de los archivos de audio
print(nombre)
print(apellido)

# Configurar el reproductor de audio
setWavPlayer("audacious")

# Reproducir los archivos de audio
listen(nombre)
listen(apellido)

# Mostrar oscilogramas de los archivos de audio
oscillo(nombre)
oscillo(apellido)

# Calcular y redondear la duración de los audios en segundos
nombre_duracion <- round(length(nombre@left) / nombre@samp.rate, 3)
apellido_duracion <- round(length(apellido@left) / apellido@samp.rate, 3)
print(paste("Duración de nombre.wav:", nombre_duracion, "segundos"))
print(paste("Duración de apellido.wav:", apellido_duracion, "segundos"))

# Unir ambos sonidos en uno solo
nombre_completo <- pastew(apellido, nombre, output = 'Wave')
print(nombre_completo)

# Reproducir y mostrar oscilograma del audio combinado
listen(nombre_completo)
oscillo(nombre_completo)

# Aplicar filtro de frecuencia
from_frequency <- 100
to_frequency <- 200
nombre_completo_filtrado <- bwfilter(
  wave = nombre_completo, 
  channel = 1, 
  n = 1, 
  from = from_frequency, 
  to = to_frequency, 
  bandpass = TRUE, 
  listen = FALSE, 
  output = 'Wave'
)

# Reproducir y mostrar oscilograma del audio filtrado
listen(nombre_completo_filtrado)
oscillo(nombre_completo_filtrado)

# Guardar el audio filtrado en un archivo
writeWave(nombre_completo_filtrado, 'mezcla.wav')

# Cargar y reproducir el archivo filtrado
mezcla <- readWave('mezcla.wav')
listen(mezcla)

# Aplicar efecto de eco al audio original
nombre_eco <- echo(
  nombre, 
  f = 22050, 
  amp = c(0.7, 0.4, 0.2), 
  delay = c(1, 2, 3), 
  output = "Wave"
)

# Reproducir y mostrar oscilograma del audio con eco
listen(nombre_eco)
oscillo(nombre_eco)

# Invertir el audio con eco
nombre_eco_reverse <- revw(nombre_eco, output = "Wave")

# Reproducir y mostrar oscilograma del audio invertido
listen(nombre_eco_reverse)
oscillo(nombre_eco_reverse)

# Guardar el audio invertido en un archivo
writeWave(nombre_eco_reverse, 'alreves.wav')
