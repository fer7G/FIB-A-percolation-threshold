# Simulación de percolación de grafos
### Descripción del Proyecto

Este proyecto simula el proceso de percolación en diferentes tipos de grafos, incluyendo la percolación por aristas y percolación por nodos. Los grafos pueden ser generados como mallas cuadradas, grafos de Kagome, o grafos geométricos aleatorios. El programa permite analizar el umbral de percolación y los componentes conexos de estos grafos, entre otros valores.

### Archivos importantes
1. main.cc: Programa principal en C++ para simular la percolación.
2. Main.py: Script en Python para automatizar la ejecución del programa en C++ y gestionar los resultados.
3. graph_generator.py: Script en Python para generar grafos y guardarlos en formato DIMACS, necesario para la entrada del programa en C++.
4. calculateBeta.py: Script python que permite calcular el exponente beta de nuestros resultados.

### Prerrequisitos

- Compilador de C++: Necesitará un compilador que soporte C++11 o superior.
- Python: Se requiere Python 3.x para ejecutar los scripts de automatización y generación de grafos. 
-   Para instalar las librerías necesarias de Python, ejecutar en un terminal:
`pip install -r requirements.txt`
-   Para compilar, ejecutar `make`en un terminal. 
-   Para limpiar los archivos binarios y .o, ejecutar `make clean`o `make distclean`en un terminal.


### Pasos a seguir para ejecutar el programa:

#### Ejecutar la simulación:
Puede automatizar múltiples ejecuciones del programa en C++ para diferentes configuraciones usando el script Main.py. Este script se encargará de generar los grafos, ejecutar el programa de percolación, capturar la salida y guardarla en un archivo.

Para ejecutar el script de automatización:
`python3 Main.py`

Antes de proceder a las ejecuciones, el programa le dará la opción de generar un grafo nuevo. En el caso de que lo desee, el programa le pedirá el tipo de grafo y sus parámetros:

- Malla (lattice cuadrada): Especifica las dimensiones de la cuadrícula (Int, Int).
- Kagome: Especifica las dimensiones de la cuadrícula triangular (Int, Int).
- Grafo geométrico aleatorio: Especifica el número de nodos.

Una vez ejecutado, se guardará en el directorio de compilación un archivo .dimacs con el nombre que le haya dado.


Tras la generación opcional del grafo, el script le pedirá los siguientes parámetros obligatorios:
- El tipo de percolación que desee hacer
- El incremento que quiere usar para la probabilidad de percolación
- El nombre de los archivos que contendrán los resultados en formato de gráfica
- El nombre de los archivos .csv que contendrán los resultados numéricos
- Cuántas iteraciones desea hacer
- Los archivos dimacs que quiere leer (Para la ejecución correcta no usar más de 7)

Una vez terminado el programa, se podrán ver los resultados en los archivos .csv y .png que se habrán generado.
