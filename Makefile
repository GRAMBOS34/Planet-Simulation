# Define flags
CFLAGS = -Wall -lGL -lSDL2 -lGLEW

CC = g++
EXEC = bin/program.exe

# Source and object file directories
SRCDIR = src
OBJDIR = obj
BIN_DIR = bin
RES_DIR = res

# List of source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# List of object files with and adjustment to the path
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# $@ expands to whatever the target is
# $^ expands to whatever the dependencies are
# @mkdir just tells it to not show to the terminal
# This compiles from source to objects
$(EXEC): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $^ $(CFLAGS) -o $@

# Compiles source files into ojbect files
# $< expands to only the first target
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BIN_DIR)/*.exe
