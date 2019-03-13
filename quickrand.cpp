/* Ian Percy
  CS584
 Project
 Randomized Pivot Quicksort

 Code borrowed from GeeksforGeeks
https://www.geeksforgeeks.org/quicksort-using-random-pivoting/

Added addtional code for running the Quicksort loop and making arrays

This file is the randomized pivot Quicksort implementation

*/

#include <cstdlib>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int size=1000;
/* Swap function - to keep swap consistent between files */
void swap(int * a, int * b)
{
  int temp = *a;
  *a = *b;   
  *b = temp;
}

/* This function takes last element as pivot, places
  the pivot element at its correct position in sorted
  array, and places all smaller (smaller than pivot)
  to left of pivot and all greater elements to right
  of pivot */

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low);
  for(int j = low; j <= high -1; j++){

      if(arr[j] <= pivot){
        swap(&arr[i],&arr[j]); 
        i++;
      }
  }
  swap(&arr[i],&arr[high]);
  return i;
}
// Generates Random Pivot, swaps pivot with 
// end element and calls the partition function 
int partition_r(int arr[], int low, int high)
{
  srand(time(NULL));
  int random = low + rand() % (high-low);
  swap(&arr[random],&arr[high]);
  return partition(arr,low,high);

}
/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
  if (low < high){
    int pi = partition_r(arr,low,high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }

}
/* Function for printing array */
void printArray(int arr[], int size)
{
  int i;
  for (i =0; i< size; i++)
    printf("%d ", arr[i]);
  printf("\n");

}
/* Function for making the randomzied array */
void makeArray(int arr[], int size)
{
  srand(time(NULL));
  for(int i= 0; i<size; i++){
    arr[i] = 0 + rand() % 2000;
  }
}

/* Function for making an array with increasing rank */
void makeArrayAsec(int arr[], int size)
{
  for(int i =0;i<size;i++){
    arr[i]=i;
  }

}
/* Function for making an array with decreasing rank */
void makeArrayDesc(int arr[], int size)
{
  for(int i=0; i<size;i++)
  {
    arr[i]=size-i;
  }
}
int main()
{
  double result =0;
  int total =0;
  int count =1000;
  int max =0;
  int sizeArray[] = {100,1000,2000,5000,10000,15000,20000,50000,100000};
  int avgArray[9];
  int maxArray[9];
  int n = sizeof(sizeArray)/sizeof(sizeArray[0]);
  for(int j=0;j<n;j++){
//  loop through size of input array
    max =0;
    total=0;
    int size =  sizeArray[j];
//  int arr[] = {10,7,8,9,1,5};
    for(int i=0;i<count;i++){
//    loop 1000 times for Quicksort - or count
      int rand[size];
//    int n = sizeof(arr) / sizeof(arr[0]);
      makeArrayDesc(rand,size);
//    cout << "before"<<endl;
//    printArray(rand,size);

//    capture running time
      auto start = high_resolution_clock::now();
      quickSort(rand,0,size-1);
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stop-start);
//    cout << duration.count() <<endl;
      total = total + duration.count();
//    cout<< "After"<<endl;
//    printArray(rand,size);

    if(duration.count() > max)
     max = duration.count();
//   cout << total << endl;
   }
   avgArray[j]=total/count;
   maxArray[j]=max;
 }
//Print out details for easy viewing
   for(int x=0;x<n;x++)
    cout<<"For size " <<sizeArray[x]<< " average " <<avgArray[x]<<" max "<<maxArray[x]<<endl; 
 // cout <<"For Size " <<size<<" Average "<< total/count << " max "<<max  << endl;
  return 0;

}
