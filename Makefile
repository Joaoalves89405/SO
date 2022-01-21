all: obj1 obj2 obj3 obj4
obj1: EX1/prog1.o
	gcc -g EX1/prog1.o
prog1.o: EX1/prog1.c
	gcc -Wall EX1/prog1.c
obj2: EX2/prog2.o
	gcc -g EX2/prog2.o
prog2.o: EX2/prog2.c
	gcc -Wall EX2/prog2.c
obj3: EX3/prog3c.o  EX3/prog3s.o EX3/prog3stop.o
	gcc -g EX3/prog3c.o 
	gcc -g EX3/prog3s.o
	gcc -g EX3/prog3stop.o
prog3c.o: EX3/prog3c.c
	gcc -Wall EX3/prog3c.c
prog3s.o: EX3/prog3s.c
	gcc -Wall EX3/prog3s.c
prog3stop.o: EX3/prog3stop.c
	gcc -Wall EX3/prog3stop.c
obj4: EX4/prog4c.o  EX4/prog4s.o EX4/prog4stop.o
	gcc -g EX4/prog4c.o 
	gcc -g EX4/prog4s.o
	gcc -g EX4/prog4stop.o
prog4c.o: EX4/prog4c.c
	gcc -Wall EX4/prog4c.c
prog4s.o: EX4/prog4s.c
	gcc -Wall EX4/prog4s.c
prog4stop: EX4/prog4stop.c
	gcc -Wall EX4/prog4stop.c
	
clean:
	rm -f *.o prog1
	rm -f prog2
	rm -f prog3s prog3c prog3stop
	rm -f prog4s prog4c prog4stop
	
