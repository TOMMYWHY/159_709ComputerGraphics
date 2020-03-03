HEADERS = -I/opt/local/include/
LIBS = -L/opt/local/lib/ -lglfw -framework OpenGL
CC = g++ -O3

example02: example02.o
	${CC} example02.o -o example02 ${LIBS}

example02.o: example02.cpp
	${CC} -c example02.cpp -o example02.o ${HEADERS}

clean:
	rm *.o
	rm example02