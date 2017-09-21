SRC_PATH= 
CC=g++
CFLAGS=-c -Wall
LDFLAGS=-Lglfw3\lib -Lglew\lib -lglfw3 -lglew32 -lopengl32 -mwindows -mconsole
INCL=-Iglfw3\include -Iglew\include
EXE=main

SRC=$(wildcard $(SRC_PATH)*.cpp $(SRC_PATH)/*.cpp $(SRC_PATH)/*.cpp)
OBJ=$(subst ../src, ../obj, $(SRC:.cpp=.o))

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

../obj/%.o: ../src/%.cpp
	$(CC) $(CFLAGS) $(INCL) -o $@ $<

clean:
	rm -rf run $(OBJ)