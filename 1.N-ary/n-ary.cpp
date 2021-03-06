#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<omp.h>
using namespace std;
void NarySearch (int *A, int lo, int hi, int key, int Ntrvl, int *pos)
{
	float offset, step;
	int *mid = new int[Ntrvl+1];
	char *locate = new char[Ntrvl+2];
	int i;
	int tot_threads;
	int thrd_num;
	locate[0] = 'R'; locate[Ntrvl+1] = 'L';
 	printf("\nTotal number of threads : %d\n",Ntrvl);
 	
	#pragma omp parallel num_threads(Ntrvl)
 	{
 		while(lo <= hi && *pos == -1) 
		{
		int lmid;
 		#pragma omp single
   		{
   			
    			mid[0] = lo - 1;
    			step = (float)(hi - lo +1)/(Ntrvl+1);
    			
    		}
 		#pragma omp for private(offset) firstprivate(step)
		for (i = 1; i <= Ntrvl; i++) 
		{
			offset = step* i + (i - 1);
			lmid = mid[i] = lo + (int)offset;
			if(lmid <= hi) {
	 			if(A[lmid] > key)
	  				locate[i] = 'L';
	 			else if (A[lmid] < key)
	  				locate[i] = 'R';
	 			else 
				{
	  				locate[i] = 'E';
	   				*pos = lmid; 
	   				thrd_num = omp_get_thread_num();
					printf("Number found by thread %d",thrd_num);
					} //found
	    			}
			else {
	  			mid[i] = hi + 1;
	  			locate[i] = 'L';
			}
       	}
 		#pragma omp single
		{
    			for (i = 1; i <= Ntrvl; i++)
			{
      		if (locate[i] != locate[i-1]) {
        			lo = mid[i-1] + 1;
        			hi = mid[i] - 1;
      		}
   			}
   			if (locate[Ntrvl] != locate[Ntrvl+1]) lo = mid[Ntrvl] +1;
   		}  // end single
  		} //End of while
 	} // end parallel region
}

int main()
{
int A[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int lo = 0;
int hi = 19;
int key = 19;
int Ntrvl = 4;
int pos = -1;
double start_time = omp_get_wtime();
NarySearch(A,lo,hi,key,Ntrvl,&pos);
cout<<"\nTotal time taken to execute n-ary search: "<<omp_get_wtime() - start_time<<endl;
}

/*========= Output ==========

guest-DTUOCI@comp12:~/Desktop$ g++ -fopenmp n-ary.cpp
guest-DTUOCI@comp12:~/Desktop$ ./a.out

Total number of threads : 4
Number found by thread 0
Total time taken to execute n-ary search: 0.00179503


*/



