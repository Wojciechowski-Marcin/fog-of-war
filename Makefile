.PHONY: compile

EXE = FogOfWar
SRCPATH = src/*.cpp
CFLAGS = -Iinclude/ -std=c++17
LDFLAGS = -lGL -lGLU -lglut

compile: $(SRCPATH)
	g++ $(SRCPATH) -o $(EXE) $(CFLAGS) $(LDFLAGS) -g
