CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC_DIR = src
OBJ_DIR = obj
BIN = test.exe

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-del /Q $(BIN) 2>nul
	-rmdir /S /Q $(OBJ_DIR) 2>nul

run: $(BIN)
	./$(BIN)

rebuild: clean all