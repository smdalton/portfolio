
graph02: graph02.o intVec.o loadGraph.o
	gcc -o graph02 -std=c99 -D_SVID_SOURCE graph02.o intVec.o loadGraph.o

graph02.o: graph02.c intVec.h loadGraph.h
	gcc -c -std=c99 -D_SVID_SOURCE graph02.c
    
intVec.o: intVec.c intVec.h
	gcc -c intVec.c

loadGraph.o: loadGraph.c loadGraph.h intVec.h
	gcc -c loadGraph.c

clean:
	rm -f graph02 graph02.o intVec.o loadGraph.o
