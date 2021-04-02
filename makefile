test: test.o config.o led.o
	g++ test.o config.o led.o -o test

test.o: test.cpp config.h led.h
	g++ -c test.cpp
config.o: config.cpp config.h
	g++ -c config.cpp
led.o: led.cpp led.h config.h
	g++ -c led.cpp

clean:
	rm *.o
