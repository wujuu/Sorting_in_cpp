// Sorting_in_cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

const int N = 10, K = 100000;

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

double* GetRandArr(int n, int k) {
	double* A = new double[n];
	for (int i = 0; i < n; i++) {
		double key = rand() % k;
		A[i] = key / k;
	}
	return A;
}

void PrintArr(double* A, int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

void BucketSort(double* &A, int n) {
	node** B=new node*[n];
	for (int i = 0; i < n; i++) B[i] = NULL;
	for (int i = 0; i < n; i++) Insert_node(B[(int)floor(n*A[i])], Get_node(A[i]));

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

bool Arr_check(double *A, int n) {
	for (int i = 1; i < n; i++) if (A[i] < A[i - 1]) return false;
	return true;
}





int main(){
	srand(time(NULL));
	
	double* A = GetRandArr(N, K);
	PrintArr(A,N);
	cout << Arr_check(A, N);
	cout << endl;

	BucketSort(A, N);

	PrintArr(A,N);
	cout << endl;
	cout << Arr_check(A, N);
	cout << endl;

	system("pause");
	cout << endl;
    return 0;
}

