// DoubleList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const int N = 20, K = 10000;

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
		double key = rand() % k;
		node* x = Get_node(key/k);
		Insert_node(first, x);
	}
	return first;
}





void Print_list(node* first) {
	for (node* x = first; x != NULL; x = x->next)
		cout << x->key << " ";
	cout << endl;
}



int main()
{
	srand(time(NULL));
	node* first = Get_list(N, K);
	Print_list(first);

	system("pause");
	cout << endl;
    return 0;
}

