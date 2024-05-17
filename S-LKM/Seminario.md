# Seminario LKM

Los LKM (Loadable Kernel Modules) son módulos que pueden ser cargados y descargados en el kernel de Linux en tiempo de ejecución. Esto permite extender la funcionalidad del kernel sin necesidad de recompilar o reiniciar el sistema. Los módulos pueden proporcionar controladores de dispositivo, sistemas de archivos, llamadas al sistema y más.

![Captura desde 2024-05-17 12-40-40](https://github.com/Rafalpv/PDIH/assets/116666555/8a484d00-1949-4e42-bda0-db43e3ed466e)

## Probando el módulo LKM

Para cargar el módulo utilizamos `insmod`.

```bash
sudo insmod hello.ko
```
Esto insertará el módulo en el kernel. Para verificar que el módulo se ha cargado correctamente, puedes usar el comando lsmod, que muestra todos los módulos cargados:

```bash
lsmod | grep hello
```
![Captura desde 2024-05-17 12-46-31](https://github.com/Rafalpv/PDIH/assets/116666555/b7575033-46bd-4bb6-98fa-ee0844d91eca)

Para mostrar informacion sobre el modulo utilizamos `modinfo`.

```bash
modinfo kello.ko
```
Este comando proporciona detalles sobre el módulo, como la versión, la descripción, la licencia, y más.

![Captura desde 2024-05-17 12-48-25](https://github.com/Rafalpv/PDIH/assets/116666555/2344e9f7-e812-49cf-b630-56a4d200985c)

## Descargar el módulo

Ahora descargamos el modulo utilizamos `rmmod`. 

```bash
sudo rmmod hello.ko
```
Esto eliminará el módulo del kernel. Para asegurarte de que el módulo se ha descargado, puedes volver a ejecutar lsmod y verificar que mimodulo ya no está listado.

Ahora, para ver los registros del kernel, puedes revisar el archivo de log correspondiente. Los registros del kernel se muestran en /var/log/kernel.log. Para ver estos registros, puedes usar tail o cat:

```bash
tail -f /var/log/kernel.log
```
Esto te permitirá ver los mensajes generados por el kernel, incluyendo aquellos relacionados con la carga y descarga de módulos.

![Captura desde 2024-05-17 13-11-09](https://github.com/Rafalpv/PDIH/assets/116666555/edbcefdf-6818-46e3-acd8-f22ecb4ecdff)
