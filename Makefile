# Compiler
CC = gcc

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source files
GLADIATOR_SRC = $(SRC_DIR)/gladiator.c
TOURNAMENT_SRC = $(SRC_DIR)/tournament.c

# Executables
GLADIATOR_BIN = $(BIN_DIR)/gladiator
TOURNAMENT_BIN = $(BIN_DIR)/tournament

# Phony targets
.PHONY: all run clean

# -----------------------------------------------------------------
# Default target: compile all binaries
# -----------------------------------------------------------------
all: $(BIN_DIR) $(GLADIATOR_BIN) $(TOURNAMENT_BIN)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile gladiator
$(GLADIATOR_BIN): $(GLADIATOR_SRC)
	$(CC) $(GLADIATOR_SRC) -o $(GLADIATOR_BIN)

# Compile tournament
$(TOURNAMENT_BIN): $(TOURNAMENT_SRC)
	$(CC) $(TOURNAMENT_SRC) -o $(TOURNAMENT_BIN)

# -----------------------------------------------------------------
# Run the tournament
# -----------------------------------------------------------------
run: all
	./$(TOURNAMENT_BIN)

# -----------------------------------------------------------------
# Clean bin and logs directories
# -----------------------------------------------------------------
clean:
	rm -rf $(BIN_DIR)
	rm -rf logs
