/*
 * lesson_2021_03_02_sparse_list.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: KZ
 */

#include <iostream>

namespace lesson_2021_03_02_sparse_list {

struct ListNode {
	std::size_t index;
	int data;
	ListNode* prev;
	ListNode* next;

	ListNode(std::size_t index, int data, ListNode* prev = nullptr, ListNode* next =nullptr) {
		this->index = index;
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
};


struct SparseList {
	ListNode* begin;
	ListNode* end;
	std::size_t size;
	static const int EMPTY_VALUE = 0;

	SparseList() {
		this->begin = this->end = nullptr;
		this->size = 0;
	}

	void add(int data = EMPTY_VALUE) {
		if (data == EMPTY_VALUE) {
			this->size++;
			return;
		}
		ListNode* new_node = new ListNode(this->size, data, this->end);
		if (this->end) {
			this->end->next = new_node;
		} else {
			this->begin = new_node;
		}
		this->end = new_node;
		this->size++;

	}
};



int main() {
	SparseList mylist;
	mylist.add();
	mylist.add();
	mylist.add(123);
	std::cout<<mylist.size<<std::endl;



	return 0;
}
}


