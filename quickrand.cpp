#include <cstdlib>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low-1);
  for(int j = low; j <= high -1; j++){

      if(arr[j] <= pivot){
        i++;
        swap(arr[i],arr[j]); 
      }
  }
  swap(arr[i+1],arr[high]);
  return (i+1);
}

int partition_r(int arr[], int low, int high)
{
  srand(time(NULL));
  int random = low + rand() % (high-low);
  swap(arr[random],arr[high]);
  return partition(arr,low,high);

}

void quickSort(int arr[], int low, int high)
{
  if (low < high){
    int pi = partition_r(arr,low,high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }

}

void printArray(int arr[], int size)
{
  int i;
  for (i =0; i< size; i++)
    printf("%d ", arr[i]);
  printf("\n");

}
void makeArray(int arr[], int size)
{
  srand(time(NULL));
  for(int i= 0; i<size; i++){
    arr[i] = 0 + rand() % 2000;
  }
}
int main()
{
//  int arr[] = {10,7,8,9,1,5};
  int size = 2000;
  int rand[size];
//  int n = sizeof(arr) / sizeof(arr[0]);
  makeArray(rand,size);
  auto start = high_resolution_clock::now();
  quickSort(rand,0,size-1);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop-start);
  cout << duration.count() <<endl;
  printArray(rand,size);
  return 0;

}
