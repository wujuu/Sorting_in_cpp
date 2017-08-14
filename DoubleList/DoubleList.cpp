// DoubleList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const int N = 20, K = 10;

struct node {
	double key;
	node* next;
	node* prev;

};

node* Get_node(int key) {
	node* x = new node;
	x->key = key;
	x->next = x->prev = NULL;
	return x;
}



node* Get_list(int n, int k) {
	node* first = NULL;
	for (int i = 0; i < n; i++) {
		node* x = Get_node(rand()%k);
		x->next = first;
		if(first!=NULL) first->prev = x;
		first = x;
	}
	return first;
}

node* Insert_node(node* &first, node* x) {
	if (first == NULL) first = x;
	else {
		node* tmp = first;
		for ( ; tmp->next != NULL && tmp->key < x->key; tmp = tmp->next);
		if (tmp->key < x->key) {
			tmp->next = x;
			x->prev = tmp;
		}
		else {
			x->next = tmp;
			x->prev = tmp->prev;
			tmp->prev->next = x;
			tmp->prev = x;
		}

	}
	
	
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

