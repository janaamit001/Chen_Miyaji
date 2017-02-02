#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include "Chen_Miyaji_algo_fun.h"

UC N, d, R, keySum;
UC Statevector1[size], J[size], S[size];


UC iSwap(UC *a, UC *b)
{
	UC temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


UC MaxcolStep( UC *Key5 )
{
	UC  l, j1 = 0, m = 0, p, t, flag = 0, flag1 = 0;
	short i;
	
	for( i = 0 ; i < size ; i++ )
		Statevector1[i] = i;

	p = d+(N-1)*k;
	
	for( i = 0 ; i < size ; i++ )
	{
		j1 = ( j1 + Statevector1[i] + Key5[i%k] ) % size ;
		S[i] = Statevector1[i];
		J[i] = j1;
		l++;
		t = d+m*k;
		if( i == t && i < p )
		{
			if( flag == 0 )
			{
				if( (j1 != d) )
					return i; 
				flag = 1;
			}
			else if( i < p-k )
			{
				if( ( j1 != t+k) )
					return i; 
			}
			else
			{
				if( j1 != t+k - 1 )
					return i; 
			}
		}
		else if( i < p-2 )
		{
			if( i < d )
			{
				if( ( j1 == d || j1 == d+1) )
					return i; 
			}
			else if( i == d+1 )
			{
				if( j1 != d+k )
					return i; 
			}
			else if( i < d+k )
			{
				if( j1 == d+k || j1 == d)
					return i; 
			}
			else if( i < p-k )
			{
				if( j1 == t+k || j1 == d )
					return i; 
			}
			else
			{
				if( j1 == t+k-1 || j1 == d)
					return i; 
			}
		}
		
		else
		{
			if( i == ( p-2 ) )
			{
				if( j1 != d )
					return i; 
			}
			
			else if( i == ( p-1 ) )
			{
				if( j1 != ( p-1 ) )
					return i; 
			}
		}
		if( i > d+k-2 )
		{
			if( flag1 == 0 )
			{
				m = 1;
				l = -1;
			}
			flag1 = 1;
			if( l == k-1 )
			{
				m++;
				l = -1;
			}
		}
		iSwap( &Statevector1[i] , &Statevector1[j1] );
	}
	return 255;
}

UC KSA( UC Key1[], int r )
{
	short i, j;
	
	j = 0;

	for(i = 0 ; i < size ; i++)
		Statevector1[i] = i;
		
	for(i = 0 ; i <= r ; i++)
	{
		j = (j + Key1[i%k] + Statevector1[i]) % size;
		iSwap(&Statevector1[i], &Statevector1[j]);
	}
	
	return j;
}

UC Round( UC a )
{
	return ((a+k-d-1)/k);
}

void print_key( UC Key1[] )
{
	short i;
	
	printf("Key1 is::\n");
	for(i = 0; i < k; ++i)
		printf("%d, ", Key1[i]);
	printf("\n");	
}

UC TranSearch( UC Key1[] )
{
	UC p, q, r, delr, t, MaxR, MaxR1, MaxR2, stateSum = 0;
	short i, j;
	
	q = MaxcolStep( Key1 );
	MaxR = Round(q);
	if(MaxR == N+1)
		return N;
	
	if(MaxR < N-1)
	{
		r = MaxR*k+d;
		stateSum = 0;
	
		for(i = r-k+1; i <= r; ++i)
			stateSum = (stateSum+S[i])%size;
			
		while( r > ((MaxR-1)*k+d))
		{
			delr = (3*size+k-stateSum+S[r]-keySum)%size;
			if(delr < ((MaxR-1)*k+d))
			{
				p = (size + r - J[delr])%size;
				Key1[delr%k] = (size+Key1[delr%k]+p)%size;
				Key1[delr%k+1] = (size+Key1[delr%k+1]-p)%size;
				q = MaxcolStep( Key1 );
				MaxR1 = Round(q);
				if(MaxR1 > MaxR)
					break;
				else
				{
					Key1[delr%k] = (size+Key1[delr%k]-p)%size;
					Key1[delr%k+1] = (size+Key1[delr%k+1]+p)%size;
				}
			}
			--r;
		}
		if((MaxR1 <= MaxR) || (R == N))
			return MaxR1;
		else
		{
			++R; 
			return (TranSearch( Key1 ));
		}
	}
	else
	{
		MaxR2 = MaxR;
		for(i = 0; i <= d-3; ++i)
		{    
			for(j = 1; j <= size; ++j)
			{
				Key1[i] = (Key1[i]+1)%size;
				Key1[(i+1)] = (size+Key1[(i+1)]-1)%size;
				q = MaxcolStep( Key1 );
				MaxR1 = Round(q);
				if(MaxR1 > MaxR2)
				{
					MaxR2 =  MaxR1;
					break;
				}
				/*if(t == 255)
					return N;*/
			}
		}
		if((MaxR1 <= MaxR) || (R == N))
			return MaxR1;
		else
		{
			++R; 
			return (TranSearch( Key1 ));
		}
	}
}




void key_generation()
{ 
	short i, count = 0;
	UC Key1[ k ], q, s, stateSum = 0;
	srand(time(NULL));
	while(1)
	{
		
		for( i = 0 ; i < k ; i++ )
			Key1[ i ] = rand()%256;

		while(1)
		{
			q = MaxcolStep( Key1 );
			if(q <= d-1)
			{
				for(i = 0; i < size; ++i)
				{
					Key1[q] = Key1[q]+1;
					Key1[(q+1)] = Key1[(q+1)]-1;
					s = MaxcolStep( Key1 );
					if(s > q)
						break;
				}
			}
			else
				break;
		}
		
		Key1[ d-1 ] = ((N-1)*k - d - 2);
		Key1[ d+1 ] = k - d - 1;
		
		q = KSA( Key1, d-1 );
		
		Key1[ d ] = 256 - q;
		
		q = KSA( Key1, d+1 );
		
		keySum = 0;
		for(i = 0; i <= d; ++i)
			keySum = (keySum + Key1[i]) % size;
			
		stateSum = 0;
		for(i = d+2; i <= d+k; ++i)
			stateSum = (stateSum + Statevector1[i]) % size;
			
		Key1[d+2] = (k - keySum - stateSum + (2*256))%256;
		
		q = MaxcolStep( Key1 );
		if(q > d+k)
		{
			R = 0;
			q = TranSearch( Key1 );
			if(q == N)
			{
				//printf("colliding key pair is found\n");
				//print_key( Key1 );
				//printf("Count = %d\n", count);
				count++;
				if(count == 1)
					break;
			}
		}
		//printf("generate new key pair: \n\n");
	}
	return;		
}

void Number_of_round()
{
	d = k-3;
	if( ( size % k ) == 0 )
		N = size/k;
	else
		N = ( size + k - d -1 )/k;
		
	printf("chen-->N = %d k = %d\n", N, k);
}

void avg_time()
{
	short i;
	double time = 0;
	
	for(i = 0; i < no_of_time; ++i)
	{
		clock_t tic = clock();
		key_generation();
		clock_t toc = clock();
		time = time+(double)(toc - tic) / (CLOCKS_PER_SEC);
		printf("count = %d\n", i);
		//printf("Elapsed: %f seconds %f sec\n", (double)(toc - tic) / (CLOCKS_PER_SEC), time);
	}
	printf("AVG TIME: %f seconds\n", time/no_of_time);
}


