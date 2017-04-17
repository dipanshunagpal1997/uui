#include<iostream>
using namespace std;

void quick_sort(int array[], int begin, int end);
int partition(int array[], int begin, int end);
int k=0;			//thread id
int main()
{
	int n;

	cout<<"Enter No of Elements : ";
	cin>>n;
	
            int array[n];
	
            cout<<"Enter Elements : ";
	for(int i = 0; i < n; i++)
	{
		cin>>array[i];
	}

	quick_sort(array,0,n-1);

	cout<<"Sorted Elements : ";
	for(int i = 0; i < n; i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
	return 0;
}

void quick_sort(int array[], int begin, int end)
{
	int pivot;
	if(begin<end)
	{
		pivot = partition(array,begin,end);
		cout<<"Pivot element with index "<<pivot<<" has been found out by thread      				"<<k<<"\n";

		#pragma omp parallel sections
		{
			#pragma omp section		//Left partition
			{
				k=k+1;			
				quick_sort(array,begin,pivot-1);
			}

			#pragma omp section		//Right partition
			{
				k=k+1;			
				quick_sort(array,pivot+1,end);
			}
		}
	}//if
}//quick_sort

int partition(int array[], int begin, int end)
{
	int temp;
	int pivot = array[begin];
	int p = begin+1;
	int q = end;

	while(1)
	{
		while(p < end && pivot >= array[p])
			p++;

		while(pivot < array[q])
			q--;

		if(p < q)
		{
			temp = array[p];
			array[p] = array[q];
			array[q] = temp;
		}
		else
		{
			temp= array[begin];
			array[begin] = array[q];
			array[q]= temp;
			return(q);
		}//else

	}//while

}//partition





OUTPUT:
pccoe@212A-09:~/Desktop$ g++ -fopenmp quick_sort_arm.cpp 
pccoe@212A-09:~/Desktop$ ./a.out
