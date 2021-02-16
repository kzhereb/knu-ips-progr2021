/*
 * lesson_2021_02_09_linked_list.cpp
 *
 *  Created on: Feb 9, 2021
 *      Author: KZ
 */
#include <iostream>

namespace lesson_2021_02_09_linked_list {

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
		this->size++;
		return new_item;
	}

	bool remove_by_value(int data_to_remove) {
		ListNode* to_remove = search(data_to_remove);
		if (to_remove) {
			remove_node(to_remove);
			return true;
		} else {
			return false;
		}
	}

	bool remove_by_pointer(ListNode* node_to_remove) {

	}

	bool remove_by_index(std::size_t index_to_remove) {
		ListNode* to_remove = get_by_index(index_to_remove);
		if (to_remove) {
			remove_node(to_remove);
			return true;
		} else {
			return false;
		}
	}

	void partial_order() {
		ListNode* current = this->begin;
		ListNode* next;
		int value = this->begin->data;

		while (next = current->next) {
			if (next->data < value) {
				current->next = next->next;
				next->next = this->begin;
				this->begin = next;
			} else {
				current = next;
			}
		}

	}

	ListNode* search(int data_to_search) {
		ListNode* current = begin;
		while (current) {
			if (current->data == data_to_search) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	ListNode* get_by_index(std::size_t index_to_find) {
		if (index_to_find >= this->size) {
			return nullptr;
		}
		bool from_begin = false;
		if (index_to_find < size/2) {
			from_begin = true;
		}
		ListNode* current = from_begin ? begin : end;
		std::size_t current_index = from_begin ? 0 : size - 1;
		while (current) {
			if (current_index == index_to_find) {
				return current;
			}
			if (from_begin) {
				current = current->next;
				current_index++;
			} else {
				current = current->prev;
				current_index--;
			}
		}
		return nullptr;
	}

	void print() {
		ListNode* current = begin;
		while (current) {
			std::cout<<current->data<<" ";
			current = current->next;
		}
		std::cout<<std::endl;
	}

private:
	ListNode* remove_node(ListNode* current) {
		if (current->prev) {
			current->prev->next = current->next;
		} else {
			this->begin = current->next;
		}
		if (current->next) {
			current->next->prev = current->prev;
		} else {
			this->end = current->prev;
		}
		delete current;
		this->size--;
		return current;
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
	std::cout<<my_list.size<<std::endl;
	ListNode* found = my_list.search(42);
	std::cout<<"searching for 42, found ptr="<<found<<", value = "<<found->data<<std::endl;
	found = my_list.search(45);
	std::cout<<"searching for 45, found ptr="<<found<<std::endl;

	bool removed = my_list.remove_by_value(45);
	if (removed) {
		std::cout<<"removed value 45"<<std::endl;

	} else {
		std::cout<<"value 45 not removed"<<std::endl;
	}
	my_list.print();
	removed = my_list.remove_by_value(42);
	if (removed) {
		std::cout<<"removed value 42"<<std::endl;

	} else {
		std::cout<<"value 42 not removed"<<std::endl;
	}
	my_list.print();

	removed = my_list.remove_by_value(123);
	if (removed) {
		std::cout<<"removed value 123"<<std::endl;

	} else {
		std::cout<<"value 123 not removed"<<std::endl;
	}
	my_list.print();

	my_list.add(43);
	my_list.add(124);
	my_list.print();

	removed = my_list.remove_by_value(10);
	if (removed) {
		std::cout<<"removed value 10"<<std::endl;

	} else {
		std::cout<<"value 10 not removed"<<std::endl;
	}
	my_list.print();

	my_list.add(567);
	my_list.add(890);
	my_list.print();

	removed = my_list.remove_by_index(2);
	if (removed) {
		std::cout << "removed index 2" << std::endl;

	} else {
		std::cout << "index 2 not removed" << std::endl;
	}
	my_list.print();

	found = my_list.get_by_index(1);
	if (found) {
		std::cout << "found at index 1 value " << found->data << std::endl;

	} else {
		std::cout << "index 1 not found" << std::endl;
	}

	found = my_list.get_by_index(10);
	if (found) {
		std::cout << "found at index 10 value " << found->data << std::endl;

	} else {
		std::cout << "index 10 not found" << std::endl;
	}

	DoublyLinkedList list_to_order;
	list_to_order.add(10);
	list_to_order.add(3);
	list_to_order.add(125);
	list_to_order.add(4);

	std::cout<<"before partial order"<<std::endl;
	list_to_order.print();

	list_to_order.partial_order();

	std::cout<<"after partial order"<<std::endl;
	list_to_order.print();



	return 0;
}
}

