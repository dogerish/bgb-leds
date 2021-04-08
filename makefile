bin/test: precomp/test.o precomp/led.o precomp/config.o precomp/files.o precomp/errors.o
	g++ precomp/test.o precomp/led.o precomp/config.o precomp/files.o precomp/errors.o -o bin/test

precomp/test.o: test.cpp src/config.h src/led.h precomp/config.o precomp/led.o
	g++ -c test.cpp -o precomp/test.o
precomp/led.o: src/led.cpp src/led.h src/config.h src/files.h precomp/config.o precomp/files.o
	g++ -c src/led.cpp -o precomp/led.o
precomp/config.o: src/config.cpp src/config.h
	g++ -c src/config.cpp -o precomp/config.o
precomp/files.o: src/files.cpp src/files.h
	g++ -c src/files.cpp -o precomp/files.o
precomp/errors.o: src/errors.cpp src/errors.h
	g++ -c src/errors.cpp -o precomp/errors.o

# debug versions
debug: bin/debug

bin/debug: precomp-dbg/test.o precomp-dbg/led.o precomp-dbg/config.o precomp-dbg/files.o precomp-dbg/errors.o
	g++ -g precomp-dbg/test.o precomp-dbg/led.o precomp-dbg/config.o precomp-dbg/files.o precomp-dbg/errors.o -o bin/debug

precomp-dbg/test.o: test.cpp src/config.h src/led.h precomp-dbg/config.o precomp-dbg/led.o
	g++ -g -c test.cpp -o precomp-dbg/test.o
precomp-dbg/led.o: src/led.cpp src/led.h src/config.h src/files.h precomp-dbg/config.o precomp-dbg/files.o
	g++ -g -c src/led.cpp -o precomp-dbg/led.o
precomp-dbg/config.o: src/config.cpp src/config.h
	g++ -g -c src/config.cpp -o precomp-dbg/config.o
precomp-dbg/files.o: src/files.cpp src/files.h
	g++ -g -c src/files.cpp -o precomp-dbg/files.o
precomp-dbg/errors.o: src/errors.cpp src/errors.h
	g++ -g -c src/errors.cpp -o precomp-dbg/errors.o


clean:
	rm precomp/*.o precomp-dbg/*.o
