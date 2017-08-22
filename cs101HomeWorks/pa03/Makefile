graph03: graph03.o intVec.o loadGraph.o scc03.o
	gcc -o graph03 -std=c99 -D_SVID_SOURCE graph03.o intVec.o scc03.o loadGraph.o

graph03.o: graph03.c intVec.h loadGraph.h scc03.h
	gcc -c -std=c99 -D_SVID_SOURCE graph03.c

intVec.o: intVec.c intVec.h
	gcc -c -std=c99 -D_SVID_SOURCE intVec.c

loadGraph.o: loadGraph.c loadGraph.h intVec.h
	gcc -c -std=c99 -D_SVID_SOURCE loadGraph.c

scc03.o: scc03.c intVec.h loadGraph.h
	gcc -c -std=c99 -D_SVID_SOURCE scc03.c

clean:
	rm -f graph03 graph03.o intVec.o loadGraph.o scc03.o
