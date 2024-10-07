# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Output
TARGET = server

# Source files
SRCS = ./src/TCP_Server/TCPEchoServer.cpp \
       ./src/Bloom_Filter/BloomFilter.cpp \
       ./src/Bloom_Filter/HashFunc.cpp \
       ./src/Bloom_Filter/HelpFunctions.cpp \
       ./src/Bloom_Filter/NumHashFunc.cpp \
       ./src/Bloom_Filter/VectorBlacklist.cpp \
       ./src/Bloom_Filter/SetupParser.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Compile source files into object files
# Pattern rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS)

.PHONY: all clean
