# This project depends on SFML, download it and make this point to the correct directory
# https://www.sfml-dev.org/download/sfml/2.5.1/
SFMLPATH := ../../dependencies/SFML-2.5.1

BUILD_DIR := ./bld
SRC_DIRS := ./src
TARGET_EXEC := exe
CPPFLAGS += -I "$(SFMLPATH)/include/"
LDFLAGS += -L "$(SFMLPATH)/lib" -lsfml-graphics -lsfml-window -lsfml-system


# Just copy this makefile:
# https://makefiletutorial.com/#getting-started

# Find all the C++ files we want to compile
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run
clean:
	rm -r $(BUILD_DIR)

# in order to run it, SFML path is exported only for the command that comes after it
# then run the target executable ./bld/exe
run:
	export LD_LIBRARY_PATH=$(SFMLPATH)/lib && $(BUILD_DIR)/$(TARGET_EXEC)
