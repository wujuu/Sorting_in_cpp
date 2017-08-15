// Sorting_in_cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

const int N = 8, K = 100;

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



int* GetRandArr(int n, int k) {
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		A[i] = rand() % k;
	}
	return A;
}

void PrintArr(int* A, int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

void BucketSort(double* &A, int n) {
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

void CountSort(int *&A, int n, int k) {
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

void Swap(int *A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

int Partition(int* A, int start, int end) {
	int i = start - 1, j = end + 1, x = A[start];
	while (true) {
		do i++;
		while (A[i] < x);

		do j--;
		while (A[j] > x);

		if (i < j) Swap(A, i, j);
		else return j;
	}
}

void Quick_sort(int* A, int start=0, int end=N-1) {
	if (start < end) {
		int middle = Partition(A, start, end);
		Quick_sort(A, start, middle);
		Quick_sort(A, middle + 1, end);
	}
}

node* Merge_list(node* first1, node* first2) {
	node* result = NULL;

	while (first1 != NULL || first2 != NULL) {
		if (first2 == NULL)
			Add_head_node(result, Del_head_node(first1));
		else if (first1->key < first2->key) {
			Add_head_node(result, Del_head_node(first1));
			continue; }
		if (first1 == NULL)
			Add_head_node(result, Del_head_node(first2));
		else if (first1->key >= first2->key)
			Add_head_node(result, Del_head_node(first2));
	}
	return result;
}

bool Arr_check(double *A, int n) {
	for (int i = 1; i < n; i++) if (A[i] < A[i - 1]) return false;
	return true;
}





int main(){
	srand(time(NULL));
	node* list1 = Get_list(N, K);
	Print_list(list1);
	node* list2 = Get_list(N+5,K);
	Print_list(list2);
	node* result = Merge_list(list1, list2);
	Print_list(result);


	system("pause");
	cout << endl;
    return 0;
}

