all:sqrt series 
sqrt:sqrt.o
sqrt.o:sqrt.c
	gcc -c sqrt.c
series:series.o
series.o: series.c
	gcc -c series.c
clean:
	rm series.o series
	rm sqrt.o sqrt
