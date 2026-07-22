SRC_RAYLIB = libraylib.a 

build: 
	@g++ -std=c++2b -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL ${SRC_RAYLIB} stochastic.cpp -o stochastic

run: 
	python3 fetch.py

clean:
	rm -r -f ./stochastic