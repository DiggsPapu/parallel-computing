# Define the compiler and the executable name
CC = gcc                # Usar gcc para OpenMP en lugar de mpicc
TARGET = fib
SRC = fib.c

# Default rule to compile the code with OpenMP support
all: $(TARGET)

# Compile the fib.c file into an executable with OpenMP support
$(TARGET): $(SRC)
	$(CC) -fopenmp -o $(TARGET) $(SRC)   # Añadir la opción -fopenmp

# Rule to run the executable
run: $(TARGET)
	./$(TARGET)

# Clean the directory by removing the compiled executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all run clean
