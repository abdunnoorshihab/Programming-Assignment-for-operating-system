#include <stdio.h> #include <stdlib.h> #include <pthread.h>
#define MAX_SIZE 100
int arr[MAX_SIZE]; // global array to hold input array
int sorted_arr[MAX_SIZE]; // global array to hold sorted array
void merge(int left, int mid, int right) {
// function to merge two sorted subarrays int i = left, j = mid + 1, k = left; while (i <= mid && j <= right) {
if (arr[i] <= arr[j]) { sorted_arr[k++] = arr[i++];
} else {
sorted_arr[k++] = arr[j++];
}
}
while (i <= mid) { sorted_arr[k++] = arr[i++];
}
while (j <= right) { sorted_arr[k++] = arr[j++];
}
for (i = left; i <= right; i++) { arr[i] = sorted_arr[i];
}
}
void* merge_sort(void* arg) {
// function to recursively sort subarrays using merge sort int* args = (int*) arg;
int left = args[0]; int right = args[1]; if (left < right) {
int mid = (left + right) / 2; int largs[2] = {left, mid};
int rargs[2] = {mid + 1, right};
pthread_t tid[2]; // array of thread IDs to hold child threads pthread_create(&tid[0], NULL, merge_sort, (void*) largs); // create left
child thread
pthread_create(&tid[1], NULL, merge_sort, (void*) rargs); // create right child thread
pthread_join(tid[0], NULL); // wait for left child thread to complete pthread_join(tid[1], NULL); // wait for right child thread to complete merge(left, mid, right); // merge the two sorted subarrays
}
pthread_exit(NULL);
}
int main() {
int n = 0, i = 0; char c = ' ';
printf("Enter the elements of the array separated by spaces: "); while (c != '\n' && i < MAX_SIZE) {
scanf("%d%c", &arr[i], &c); // take input array from user i++;
n++;
}
int left = 0;
int right = n - 1;
int args[2] = {left, right}; pthread_t tid;
pthread_create(&tid, NULL, merge_sort, (void*) args); // create parent thread to sort the entire array
pthread_join(tid, NULL); // wait for parent thread to complete printf("Sorted array: ");
for (i = 0; i < n; i++) {
printf("%d ", arr[i]); // print the sorted array
}
printf("\n"); return 0;
}

