# --- Compiler and flags ---
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra

# --- Paths ---
SRC_DIR := src
OBJ_DIR := obj
RESULT_DIR := result
BIN := main

# --- Files ---
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# --- Arguments ---
INPUT ?= ../testpictures/volcano.png
OUTPUT := $(RESULT_DIR)/output.png
COLOR ?= false

# --- Rules ---
all: $(BIN)

$(BIN): $(OBJS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(BIN)
	@mkdir -p $(RESULT_DIR)
ifeq ($(COLOR),true)
	@echo "Running in COLOR mode..."
	./$(BIN) $(INPUT) $(OUTPUT) --color
else
	@echo "Running in GRAYSCALE mode..."
	./$(BIN) $(INPUT) $(OUTPUT)
endif

clean:
	@echo "Cleaning build files and results..."
	rm -rf $(OBJ_DIR) $(BIN)
	rm -f $(RESULT_DIR)/*.png
	@echo "Clean complete."

.PHONY: all run clean
