CC = g++
CFLAGS = -I/usr/include/SFML -I/usr/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = sfml-project

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)