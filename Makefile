################################################################################



################################################################################

LIBS := -lglut -lGL -lGLU -lGLEW
SRC_DIR := source
SRC_TUTORIAL_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

CXXFLAGS := -g -O0

CCFILES := $(shell ls -1 ./$(SRC_DIR)/*.cpp 2>/dev/null)

################################################################################
# Set up object files
################################################################################
OBJS +=  $(patsubst %.cpp,$(OBJ_DIR)/%.cpp.o,$(notdir $(CCFILES)))
BINS +=  $(patsubst %.cpp,$(BIN_DIR)/%,$(notdir $(CCFILES)))

all: make_dirs $(BINS) $(BIN_DIR)/example_1 $(BIN_DIR)/example_2

make_dirs:
	mkdir -p ./bin
	mkdir -p ./obj


$(BIN_DIR)/example_1: $(SRC_TUTORIAL_DIR)/example_1.cpp
	$(CXX) $< $(LIBS) $(CXXFLAGS) -o $@

$(BIN_DIR)/example_2: $(SRC_TUTORIAL_DIR)/example_2.cpp
	$(CXX) $< $(LIBS) $(CXXFLAGS) -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(CXX) $< -c -o $@
	
$(BIN_DIR)/%: $(OBJ_DIR)/%.cpp.o
	$(CXX) $< $(LIBS) -o $@


clean:
	rm -f ./bin/*
	rm -f ./obj/*

	