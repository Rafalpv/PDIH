install.packages('tuneR', dep=TRUE)
install.packages('seewave', dep=TRUE)

library(tuneR)
library(seewave)
library(audio)

setwd("/home/rafalpv/Escritorio/Practicas/PDIH/P5")

nombre<-readWave('nombre.wav')
str(nombre)
apellido<-readWave('apellido.wav')
apellido
listen(apellido)
plot(nombre)

round(length(nombre@left)/nombre@samp.rate, 3)
round(length(apellido@left)/apellido@samp.rate, 3)




