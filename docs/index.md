# Video de Features

<iframe width="560" height="315" src="https://www.youtube.com/embed/8L4Z-yWYZ-w" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

# Instalacion rapida
 
## Cliente 
+ 1 Una vez descargado el [paquete de Debian](https://github.com/nicomatex/taller_argentum/releases/download/v1.1/argentum_1.0-1.deb), ejecutar 

```bash 
~$ sudo apt install ./argentum_1.0-1.deb 
```

+ 2 - Ejecutar el juego corriendo 

```bash
$ aoclient 
```

Luego de ejecutar el juego por primera vez, se creara el archivo de configuracion
en el directorio _~/argentum/config.json_.  

## Servidor 

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
