CC=mpicc
CCFLAGS= -Ofast -Wall

EXE=mpi_postmansort

all: $(EXE)



$(EXE): mpi_postmansort.c
	$(CC) $(CCFLAGS) -o $@ $^

clean:
	-/bin/rm -f $(EXE)