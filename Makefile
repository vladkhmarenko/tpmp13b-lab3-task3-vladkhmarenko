bin/program: obj/main.o 
	gcc -o bin/program obj/main.o

obj/main.o: src/main.c 
	gcc -o obj/main.o -c src/main.c

clean:
	rm -rf obj/*.o bin/program
