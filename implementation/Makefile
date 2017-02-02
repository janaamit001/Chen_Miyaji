all: Chen_Miyaji_algo

Chen_Miyaji_algo:	Chen_Miyaji_algo_main.o Chen_Miyaji_algo_fun.o
	gcc Chen_Miyaji_algo_main.c Chen_Miyaji_algo_fun.c -o Chen_Miyaji_algo

Chen_Miyaji_algo_main.o:	Chen_Miyaji_algo_main.c
	gcc -c Chen_Miyaji_algo_main.c

Chen_Miyaji_algo_fun.o:	Chen_Miyaji_algo_fun.c
	gcc -c Chen_Miyaji_algo_fun.c

clean:	
	rm -rf *o Chen_Miyaji_algo 
