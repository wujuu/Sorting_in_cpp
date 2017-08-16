// Sorting_in_cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

const int N = 20, K = 100;

//LISTS
//Basic
struct node {
	double key;
	node* next;
};
node* Get_node(double key) {
	node* x = new node;
	x->key = key;
	x->next = NULL;
	return x;
}
void Insert_node(node* &first, node* x) {
	node* war = new node;
	war->next = first;

	while (war->next != NULL && war->next->key < x->key) war = war->next;
	if (war->next == first) first = x;
	x->next = war->next;
	war->next = x;
}
node* Get_list(int n, int k) {
	node* first = NULL;
	for (int i = 0; i < n; i++) {
		node* x = Get_node(rand()%k);
		Insert_node(first, x);
	}
	return first;
}
void Print_list(node* first) {
	for (node* x = first; x != NULL; x = x->next)
		cout << x->key << " ";
	cout << endl;
}
void Add_head_node(node* &first, node* x) {
		x->next = first;
		first = x;
}
node* Del_head_node(node* &first) {
	node* tmp = first;
	first = first->next;
	return tmp;
}

//ARRAY FUNCTIONS
//Basic 
void Swap(int *A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}
int* Get_array(int n, int k) {
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		A[i] = rand() % k;
	}
	return A;
}
void Print_array (int* A, int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}
int Search_sorted_array(int* A, int x, int end, int start=0) {
	if (start <= end) {
		int k = (start + end) / 2;
		if (x == A[k]) return k;
		else if (x < A[k]) Search_sorted_array(A, x, start, k - 1);
		else Search_sorted_array(A, x, k + 1, end);
	} 
	else return -1;
}
//Bucket sort
void Bucket_sort(double* &A, int n) {
	node** B=new node*[n];

	for (int i = 0; i < n; i++) 
		B[i] = NULL;

	for (int i = 0; i < n; i++) 
		Insert_node(B[(int)floor(n*A[i])], Get_node(A[i]));

	int j = 0;

	for (int i = 0; i < n; i++) {
		while (B[i] != NULL) {
			A[j] = B[i]->key;
			B[i] = B[i]->next;
			j++;
		}
	}
}
//Count sort
void Count_sort(int *&A, int n, int k) {
	int *B = new int[n], *C = new int[k];

	for (int i = 0; i < k; i++)
		C[i] = 0;

	for (int i = 0; i < n; i++)
		C[A[i]]++;

	for (int i = 1; i < k; i++)
		C[i] += C[i - 1];

	for (int i = n-1; i >= 0; i--) {
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}

	A = B;
}
//Quick sort
int Partition(int* A, int start, int end) {
	int i = start - 1, j = end + 1, x = A[start];
	while (true) {
		do i++; while (A[i] < x);
		do j--; while (A[j] > x);
		if (i < j) Swap(A, i, j);
		else return j;
	}
}
void Quick_sort(int* A, int end, int start=0) {
	if (start < end) {
		int middle = Partition(A, end, start);
		Quick_sort(A, middle, start);
		Quick_sort(A, end, middle+1);
	}
}
//Heap sort
int Parent(int i) {
	return (i - 1) / 2;
}
int Left(int i) {
	return 2 * i + 1;
}
int Right(int i) {
	return 2 * i + 2;
}
void Heapify(int* A, int i, int n) {
	int imax = i;

	if (Left(i) < n && A[Left(i)] > A[imax]) 
		imax = Left(i);

	if (Right(i) < n && A[Right(i)] > A[imax]) 
		imax = Right(i);

	if (imax != i) {
		Swap(A, i, imax);
		Heapify(A, imax, n);
	}
}
void Make_heap(int* A, int n) {
	for (int i = Parent(n - 1); i >= 0; i--)
		Heapify(A, i, n);
}
void Heap_sort(int* A, int n) {
	Make_heap(A, n);

	for (int i = n - 1; i >= 1; i--) {
		Swap(A, i, 0);
		Heapify(A, 0, i);
	}
}
//Merge sort
void Merge_two(int* A, int start, int middle, int end) {
	int *Tmp = new int[end - start + 1], i = start, j = middle + 1, k = 0;
	
	while (i <= middle && j <= end) {
		if (A[i] < A[j]) { Tmp[k] = A[i]; i++;}
		else { Tmp[k] = A[j]; j++; }
		k++; }

	if (i <= middle) for (; i <= middle; i++) { Tmp[k] = A[i]; k++; }
	else if (j <= end) for (; j <= end; j++) { Tmp[k] = A[j]; k++; }

	for (int l = 0; l < (end - start + 1); l++) A[l + start] = Tmp[l];

	delete[] Tmp;
}
void Merge_sort(int* A, int start, int end) {
	if (start < end) {
		int middle = (start + end) / 2;
		Merge_sort(A, start, middle);
		Merge_sort(A, middle+1, end);
		Merge_two(A, start, middle, end);
	}
}

//MAIN
int main(){
	int* A = Get_array(N, K);
	Print_array(A, N);
	Merge_sort(A,0,N-1);
	Print_array(A, N);

	system("pause");
	cout << endl;
    return 0;
}

