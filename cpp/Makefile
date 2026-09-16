# model graciously provided by geeksforgeeks @ https://www.geeksforgeeks.org/cpp/makefile-in-c-and-its-applications/
# yet I found it quite complex, so I'm explicitly writing the rules...
#I'LL FUCKING DO IT BY HAND THAT'S IT!


# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Target executable
TARGET = app

# For deleting the target
TARGET_DEL = app

all: app clear

app: ./obj/App.o ./
	$(CXX) $(CXXFLAGS) -o app ./objs/*




#FUCKING BLACKMAGIC! which doesn't quite work...
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

