# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Wno-deprecated-declarations -Wno-missing-field-initializers

# Source and object files
SRCS = main.cpp loadimage.cpp saveimage.cpp
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main

# Default rule
all: $(TARGET)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Clean objects and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Run program
# Usage: make run INPUT=../testpictures/volcano.png
run: $(TARGET)
	@mkdir -p result
	./$(TARGET) $(INPUT) result/output.png
