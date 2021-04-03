test: test.o config.o led.o errors.o
	g++ test.o config.o led.o errors.o -o test

test.o: test.cpp config.h led.h
	g++ -c test.cpp
config.o: config.cpp config.h errors.h
	g++ -c config.cpp
led.o: led.cpp led.h config.h errors.h
	g++ -c led.cpp
errors.o: errors.cpp errors.h
	g++ -c errors.cpp

# debug versions
debug: test-dbg.o config-dbg.o led-dbg.o errors-dbg.o
	g++ -g test-dbg.o config-dbg.o led-dbg.o errors-dbg.o -o debug

test-dbg.o: test.cpp config.h led.h
	g++ -g -c test.cpp -o test-dbg.o
config-dbg.o: config.cpp config.h errors.h
	g++ -g -c config.cpp -o config-dbg.o
led-dbg.o: led.cpp led.h config.h errors.h
	g++ -g -c led.cpp -o led-dbg.o
errors-dbg.o: errors.cpp errors.h
	g++ -g -c errors.cpp -o errors-dbg.o


clean:
	rm *.o
