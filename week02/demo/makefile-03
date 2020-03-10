HEADERS = -I/opt/local/include/
LIBS = -L/opt/local/lib/ -lglfw -framework OpenGL
CC = g++ -O3

example03: example03.o
	${CC} example03.o -o example03 ${LIBS}

example03.o: example03.cpp
	${CC} -c example03.cpp -o example03.o ${HEADERS}

clean:
	rm *.o
	rm example03