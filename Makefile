CC = gcc
SOURCE = ./src/artwork.c ./src/image.c
OUTPUT = main
LINKERS_FLAGS = -lm

windows:
	$(CC) $(SOURCE) $(LINKERS_FLAGS) -o main