# Referencias y cosas interesantes para el proyecto

A continuación se mencionan algunas referencias y conceptos interesantes para el proyecto.

## Literatura

- **Percolation**, libro de **Geoffrey Grimmet** (1999)
  Disponible en: http://lib.ysu.am/open_books/417531.pdf
  Libro sobre teoría de la percolación desde 0. El autor es una referencia estándar en este campo.
  
- **Probability Theory: The Coupling Method** (*Coupling lectures*) (2012)
  Disponible en: https://mathematicaster.org/teaching/lcs22/hollander_coupling.pdf
  Apuntes de teoría de la probabilidad de una universidad holandesa. En este caso la percolación es un ejemplo de *Coupling* (un método para comparar variables aleatorias). Está bien porque se basa en el libro de Geoffrey Grimmet en la parte de Teoría de la Percolación.

- **Percolation Thresholds and Fisher Exponents in Hypercubic Lattices** (2018)
  Disponible en: https://arxiv.org/pdf/1806.08067
  Paper breve que puede servir como referencia para la experimentación. Usan invasion percolation para buscar el umbral crítico $p_c$ (donde se produce la transición de fase) en rejillas $\mathbb{Z}^d$.

- **Percolation processes**, Broadbent and Hammersley (1957)
  Disponible en: no encontrado con acceso no restringido
  Artículo original sobre los procesos de percolación

## Conceptos

- Invasion percolation

- Dualidad de las rejillas
  
- Infinite open cluster (cómo determinamos un open clúster? Suponemos que es algo asintítico, como en los costes temporales)

- Qué marca realmente la transición de fase que nos piden? La conectividad del grafo? Encontrar este gran clúster?

- Un *bond model* puede ser reformulado como un *site model* pero no al revés. Los *site models* son más generales.

- **Elbow method** (Método del codo)
  Nos puede servir para ver a partir de qué número de experimentaciones deberíamos parar. Usamos una métrica que mida la estabilidad de los resultados para hacer la "optimización" como puede ser la varianza:

	- Al principio, aumentar el número de experimentos reduce la varianza o mejora la estabilidad de los resultados rápidamente.
	  
	- En algún punto, la mejora empieza a ser mínima, formando un "codo" en el gráfico. Ese es el punto donde realizar más experimentos **no agrega valor significativo**, porque los resultados ya son bastante consistentes. 