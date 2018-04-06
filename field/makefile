
all: field.o test.o lodepng.o
	@$(CC)  field.o test.o lodepng.o -o a 
	@rm *.o	
	@./a
field.o: field.c field.h
	@$(CC)  field.c -c 

test.o: test_field.c field.h
	@$(CC)  test_field.c -c -o test.o

lodepng.o: ../lodepng/lodepng.c ../lodepng/lodepng.h
	@$(CC) ../lodepng/lodepng.c -c 

valgrind: a
	 valgrind  ./a 
