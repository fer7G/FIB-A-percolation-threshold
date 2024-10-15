# Nombre del ejecutable
TARGET = programa

# Compilador y opciones
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Archivos fuente y cabeceras
SRCS = main.cc BondPercolation.cc SitePercolation.cc lecturaGrafos.cc UnionFind.cc
HEADERS = BondPercolation.h SitePercolation.h lecturaGrafos.h UnionFind.h

# Objetos a generar
OBJS = $(SRCS:.cc=.o)

# Regla principal
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar los archivos fuente en objetos
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza de archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Limpieza profunda (incluyendo archivos temporales)
distclean: clean
	rm -f *~ *.gch
