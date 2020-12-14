#include <mpi.h>
#include <mpi_accelerator.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ITERATIONS 2

/* /!\ we need rdynamic or dlsym does not work */
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

int main(int argc, char *argv[])
{

	int t_level;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &t_level);
	
	MPIX_Accelerator_init();

	int rank, size, i;

	MPI_Request * work_requests = malloc(size * sizeof(MPI_Request));



    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    

    double before = MPI_Wtime();
	for (i = 0; i < NUM_ITERATIONS; ++i)
	{
		for( i = 0 ; i < size ; i++ )
	    {
	    	int j = rand() % size;
	    	int * response_buffer = malloc(size * sizeof(int));

	        MPI_Datatype param[2] = {MPI_INT, MPI_INT};
	        void* buffers[2] = {&i, &j};

	        MPIX_Ioffload(buffers,
	                    param,
	                    2,
	                    &response_buffer[i],
	                    MPI_INT,
	                    "MAX",
	                    i,
	                    &work_requests[i]);
	    }

	    MPI_Waitall(size, work_requests, MPI_STATUSES_IGNORE);
	}
   

    double after = MPI_Wtime();

    double total_time = after - before;

    printf("le temps execution est : %f\n",total_time);

    MPIX_Accelerator_finalize();

    MPI_Finalize();
	return 0;
}