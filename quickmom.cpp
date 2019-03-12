/*Ian Percy
CS584
Project - Quicksort
MOM Implementation

Code borrowed from GeeksforGeeks
https://www.geeksforgeeks.org/can-quicksort-implemented-onlogn-worst-case-time-complexity/

Test runs created as well as the generation for the arrays

This code file controls the Quicksort implementation while using a median-for-medians approach


*/

/* A worst case O(nLogn) implementation of quicksort */
#include<cstring> 
#include<iostream> 
#include<algorithm> 
#include<climits> 
#include<chrono>
using namespace std; 
using namespace std::chrono;
int size=1000;
// Following functions are taken from http://goo.gl/ih05BF 
int partition(int arr[], int l, int r, int k); 
int kthSmallest(int arr[], int l, int r, int k); 

/* A O(nLogn) time complexity function for sorting arr[l..h] */
void quickSort(int arr[], int l, int h) 
{ 
	if (l < h) 
	{ 
		// Find size of current subarray 
		int n = h-l+1; 

		// Find median of arr[]. 
		int med = kthSmallest(arr, l, h, n/2); 

		// Partition the array around median 
		int p = partition(arr, l, h, med); 

		// Recur for left and right of partition 
		quickSort(arr, l, p - 1); 
		quickSort(arr, p + 1, h); 
	} 
} 

// A simple function to find median of arr[]. This is called 
// only for an array of size 5 in this program. 
int findMedian(int arr[], int n) 
{ 
	sort(arr, arr+n); // Sort the array 
	return arr[n/2]; // Return middle element 
} 

// Returns k'th smallest element in arr[l..r] in worst case 
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT 
int kthSmallest(int arr[], int l, int r, int k) 
{ 
	// If k is smaller than number of elements in array 
	if (k > 0 && k <= r - l + 1) 
	{ 
		int n = r-l+1; // Number of elements in arr[l..r] 

		// Divide arr[] in groups of size 5, calculate median 
		// of every group and store it in median[] array. 
		int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups; 
		for (i=0; i<n/5; i++) 
			median[i] = findMedian(arr+l+i*5, 5); 
		if (i*5 < n) //For last group with less than 5 elements 
		{ 
			median[i] = findMedian(arr+l+i*5, n%5); 
			i++; 
		} 

		// Find median of all medians using recursive call. 
		// If median[] has only one element, then no need 
		// of recursive call 
		int medOfMed = (i == 1)? median[i-1]: 
								kthSmallest(median, 0, i-1, i/2); 

		// Partition the array around a random element and 
		// get position of pivot element in sorted array 
		int pos = partition(arr, l, r, medOfMed); 

		// If position is same as k 
		if (pos-l == k-1) 
			return arr[pos]; 
		if (pos-l > k-1) // If position is more, recur for left 
			return kthSmallest(arr, l, pos-1, k); 

		// Else recur for right subarray 
		return kthSmallest(arr, pos+1, r, k-pos+l-1); 
	} 

	// If k is more than number of elements in array 
	return INT_MAX; 
} 

//Swap function
void swap(int *a, int *b) 
{ 
	int temp = *a; 
	*a = *b; 
	*b = temp; 
} 

// It searches for x in arr[l..r], and partitions the array 
// around x. 
int partition(int arr[], int l, int r, int x) 
{ 
	// Search for x in arr[l..r] and move it to end 
	int i; 
	for (i=l; i<r; i++) 
		if (arr[i] == x) 
		break; 
	swap(&arr[i], &arr[r]); 

	// Standard partition algorithm 
	i = l; 
	for (int j = l; j <= r - 1; j++) 
	{ 
		if (arr[j] <= x) 
		{ 
			swap(&arr[i], &arr[j]); 
			i++; 
		} 
	} 
	swap(&arr[i], &arr[r]); 
	return i; 
} 

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		cout << arr[i] << " "; 
	cout << endl; 
} 
/* Function to make a random array */
void makeArray(int arr[], int size)
{
  srand(time(NULL));
  for(int i = 0; i<size; i++){
    arr[i]= 0 + rand() % 2000;
  }
}

/*Function to make array with increasing rank */
void makeArrayAsec(int arr[],int size)
{
  for(int i=0;i<size;i++)
    arr[i]=i;
}
/* Function to make an array with decreasing rank */
void makeArrayDesc(int arr[],int size)
{
  for(int i=0;i<size;i++)
    arr[i]=size-i;
}

// Driver program to test above functions 
int main() 
{ 
// set defaults
 int total = 0;
 int max =0;
 int count =1000;
 int sizeArray[] ={100000};
 int avgArray[9];
 int maxArray[9];
 int n = sizeof(sizeArray)/sizeof(sizeArray[0]);
 //loop through size of array 
for(int j=0;j<n;j++){
   max =0;
   total=0;
   int size = sizeArray[j]; 

  // Call Quicksort 1000 times (count)
 for(int i=0;i<count; i++){
   int rand[size];
   makeArray(rand,size);
 //printArray(rand,size); 
  // calculate run time
   auto start = high_resolution_clock::now();
	  quickSort(rand, 0, size-1); 
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop-start);
 //cout << duration.count() << endl;
  total = total + duration.count();
 // printArray(rand,size);
  if (duration.count() > max)
     max = duration.count();
  }
   avgArray[j]=total/count;
   maxArray[j]=max;
 }
// print for easy display of data
 for(int x=0;x<n;x++)
   cout << "For size " <<sizeArray[x]<<" MOM Average " << avgArray[x] << " max " << maxArray[x]<<endl;
	return 0; 
} 

