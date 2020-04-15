#include <mpi_accelerator.h>
#include <stdio.h>

int foo(int par)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	return rank + par;
}


int main(int argc, char ** argv)
{
	int sup;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &sup);
	MPIX_Accelerator_init();

	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("%d/%d\n", rank, size);

	if( rank == 0 )
	{


		


		int tab[128];
		MPI_Request req[128];
		int i;

#if 0
		for( i = 0; i < 128; i++)
			tab[i] = foo(i);
#endif


		for(i=0; i < 128; i++)
		{
			void *addr[1] = {&i};

			MPIX_Ioffload(addr,
				     &type,
				     1,
				     &tab[i],
				     MPI_INT,
			             "foo",
				     (i)%size,
				     &req[i]);

		}

		MPI_Waitall(req, 128, MPI_STATUSES_IGNORE);

		//tab[i] valide




		for(i=1; i < size; i++)
		{

			int ret;
			MPI_Datatype type = MPI_INT;


			MPIX_Offload(addr,
				     &type,
				     1,
				     &ret,
				     MPI_INT,
			             "foo",
				     i);


			printf("Call foo(%d) on %d returned %d\n",i, i, ret);
		}


	}



	MPIX_Accelerator_finalize();	
	MPI_Finalize();

	return 0;
}
