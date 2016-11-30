/*
 * LLSE.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: Debra
 */

#include "Node.hpp"
#include "LLSE.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

LLSE::LLSE() {
	first = NULL;
	last = NULL;
	size = 0;
}
LLSE::~LLSE() {
	Node *tmp = first;
	for(int i = 0; i < size; i++) {
		tmp = first->next;
		delete first;
		first = tmp;
	}
}

void LLSE::printLL() {
	Node *tmp = first;
	while (tmp != NULL) {
		cout << tmp->count <<":"<<tmp->word << endl;
		tmp = tmp->next;
	}
}

void LLSE::addFirst(string w) {
	first = new Node(w);
	last = first;
	size = 1;
}



void LLSE::insertUnique(string w) {
	Node *tmp = first;
	if (tmp == NULL) {
		addFirst(w);
	}
	else {
		while (tmp != NULL && tmp->word < w)  {
			tmp = tmp->next;
		}
		if ((tmp!= NULL) && (tmp->word == w)) {
			tmp->count++;
		}
		else {
			Node *tmp2 = new Node(w);
			if (tmp != NULL) {
				if (tmp->prev != NULL) {
					tmp->prev->next = tmp2;
					tmp2->prev = tmp->prev;
				}
				else {
					first = tmp2;
				}
				tmp2->next = tmp;
				tmp->prev = tmp2;
			}
			else {
				last->next = tmp2;
				tmp2->prev = last;
				last = tmp2;
			}
			size++;

		}
	}
}

// Write an insertion Sort on the linked list (not an array, 
// a linked list!
void LLSE::insertionSortLL() {
	int i, j;
	Node * key = new Node;
	Node * temp = new Node;
	temp = first;
	for (i = 1; i < size; i++) {
		key = first->next;
		for (j = i - 1; j >= 0 && temp < key; j--) {
			temp->next = temp;
		} // for
		temp->next = key;
	} // for
} // insertionSortLL


// Convert the linked list to an array of nodes and return that array
Node *LLSE::convertToArray() {
	Node * temp = new Node;
	temp = first;
	Node * arr = new Node[size];
	for (int i = 0; i < size; i++) {
		arr[i] = temp;
		temp = temp->next;
	} // for
	return arr;
} // convertToArray

// For the quicksort - the partition
int LLSE::partition(Node ** arr, int beg,int end) {
	string pivot = arr[end]->count;
	int i = beg - 1;
	string temp;
	string temp2;
	for (int j = beg; j <= end - 1; j++) {
		if (arr[j]->count <= pivot) {
			i += 1;
			temp = arr[i]->word;
			arr[i] = arr[j];
			arr[j] = temp;
		} // if
	} // for
	temp2 = arr[i + 1]->word;
	arr[i + 1] = arr[end];
	arr[end] = temp2;
	return i + 1;
} // partition


// your recursive quicksort
void LLSE::quickSort(Node ** arr, int beg, int end) {
	if (beg < end) {
		int mark = partition(arr, beg, end);
		quickSort(arr, beg, mark - 1);
		quickSort(arr, mark + 1, end);
	} // if
} // quickSort

//Take the linked list and create a binary heap
Node *LLSE::makeHeap(Node ** arr, int s, int root) {
	int max = root;
	int left = (2 * root) + 1;
	int right = (2 * root) + 2;

	if (left < s && arr[left]->count > arr[max]->count) {
		max = left;
	} // if
	if (right < s && arr[right]->count > arr[max]->count) {
		max = right;
	} // if
	if (max != root) {
		Node * temp = new Node;
		temp = arr[root];
		arr[root] = arr[max];
		arr[max] = temp;
		makeHeap(arr, s, max);
	} // if
	return arr;
} // makeHeap

//Sort the heap array using heapsort
void LLSE::heapSort(Node ** arr, int s) {
	for (int i = (s / 2) - 1; i >= 0; i--) {
		makeHeap(arr, s, i);
	} // for
	for (int j = s - 1; j >= 0; j--) {
		Node * temp = new temp;
		temp = arr[j];
		arr[j] = arr[0];
		arr[0] = temp;
		makeHeap(arr, j, 0);
	} // for
} // heapSort

