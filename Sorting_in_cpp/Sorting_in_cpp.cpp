// Sorting_in_cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

const int N = 20, K = 10;

struct Node {
	float key;
	Node* next;
	Node* prev;
};

Node* NewNode(float key) {
	Node* x = new Node;
	x->key = key;
	x->next = NULL;
	x->prev = NULL;
	return x;
}

void ListInsert(Node* &first, float key) {
	Node* x = NewNode(key);
	if (first == NULL) { first = x; return; }
	Node* tmp;
	for (tmp = first; tmp->key < x->key && tmp->next != NULL; tmp = tmp->next);
	x->next = tmp->next;
	tmp->next = x;
	x->prev = tmp;
	if (tmp == first) first = x;
}

float* GetRandArr(int n, int k) {
	float* A = new float[n];

	for (int i = 0; i < n; i++)
		A[i] = (rand() % k)/k;

	return A;
}

void PrintArr(float* A, int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";

	cout << endl;
}

void BucketSort(float* &A, int n) {
	Node** B=new Node*[n];
	for (int i = 0; i < n; i++) B[i] = NULL;
	for (int i = 0; i < n; i++) ListInsert(B[ (int)floor(n*A[i]) ], A[i]);

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





int main(){
	srand(time(NULL));
	
	float* A = GetRandArr(N, K);
	PrintArr(A,N);

	BucketSort(A, N);

	PrintArr(A,N);


	system("pause");
	cout << endl;
    return 0;
}

