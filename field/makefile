
all: field.o test.o
	@$(CC)  field.o test.o -o a 
	@rm *.o	
	@./a
field.o: field.c field.h
	@$(CC)  field.c -c 

test.o: test_field.c field.h
	@$(CC)  test_field.c -c -o test.o


