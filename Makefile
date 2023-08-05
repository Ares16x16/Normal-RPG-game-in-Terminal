RPG_function.o: RPG_function.cpp RPG_struct.h
	g++ -c RPG_function.cpp

RPG_main.o: RPG_main.cpp RPG_struct.h
	g++ -c RPG_main.cpp

RPG: RPG_function.o RPG_main.o
	g++ RPG_function.o RPG_main.o -o RPG

clean:
	rm -f RPG_function.o RPG_main.o
	
.PHONY: clean
