### TODO

- Makefile
- Documentation
- Uni testing

### Compile and execute tests

```
gcc -Wall -pedantic -ansi -O2 -g src/floats.c test/test_floats.c
gcc -Wall -pedantic -ansi -O2 -g src/floats.c src/file_io.c src/matrix.c test/test_matrix.c
gcc -Wall -pedantic -ansi -O2 -g src/file_io.c test/test_file_io.c
./a.out
```

### Compile and execute main

```
gcc -Wall -pedantic -ansi -O2 -g src/floats.c src/file_io.c src/matrix.c src/main.c
./a.out test/mat.txt test/mat2.txt
```

