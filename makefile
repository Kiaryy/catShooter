# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# Target
TARGET = ballShooter
# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
# Source files
SRCS = main.cpp 
# Objet Files, uses patsbust which replaces text
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(TARGET)

# Debug, adds debug flags and builds target
debug: CXXFLAGS += -ggdb
debug: all

# Release, adds optimization flags and builds
release: CXXFLAGS += -O3 -DNDEBUG
release: all

# Windows, adds window build flag
windows: CXX = x86_64-w64-mingw32-g++
windows: CXXFLAGS = -O3 -static
windows: all


# Rule to build the target
$(TARGET): $(OBJS)
	@echo "Compiling $@"
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(BUILD_DIR)/$@ $(CXXFLAGS)

# Rule to build object files
$(OBJ_DIR)/%.o: %.cpp
	@echo "Making $@"
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	@echo "Cleaning object files"
	rm -r $(BUILD_DIR)/*