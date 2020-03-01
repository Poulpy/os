CC=gcc
CFLAGS=-O2 -pedantic -ansi -g -Wall
SRCDIR=src
BUILDDIR=build
TARGET=bin/main
INC=-Iinclude
OBJ=build/main.o build/floats.o build/matrix.o build/file_io.o

all: $(TARGET)

test: $(TARGET)

$(TARGET): $(OBJ)
	mkdir build
	mkdir bin
	$(CC) $(CFLAGS) $^ -o $(TARGET)

build/main.o: src/main.c $(BUILDDIR)/file_io.o $(BUILDDIR)/floats.o $(BUILDDIR)/matrix.o
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/floats.o: $(SRCDIR)/floats.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/matrix.o: $(SRCDIR)/matrix.c $(BUILDDIR)/floats.o
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/file_io.o: $(SRCDIR)/file_io.c $(BUILDDIR)/floats.o $(BUILDDIR)/matrix.o
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)/*.o
	rm -rf $(TARGET)
