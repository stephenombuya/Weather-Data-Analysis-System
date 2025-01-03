# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS = -lm

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
DATA_DIR = data

# Files
EXEC = weather_analyzer
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
.PHONY: all
all: dirs $(BIN_DIR)/$(EXEC)

# Create necessary directories
.PHONY: dirs
dirs:
	@mkdir -p $(SRC_DIR) $(OBJ_DIR) $(BIN_DIR) $(TEST_DIR) $(DATA_DIR)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link the program
$(BIN_DIR)/$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Debug build
.PHONY: debug
debug: CFLAGS += -g -DDEBUG
debug: clean all

# Run the program with sample data
.PHONY: run
run: all
	./$(BIN_DIR)/$(EXEC) $(DATA_DIR)/sample_weather_data.csv

# Run tests
.PHONY: test
test: $(TEST_OBJ)
	$(CC) $^ $(OBJ) -o $(BIN_DIR)/run_tests $(LDFLAGS)
	./$(BIN_DIR)/run_tests

# Generate sample data
.PHONY: sample-data
sample-data:
	@echo "Date,Temperature,Humidity,Pressure,WindSpeed,Rainfall" > $(DATA_DIR)/sample_weather_data.csv
	@echo "2024-01-01,20.5,65.0,1013.2,12.5,0.0" >> $(DATA_DIR)/sample_weather_data.csv
	@echo "2024-01-02,22.0,70.0,1012.8,10.2,5.2" >> $(DATA_DIR)/sample_weather_data.csv

# Clean build files
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Clean all generated files
.PHONY: clean-all
clean-all: clean
	rm -f weather_report.txt processed_weather_data.csv
	rm -rf $(DATA_DIR)/*

# Format source code
.PHONY: format
format:
	clang-format -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h

# Check for memory leaks
.PHONY: memcheck
memcheck: debug
	valgrind --leak-check=full ./$(BIN_DIR)/$(EXEC) $(DATA_DIR)/sample_weather_data.csv

# Install the program
.PHONY: install
install: all
	install -d $(DESTDIR)/usr/local/bin/
	install $(BIN_DIR)/$(EXEC) $(DESTDIR)/usr/local/bin/

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all          - Build the program (default)"
	@echo "  debug        - Build with debug symbols"
	@echo "  run          - Run the program with sample data"
	@echo "  test         - Run unit tests"
	@echo "  sample-data  - Generate sample weather data"
	@echo "  clean        - Remove build files"
	@echo "  clean-all    - Remove all generated files"
	@echo "  format       - Format source code"
	@echo "  memcheck     - Check for memory leaks"
	@echo "  install      - Install the program"
	@echo "  help         - Show this help message"
