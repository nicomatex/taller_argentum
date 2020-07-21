# Argentum Online - Grupo 4
TP Final de 75.42 - Remake de Argentum Online

Ver Github page: https://nicomatex.github.io/taller_argentum/

## Instalacion rapida
 
### Cliente 
+ 1 Una vez descargado el paquete de debian, ejecutar 

```bash 
~$ sudo apt install ./argentum_1.0-1.deb 
```

+ 2 - Ejecutar el juego corriendo 

```bash
$ aoclient 
```

Luego de ejecutar el juego por primera vez, se creara el archivo de configuracion
en el directorio _~/argentum/config.json_.  

### Servidor 

+ 1 - Descargar el codigo fuente del servidor y crear un directorio _build_

```bash
argentum/server$ mkdir build
```

```bash
argentum/server$ cd build
```

+ 2 - Generar el MakeFile con cmake 

```bash
argentum/server/build$ cmake .. 
```

+ 3 - Compilar 

```bash
argentum/server/build$ make 
```

+ 4 - Instalar base de datos y assets en el directorio 

```bash
argentum/server/build$ make install 
```

+ 5 - Y listo! Ejecutar el servidor mediante 

```bash
argentum/server/build$ ./aoserver 
```

Toda la configuracion de parametros del juego esta en el directorio _ind_.


