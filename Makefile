# Nombre del ejecutable
TARGET = program

# Compilador y opciones
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Directorios
SRC_DIR = src
BUILD_DIR = build

# Archivos fuente y cabeceras
SRCS = $(SRC_DIR)/main.cc $(SRC_DIR)/BondPercolation.cc $(SRC_DIR)/SitePercolation.cc $(SRC_DIR)/lecturaGrafos.cc $(SRC_DIR)/UnionFind.cc
HEADERS = $(SRC_DIR)/BondPercolation.h $(SRC_DIR)/SitePercolation.h $(SRC_DIR)/lecturaGrafos.h $(SRC_DIR)/UnionFind.h

# Objetos a generar en la carpeta build/
OBJS = $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRCS))

# Regla principal
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(OBJS)

# Regla para compilar los archivos fuente en objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza de archivos generados
clean:
	rm -rf $(BUILD_DIR)

# Limpieza profunda (incluyendo archivos temporales)
distclean: clean
	rm -f *~ *.gch
