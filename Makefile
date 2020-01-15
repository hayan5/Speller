
# CXX = g++
# CXXFLAGS = -std=c++11 -Wall -g
# BUILD    := ./build
# OBJ_DIR  := $(BUILD)/objects
# APP_DIR  := $(BUILD)/apps
# TARGET   := speller
# INCLUDE  := -Iinclude/

# SRC := 
# 	$(wildcard src/trie/*.cpp) 
# 	$(wildcard src/*.cpp) 


# OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# all: build $(APP_DIR)/$(TARGET)

# $(OBJ_DIR)/%.o: %.cpp
# 	@mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# $(APP_DIR)/$(TARGET): $(OBJECTS)
# 	@mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

# $(TEST_DIR)/$(TEST_TARGET): $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(TEST_DIR)/$(TARGET) $(OBJECTS)

# .PHONY: all build clean debug release test

# build:
# 	@mkdir -p $(APP_DIR)
# 	@mkdir -p $(OBJ_DIR)

# debug: CXXFLAGS += -DDEBUG -g
# debug: all

# release: CXXFLAGS += -O2
# release: all

# clean:
# 	-rm -rvf $(OBJ_DIR)/*
# 	-rm -rvf $(APP_DIR)/*

# run:
# 	$(APP_DIR)/$(TARGET)

# CXX := g++
# LD := g++

# EXEC := speller
# FLAGS := -Wall
# CXXFLAGS := -std=c++11 -Wall -g
# LDFLAGS := $(FLAGS)
# INC := -I inc
# SRC := $(wildcard src/*.cpp)
# OBJ := $(SRC:src/%.cpp=tmp/%.o)

# EXEC_TEST := test
# FLAGS_TEST := $(FLAGS)
# CXXFLAGS_TEST := (CXXFLAGS)
# LDFLAGS_TEST := $(LDFLAGS)
# INC_TEST := $(INC) -I lib/catch/inc
# SRC_TEST := $(wildcard tst/*cpp)
# OBJ_TEST := $(filter-out tmp/main.o, $(OBJ)) $(SRC_TEST:tst/%.cpp=tmp/%.o)

# .SUFFIXES:

# #----

# .PHONY: all
# all: out/$(EXEC)

# out/$(EXEC): $(OBJ)
# 	$(LD) $(LDFLAGS) $^ -o $@ && echo "[OK] $@"

# #----

# .PHONY: test
# test: out/$(EXEC_TEST)
	

# out/$(EXEC_TEST): $(OBJ_TEST)
# 	@$(LD) $(LDFLAGS_TEST) $^ -o $@ && echo "[OK] $@"
# #----

# tmp/%.o: src/%.cpp
# 	$(CXX) $(CXXFLAGS) -c $< $(INC) -o $@ && echo "[OK] $@"

# tmp/%.o: tst/%.cpp
# 	$(CXX) $(CXXFLAGS) -c $< $(INC_TEST) -o $@ && echo "[OK] $@"

# #----

# .PHONY: clean clear
# clean clear: 
# 	rm -f out/*
# 	rm -f tmp/*

# .PHONY: archive zip
# archive zip:
# 	zip -x out/* tmp/* lib/* -q -r out/$(EXEC)-$(shell date '+%F').zip . && echo "[OK]  out/$(EXEC)-$(shell date '+%F').zip" 

CXX := g++
LD := g++

EXEC := speller
CXXFLAGS := -std=c++11 -Wall -g
LDFLAGS := -Wall
INCLUDE := -I include

BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
SRC := $(wildcard src/*.cpp)
OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

EXEC_TEST := test
FLAGS_TEST := -Wall
CXXFLAGS_TEST := $(CXXFLAGS)
LDFLAGS_TEST := $(LDFLAGS)
INCLUDE_TEST := $(INCLUDE) -I lib/catch/include
SRC_TEST := $(wildcard test/*cpp)
OBJ_TEST := $(filter-out $(OBJ_DIR)/src/main.o, $(OBJECTS)) $(SRC_TEST:%.cpp=$(OBJ_DIR)/%.o)

.SUFFIXES:

#-----

.PHONY: all
all: $(APP_DIR)/$(EXEC)

$(APP_DIR)/$(EXEC): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

#-----

.PHONY: test
test: $(APP_DIR)/$(EXEC_TEST)

$(APP_DIR)/$(EXEC_TEST): $(OBJ_TEST)
	$(LD) $(LDFLAGS_TEST) $^ -o $@

#-----

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDE) -o $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS_TEST) -c $< $(INCLUDE_TEST) -o $@

#-----

.PHONY: clean
clean:
	-rm -rvf $(OBJ_DIR)/*
	-rm -rvf $(APP_DIR)/*

.PHONY: t
t:
	@$(APP_DIR)/$(EXEC_TEST)

.PHONY: r
run:
	@$(APP_DIR)/$(EXEC)

