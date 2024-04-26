CC=mpicc
CCFLAGS= -Ofast -Wall

EXE=mpi_binarySearch

all: $(EXE)



$(EXE): mpi_binarySearch.c
	$(CC) $(CCFLAGS) -o $@ $^

clean:
	-/bin/rm -f $(EXE)
