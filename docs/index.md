# Video de Features

<iframe width="560" height="315" src="https://www.youtube.com/embed/8L4Z-yWYZ-w" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

# Instalacion rapida
 
## Cliente 
1. Una vez descargado el paquete de debian, ejecutar 

``` ~$ sudo apt install ./argentum_1.0-1.deb ```.

2. Ejecutar el juego corriendo 

``` $ aoclient ```

Luego de ejecutar el juego por primera vez, se creara el archivo de configuracion
en el directorio _~/argentum/config.json_.  

## Servidor 

1. Descargar el codigo fuente del servidor y crear un directorio _build_

```argentum/server$ mkdir build```

```argentum/server$ cd build```

2. Generar el MakeFile con cmake 

```argentum/server/build$ cmake .. ```

3. Compilar 

```argentum/server/build$ make ```

4. Instalar base de datos y assets en el directorio 

```argentum/server/build$ make install ```

5. Y listo! Ejecutar el servidor mediante 

```argentum/server/build$ ./aoserver ```

Toda la configuracion de parametros del juego esta en el directorio _ind_.
