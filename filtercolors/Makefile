# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Output program name
TARGET = main

# Source files
SRC = main.cpp

# Default rule
all: $(TARGET)

# How to build the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule to remove compiled files
clean:
	rm -f $(TARGET)

# Optional: run rule to compile and execute in one step
run: all
	./$(TARGET)
