# Compiler and options
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra \
           -Wno-deprecated-declarations -Wno-missing-field-initializers

# Source and object files
SRCS = main.cpp loadimage.cpp saveimage.cpp shiftcolor.cpp
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = main

# Default target
all: $(TARGET)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all objects
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Run with custom input (usage: make run INPUT=../testpictures/volcano.png)
run: $(TARGET)
	@mkdir -p result
	@if [ -z "$(INPUT)" ]; then \
		echo "Usage: make run INPUT=<path_to_image>"; \
	else \
		./$(TARGET) $(INPUT) result/output.png; \
	fi

# Clean up compiled files and output images
clean:
	rm -f $(OBJS) $(TARGET)
	rm -f result/*

.PHONY: all run clean
