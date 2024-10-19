---
tags:
links:
created: 2024-10-08T23:46
modified: 2024-10-19T13:19
---
# Referencias y cosas interesantes para el proyecto

A continuación se mencionan algunas referencias y conceptos interesantes para el proyecto.

## Literatura

- **Percolation**, libro de **Geoffrey Grimmet** (1999)
  Disponible en: http://lib.ysu.am/open_books/417531.pdf
  Libro sobre teoría de la percolación desde 0. El autor es una referencia estándar en este
  campo.
  
- **Probability Theory: The Coupling Method** (*Coupling lectures*) (2012)
  Disponible en: https://mathematicaster.org/teaching/lcs22/hollander_coupling.pdf
  Apuntes de teoría de la probabilidad de una universidad holandesa. En este caso la percolación es un ejemplo de *Coupling* (un método para comparar variables aleatorias). Está bien porque se basa en el libro de Geoffrey Grimmet en la parte de Teoría de la Percolación.

- **Percolation Thresholds and Fisher Exponents in Hypercubic Lattices** (2018)
  Disponible en: https://arxiv.org/pdf/1806.08067
  Paper breve que puede servir como referencia para la experimentación. Usan invasion percolation para buscar el umbral crítico $p_c$ (donde se produce la transición de fase) en rejillas $\mathbb{Z}^d$.

- **Percolation processes**, Broadbent and Hammersley (1957)
  Disponible en: no encontrado con acceso no restringido
  Artículo original sobre los procesos de percolación

- **PAPER (*MUY IMPORTANTE*) - HK algorithm for estimation of percolation in square lattice using Python programing** (2020)
  Estimación del umbral de percolación usando el algoritmo Hoshen-Kopelman (basado en union-find). Estiman este umbral cuando existe un camino entre el top y el bottom de la cuadrícula. Es lo más parecido a lo nuestro si no idéntico.
  
- **PAPER - A technique for the estimation of percolation thresholds in lattice systems: Application to a problem of granular flow through an orifice** (2023)
  El método se basa en calcular las probabilidades de encontrar un clúster percolante de diferentes tipos (horizontal, vertical, etc.) en una cuadrícula finita de tamaño **L**. A partir de estas simulaciones numéricas, se estiman los umbrales efectivos y luego se extrapolan para obtener el **p_c** en el límite termodinámico (tamaño infinito). Esta técnica mejora un esquema clásico y se valida comparando con resultados previos para percolación en redes cuadradas. Finalmente, aplican la técnica para modelar transiciones de taponamiento en un silo 2D con base vibrada.

- **PAPER - Percolation for D2D Networks on Street Systems** (2018)
  Este paper estudia la **conectividad en redes D2D (device-to-device)** donde los dispositivos se distribuyen aleatoriamente en sistemas de calles modelados por **teselaciones Poisson-Voronoi** o **Poisson-Delaunay**. Los dispositivos pueden comunicarse si están a una distancia menor que un umbral de conectividad. El problema se aborda como una cuestión de **percolación** en un grafo aleatorio subyacente, donde se analiza la **intensidad crítica de dispositivos** para que la red percole, es decir, para que se forme un componente gigante conectado. El estudio también compara el **modelo de Poisson Boolean** para áreas urbanas y rurales, mostrando que en áreas rurales la probabilidad de percolación permanece baja incluso muy por encima del umbral crítico.

- **PAPER - Understanding percolation phase transition behaviors in complex networks from the macro and meso-micro perspectives** (2022)
  Este paper explora el **comportamiento de la transición de fase en redes complejas** desde dos perspectivas: **macroscópica** y **meso-micro**. Desde el punto de vista macro, se analiza cómo los sistemas de red muestran transiciones de fase de segundo orden cuando fallan y se desconectan, destacando el papel del **componente gigante** (la mayor parte conectada de la red). Sin embargo, también se estudia desde una perspectiva más fina (meso-micro) el impacto de los **componentes de tamaño finito**, que pueden influir en la conectividad de redes a gran escala. El estudio se aplica tanto a redes individuales como a redes acopladas, que pueden mostrar transiciones de fase más complejas según los mecanismos de acoplamiento. Este enfoque proporciona una visión más completa de cómo las redes se comportan ante fallos y percolación, con aplicaciones en redes adaptativas y de orden superior. 

- **PAPER - On the estimation of percolation thresholds for real networks** (2022)
  Este paper aborda la **estimación del umbral de percolación** (p_c) en redes reales, que tienen estructuras más complejas que los modelos de red regulares. Propone una mejora al algoritmo tradicional de **message passing** (difusión de mensajes), incorporando correcciones relacionadas con la independencia de variables en las ecuaciones iterativas. Usan un modelo de **regresión por gradiente** para predecir una corrección **δs(b)**, que ajusta los cálculos del umbral de percolación, haciéndolos más precisos. Finalmente, muestran que sus estimaciones para los umbrales de percolación (por sitios y por aristas) son más precisas que los métodos actuales en 209 redes reales. 

- **PAPER (*INTERESANTE*) - Percolation, Renormalization and the Quantum-Hall Transition** (2001)
  Este paper ofrece una **introducción pedagógica** a la teoría de la percolación, haciendo especial énfasis en los **algoritmos** utilizados para estudiarla numéricamente. El enfoque principal está en el tratamiento del problema de percolación utilizando el **grupo de renormalización en el espacio real**, una técnica para simplificar sistemas complejos. Además, como una aplicación novedosa, el artículo revisa cómo estas ideas de renormalización se han aplicado para estudiar la **transición de Hall cuántico**, un fenómeno en la física de materiales.
  
- **PAPER - Connectivity in Two-Dimensional Lattice Networks**
  Este paper se enfoca en el **problema de conectividad dirigida** en redes de cuadrículas 2D, que es una variación del problema de percolación. En lugar de estudiar la aparición de un clúster gigante en toda la red, aquí se analiza la **conectividad desde una fuente** a cualquier vértice siguiendo ciertas direcciones. Aunque la percolación dirigida ha sido estudiada ampliamente mediante simulaciones, este trabajo introduce una **expresión analítica** usando un enfoque de **descomposición recursiva** para resolver el problema. Estas fórmulas son aplicables a **redes ad hoc** como las redes móviles y vehiculares.
  
- **PAPER - Percolation of randomly distributed growing clusters: Finite-size scaling and critical exponents for the square lattice** (2010)
  Este paper estudia las propiedades de percolación en un modelo de **crecimiento de clústeres** en una cuadrícula 2D. Se colocan "semillas" en posiciones aleatorias, y cada una crece formando clústeres hasta que dos o más clústeres se tocan, momento en el cual se detienen. El estudio revela que hay una transición de fase **discontinua** para concentraciones de semillas bajas, y una **transición continua** no trivial para valores intermedios de la concentración. Utilizando técnicas de escalado finito y simulaciones Monte Carlo, identifican el umbral de percolación y los exponentes críticos, demostrando que esta transición pertenece a una **clase de universalidad** distinta a la de la percolación estándar.
  
- **LIBRO - Introduction to Percolation Theory** (1994)

- **PAPER - Interpretation of percolation in terms of infinity computations** (2012)
  Este paper propone una nueva metodología computacional que permite trabajar con cantidades infinitas e infinitesimales utilizando un concepto llamado **Infinity Computer**. El enfoque se aplica a la teoría de la percolación, específicamente a la **percolación por sitios** y la **percolación por gradiente**. A diferencia de la visión tradicional, donde la transición de fase ocurre en un punto crítico, este método sugiere que la transición es un **intervalo crítico** que puede ser finito, infinito o infinitesimal dependiendo del "microscopio" utilizado. Además, sugiere que cerca del umbral de percolación pueden existir varios clústeres infinitos en lugar de solo uno.
  
- **PAPER - Modeling myosin Va liposome transport through actin filament networks reveals a percolation threshold that modulates transport properties** (2021)
  Este paper presenta un modelo computacional simplificado para estudiar cómo los **motores de miosina Va (myoVa)** transportan liposomas a través de redes de filamentos de actina tridimensionales. El estudio simula el comportamiento de los liposomas (de diferentes tamaños) moviéndose en una red aleatoria de filamentos de actina, y explora cómo la **densidad de filamentos** afecta su transporte. A medida que la densidad de actina aumenta, los liposomas experimentan una **transición de fase de percolación**: pasan de un transporte dirigido en un solo filamento a un "camino aleatorio" debido a encuentros con más filamentos (generando eventos de "tira y afloja"). Esta transición está controlada por un número crítico de filamentos accesibles, **Nc**, que depende de la geometría de la red y del tamaño de los liposomas. El estudio sugiere que las células pueden ajustar la densidad de su red de actina y el tamaño del cargo para optimizar el transporte según sus necesidades fisiológicas.

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

