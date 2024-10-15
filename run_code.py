import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os

nombre_archivo_dimacs = "malla_cuadrada.dimacs"  
num_iteraciones = 10                #Numero de veces que se aplica la perocolación con distinta q
valores_q = [round(i * 0.1, 2) for i in range(1, num_iteraciones + 1)]  


resultados = []
for q in valores_q:
    try:
        #Ejecuta el programa script.cpp con los params de entrada
        resultado = subprocess.run(["./node_percolation"], input=f"{nombre_archivo_dimacs}\n{q}\n", capture_output=True, text=True)

        if resultado.returncode == 0:
            # Extraer el número de componentes conexos de la salida
            salida = resultado.stdout
            componentes_conexos = int(salida.split(":")[-1].strip())
            resultados.append((q, componentes_conexos))
        else:
            print(f"Error en la ejecución con q = {q}:\n{resultado.stderr}")
            
    except Exception as e:
        print(f"Error al ejecutar el programa: {e}")

#Creación de los títulos de las columnas
df_cols = pd.DataFrame(resultados, columns=['q', 'Componentes Conexos'])
df_espacio = pd.DataFrame(columns=['q', 'Componentes Conexos'], index=[-1])  # Using -1 or another unique index

#Comprueba que el archivo exista, y en caso
if os.path.exists("resultados_percolacion.xlsx"):
    df_existente = pd.read_excel("resultados_percolacion.xlsx")
    df_total = pd.concat([df_existente, df_espacio, df_cols], ignore_index=True)
else:
    df_total = df_cols

# Guardar el archivo actualizado
df_total.to_excel("resultados_percolacion.xlsx", index=False)
print("Resultados acumulados guardados en 'resultados_percolacion.xlsx'")

# Generar la gráfica de línea
plt.plot(df_total['q'], df_total['Componentes Conexos'], marker='o', color='b', linestyle='-')
plt.xlabel("Valor de q")
plt.ylabel("Componentes Conexos")
plt.title("Percolación de Grafo: q vs Componentes Conexos")
plt.grid()
plt.savefig("grafica_percolacion.png")  # Guardar la gráfica como archivo de imagen
plt.show()  # Mostrar la gráfica