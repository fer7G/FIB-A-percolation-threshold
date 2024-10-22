# Algoritmia-Pryecto
### Descripción del Proyecto

Este proyecto simula el proceso de percolación en diferentes tipos de grafos, incluyendo la percolación por aristas y percolación por nodos. Los grafos pueden ser generados como mallas cuadradas, grafos de Kagome, o grafos geométricos aleatorios. El programa permite analizar el umbral de percolación y los componentes conexos de estos grafos, entre otros valores.

### Archivos importantes
1. main.cc: Programa principal en C++ para simular la percolación.
2. Main.py: Script en Python para automatizar la ejecución del programa en C++ y gestionar los resultados.
3. graph_generator.py: Script en Python para generar grafos y guardarlos en formato DIMACS, necesario para la entrada del programa en C++.

### Prerrequisitos

- Compilador de C++: Necesitarás un compilador que soporte C++11 o superior.
- Python: Se requiere Python 3.x para ejecutar los scripts de automatización y generación de grafos. 
-   Para instalar las librerías necesarias de Python, ejecutar en un terminal:
`pip install -r requirements.txt`
-   Para compilar, ejecutar `make`en un terminal. 
-   Para limpiar los archivos binarios y .o, ejecutar `make clean`o `make distclean`en un terminal.


### Pasos a seguir para ejecutar el programa:

#### Generar un Grafo (Formato DIMACS):

Para generar un grafo, usa el script de Python graph_generator.py, ejecutando `python3 graph_generator.py`en un terminal. Este script soporta la generación de tres tipos de grafos:

- Malla (lattice cuadrada): Especifica las dimensiones de la cuadrícula (Int, Int).
- Kagome: Especifica las dimensiones de la cuadrícula triangular (Int, Int).
- Grafo geométrico aleatorio: Especifica el número de nodos y el radio para la formación de       aristas,un valor entre 0 y 1.

Una vez ejecutado, se guardará en el directorio de compilación un archivo .dimacs con el nombre que le hayas dado.

#### Ejecutar la simulación:
Puedes automatizar múltiples ejecuciones del programa en C++ para diferentes configuraciones usando el script Main.py. Este script se encargará de ejecutar el programa de percolación, capturar la salida y guardarla en un archivo.

Para ejecutar el script de automatización:
`python3 Main.py`
El script te pedirá:
- El tipo de percolación que quieres hacer
- El incremento que quieres usar para la probabilidad de percolación
- El nombre de los archivos que contendrán los resultados en formato de gráfica
- El nombre de los archivos .csv que contendrán los resultados numéricos
- Cuántas iteraciones quieres hacer
- Los archivos dimacs que quieres leer (Para la ejecución correcta no usar más de 7)

Una vez terminado el programa, podrás ver los resultados en los archivos .csv y .png que se habrán generadp
