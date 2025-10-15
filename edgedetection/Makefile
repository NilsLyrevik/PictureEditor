# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -O2 -w

# Paths
SRC_DIR = src
OBJ_DIR = obj
BIN = edgedetect
RESULT_DIR = result

# Gather source and object files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(BIN)

# Build the main executable
$(BIN): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✅ Build complete!"

# Compile each .cpp to .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Run the program
# Usage: make run INPUT=../testpictures/volcano.png
run: $(BIN)
	@if [ -z "$(INPUT)" ]; then \
		echo "Usage: make run INPUT=<path_to_image>"; \
	else \
		mkdir -p $(RESULT_DIR); \
		./$(BIN) $(INPUT) $(RESULT_DIR)/output.png; \
	fi

# Clean up build files and generated images
clean:
	@rm -rf $(OBJ_DIR) $(BIN)
	@rm -f $(RESULT_DIR)/*.png
	@echo "🧹 Cleaned build files and result images!"

.PHONY: all run clean
