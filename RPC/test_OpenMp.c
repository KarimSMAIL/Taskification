#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define NUM_THREADS 128
#define NUM_ITERATIONS 128

int test_func(int a, int b)
{
    return a + b;
}


/*we will test this pure function*/
int MAX(int X, int Y)
{
    if (X>Y) return X;
    else return Y;
}

int main(int argc, char const *argv[])
{

	int tab[128];
	int i, j=0;


	float temps;
    clock_t before, after;

    before = clock();

    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
    	/*//#pragma omp parallel
		for( i =0; i < ; i ++)
		{*/
			j = rand() % 128;
			tab[i] = MAX(i, j);
			//printf("%d\n", tab[i]);
		//}
    }
	
	
	after = clock();
	temps = (float)(after-before)/CLOCKS_PER_SEC;

	printf("le temps d'execution est : %f\n", temps);
	return 0;
}