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
		if (end) { // list is not empty
			ListNode* new_item = new ListNode;
			new_item->data = data;
			new_item->prev = this->end;
			new_item->next = nullptr;
			this->end = new_item;
			return new_item;
		} else { // list is empty
			ListNode* new_item = new ListNode;
			new_item->data = data;
			new_item->next = new_item->prev = nullptr;
			this->begin = this->end = new_item;
			return new_item;
		}
	}
};


int main() {
	DoublyLinkedList my_list;
	my_list.add(10);
	my_list.add(42);
	ListNode * last_added = my_list.add(123);
	std::cout<<"last item data is "<<last_added->data<<"; prev data is "<<last_added->prev->data<<std::endl;
	std::cout<<"last item data is "<<my_list.end->data<<"; prev data is "<<my_list.end->prev->data<<std::endl;
	return 0;
}


