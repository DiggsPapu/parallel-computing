# Variables
CXX = g++
CXXFLAGS = -fopenmp -Wall
# TARGET = Ejercicio1
# SOURCES = Ejercicio1.cpp
TARGET = Ejercicio2
SOURCES = Ejercicio2.cpp
CSVFILES = numeros.csv numeros_ordenados.csv

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Run the program
run: clean_csv $(TARGET)
	./$(TARGET)

# Clean the CSV files
clean_csv:
	rm -f $(CSVFILES)

# Clean all generated files
clean: clean_csv
	rm -f $(TARGET)

# Phony targets
.PHONY: all run clean clean_csv
