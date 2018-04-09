################################################################################



################################################################################

LIBS := -lglut -lGL -lGLU
SRC_DIR := source
BIN_DIR := bin
OBJ_DIR := obj

CCFILES := $(shell ls -1 ./$(SRC_DIR)/*.cpp 2>/dev/null)

################################################################################
# Set up object files
################################################################################
OBJS +=  $(patsubst %.cpp,$(OBJ_DIR)/%.cpp.o,$(notdir $(CCFILES)))
BINS +=  $(patsubst %.cpp,$(BIN_DIR)/%,$(notdir $(CCFILES)))

all: make_dirs $(BINS)
#all: a-initialization b-reshape c-animation d-keyboard e-thecodesofar \
	f-thecodesofarII g-thecodesofarIII h-thecodesofarIV i-thecodesofarV \
	j-thecodesofarVI k-subwindowscode l-thecodesofarVII

make_dirs:
	mkdir -p ./bin
	mkdir -p ./obj


$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(CXX) $< -c -o $@
	
$(BIN_DIR)/%: $(OBJ_DIR)/%.cpp.o
	$(CXX) $< $(LIBS) -o $@


clean:
	rm -f ./bin/*
	rm -f ./obj/*

	