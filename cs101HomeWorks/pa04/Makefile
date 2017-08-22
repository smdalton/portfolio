greedy04: greedy04.o adjWgtVec.o loadWgtGraph.o minPQ.o
	gcc -o greedy04 -std=c99 -D_SVID_SOURCE greedy04.o adjWgtVec.o minPQ.o loadWgtGraph.o

greedy04.o: greedy04.c adjWgtVec.h loadWgtGraph.h minPQ.h
	gcc -c -std=c99 -D_SVID_SOURCE greedy04.c

adjWgtVec.o: adjWgtVec.c adjWgtVec.h
	gcc -c -std=c99 -D_SVID_SOURCE adjWgtVec.c

loadWgtGraph.o: loadWgtGraph.c loadWgtGraph.h adjWgtVec.h
	gcc -c -std=c99 -D_SVID_SOURCE loadWgtGraph.c

minPQ.o: minPQ.c minPQ.h
	gcc -c -std=c99 -D_SVID_SOURCE minPQ.c

clean:
	rm -f greedy04 greedy04.o adjWgtVec.o loadWgtGraph.o minPQ.o