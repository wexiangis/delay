target:
	gcc -Wall -o out1 t1.c delay.c
	gcc -Wall -o out2 t2.c delay.c
	gcc -Wall -o out3 t3.c delay.c -lm -lpthread
	gcc -Wall -o out4 t4.c delay.c -lm -lpthread
clean:
	rm ./out*