#ifndef _MEMORY_H_
#define _MEMORY_H_

#define k 64			//key size
#define size 256		//state size
#define no_of_time 100	//How many number of colliding key pairs you need.

typedef unsigned char UC;

UC iSwap(UC *, UC * );
UC MaxcolStep( UC * );
UC KSA( UC *, int );
void print_key( UC * );
UC Round(UC );
UC TranSearch( UC *);
void key_generation();
void Number_of_round();
void avg_time();

#endif
