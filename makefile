test: bin/test
	
bin/test: precomp/test.o precomp/config.o precomp/led.o precomp/errors.o
	g++ precomp/test.o precomp/config.o precomp/led.o precomp/errors.o -o bin/test

precomp/test.o: test.cpp src/config.h src/led.h
	g++ -c test.cpp -o precomp/test.o
precomp/config.o: src/config.cpp src/config.h src/errors.h
	g++ -c src/config.cpp -o precomp/config.o
precomp/led.o: src/led.cpp src/led.h src/config.h src/errors.h
	g++ -c src/led.cpp -o precomp/led.o
precomp/errors.o: src/errors.cpp src/errors.h
	g++ -c src/errors.cpp -o precomp/errors.o

# debug versions
debug: bin/debug
	
bin/debug: precomp/test-dbg.o precomp/config-dbg.o precomp/led-dbg.o precomp/errors-dbg.o
	g++ -g precomp/test-dbg.o precomp/config-dbg.o precomp/led-dbg.o precomp/errors-dbg.o -o bin/debug

precomp/test-dbg.o: test.cpp src/config.h src/led.h
	g++ -g -c test.cpp -o precomp/test-dbg.o -o precomp/test-dbg.o
precomp/config-dbg.o: src/config.cpp src/config.h src/errors.h
	g++ -g -c src/config.cpp -o precomp/config-dbg.o -o precomp/config-dbg.o
precomp/led-dbg.o: src/led.cpp src/led.h src/config.h src/errors.h
	g++ -g -c src/led.cpp -o precomp/led-dbg.o -o precomp/led-dbg.o
precomp/errors-dbg.o: src/errors.cpp src/errors.h
	g++ -g -c src/errors.cpp -o precomp/errors-dbg.o -o precomp/errors-dbg.o


clean:
	rm precomp/*.o
