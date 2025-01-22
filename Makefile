CC = gcc
CFLAGS = -Wall -g
LDFLAGS = `sdl2-config --libs`
INCLUDES = `sdl2-config --cflags`

SRC = Game.c
OBJ = $(SRC:.c=.o)
EXEC = Game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
