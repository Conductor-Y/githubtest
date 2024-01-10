CFLAGS=-Wall -g

target:=ex17

all:$(target)

val_c:
	valgrind --leak-check=full ./$(target) db.dat c 100 100 Condutor 			

val_s:
	valgrind --leak-check=full ./$(target) db.dat s 1 Yjh Yjh@.com male

val_l:
	valgrind --leak-check=full ./$(target) db.dat l

val_g:
	valgrind --leak-check=full ./$(target) db.dat g 1

val_f:
	valgrind --leak-check=full ./$(target) db.dat f Yjh

val_d:
	valgrind --leak-check=full ./$(target) db.dat d 1

clean:
	rm -rf $(target)





















