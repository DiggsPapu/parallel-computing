# Define the compiler and the executable name
CC = mpicc
TARGET = mpi_hello
SRC = mpi_hello.c

# Default rule to compile the code
all: $(TARGET)

# Compile the mpi_hello.c file into an executable
$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

# Rule to run the executable with 4 processes
run: $(TARGET)
	mpiexec --allow-run-as-root -n 4 ./$(TARGET)

# Clean the directory by removing the compiled executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all run clean
