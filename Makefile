test: testMain.c btree.c helperFunctions.c test.c
	gcc testMain.c btree.c helperFunctions.c test.c -o test -lm -I . 
