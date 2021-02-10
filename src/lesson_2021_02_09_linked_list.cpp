/*
 * lesson_2021_02_09_linked_list.cpp
 *
 *  Created on: Feb 9, 2021
 *      Author: KZ
 */
#include <iostream>

struct ListNode {
	int data;
	ListNode* prev;
	ListNode* next;
	ListNode(int data, ListNode* prev = nullptr, ListNode* next = nullptr) {
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
};

struct DoublyLinkedList {
	ListNode* begin;
	ListNode* end;
	std::size_t size;

	DoublyLinkedList() {
		begin = nullptr;
		end = nullptr;
		size = 0;
	}

	ListNode* add(int data) {
		ListNode* new_item = new ListNode(data, this->end);
		if (end) { // list is not empty
			this->end->next = new_item;
		} else { // list is empty
			this->begin = new_item;
		}
		this->end = new_item;
		return new_item;
	}

	void print() {
		ListNode* current = begin;
		while (current) {
			std::cout<<current->data<<" ";
			current = current->next;
		}
		std::cout<<std::endl;
	}
};


int main() {
	DoublyLinkedList my_list;
	my_list.add(10);
	my_list.add(42);
	ListNode * last_added = my_list.add(123);
	std::cout<<"last item data is "<<last_added->data<<"; prev data is "<<last_added->prev->data<<std::endl;
	std::cout<<"last item data is "<<my_list.end->data<<"; prev data is "<<my_list.end->prev->data<<std::endl;
	my_list.print();

	return 0;
}


