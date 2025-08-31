# Geant4_Hola_Mundo

El proyecto consiste en observar el atenuamiento del número de particulas, energia, momento, etc,  atraves de un bloque de oro de 50x20x20 [cm], dividido en 10 trozos y ajustar a una ecuación exponencial, tipo Beer - Lambert. 

Se pueden estudiar dos casos:

1. Decaimiento de un ion de fluor F18
2. Haz de gammas monoenergeticos de 300 MeV

El proyecto consiste en varios archivos .cc. y .hh. Para un mejor control se dividen en dos carpetas "include" para las cabeceras (.hh) y "source" para los archivos fuente (.cc). Ademas, un folder "macros", para los macros de ejecución y "analysis" para contener los archivos de salida.

Breve descripcion de los archivos. Cada entrada tiene su correspondiente archivo .cc y .hh

- construction: Informacion sobre los objetos, sus dimensiones, materiales y posiciones respecto a una caja de 2m de lado, llamada mundo.
- physics: La fisica a usar en el proyecto
    - Electromagnetismo
    - Decaimiento
    - Decaimiento radioactivo
- generator: Generador de primarios, son dos opciones que se puede cambiar sobre la marcha, sin necesidad de compilar el proyecto de nuevo, a partir de un boolen *gun*
    - *gun == true*: ion estacionario
    - *gun == false*: haz de gammas monoenergeticos
- run: Informacion que tendra el archivo de salida, un arbol de root con sus ramas y hojas
- action:
- bloque: 
- detector
