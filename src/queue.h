/*
 * queue.h
 *
 *  Created on: Apr 21, 2021
 *      Author: KZ
 */

#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <iostream>
#include <exception>
#include <cassert>

template<typename T>
struct ListNode {
	T value;
	ListNode* next;
	ListNode(T value, ListNode* next = nullptr) {
		this->value = value;
		this->next = next;
	}
};
template<typename T>
struct Stack {
	std::size_t size;
	ListNode<T>* top;

	Stack() {
		this->size = 0;
		this->top = nullptr;
	}


	void push(T value) {
		ListNode<T>* new_node = new ListNode<T>(value, this->top);
		this->top = new_node;
		size++;
	}

	int pop_minus1() {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			return -1;
		}
		ListNode<T>* current = this->top;
		this->top = this->top->next;
		T result = current->value;
		delete current;
		size--;
		return result;

	}

	bool pop_bool(T& result) {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			return false;
		}
		ListNode<T>* current = this->top;
		this->top = this->top->next;
		result = current->value;
		delete current;
		size--;
		return true;
	}

	T* pop_pointer() {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			return nullptr;
		}
		ListNode<T>* current = this->top;
		this->top = this->top->next;
		T* result = new int;
		*result = current->value;
		delete current;
		size--;
		return result;
	}

	T pop_exception_string() {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			throw "Trying to pop item from empty stack";
		}
		ListNode<T>* current = this->top;
		this->top = this->top->next;
		T result = current->value;
		delete current;
		size--;
		return result;

	}

	T pop_exception() {
		if (this->top == nullptr) {
			//std::cout<<"Trying to pop item from empty stack"<<std::endl;
			throw std::logic_error("Trying to pop item from empty stack");
		}
		ListNode<T>* current = this->top;
		this->top = this->top->next;
		T result = current->value;
		delete current;
		size--;
		return result;

	}

	T pop_assert() {
		assert(this->top != nullptr); // Trying to pop item from empty stack

		ListNode<T>* current = this->top;
		this->top = this->top->next;
		T result = current->value;
		delete current;
		size--;
		return result;

	}

	T pop_assert_with_message() {
		assert(this->top != nullptr && "Trying to pop item from empty stack");

		ListNode<T>* current = this->top;
		this->top = this->top->next;
		T result = current->value;
		delete current;
		size--;
		return result;

	}

	T pop() {
		return pop_assert_with_message();
	}
	T peek() {
		assert(this->top && "Trying to peek into empty stack");
		return this->top->value;
	}

	void clear() {
		ListNode<T>* current = this->top;
		while (this->top) {
			this->top = this->top->next;
			delete current;
			current = this->top;
		}
		this->size = 0;
	}

	bool is_empty() {
		return this->top == nullptr;
	}

	void print() {
		ListNode<T>* current = this->top;
		while (current) {
			std::cout<<current->value<<" ";
			current = current->next;
		}
		std::cout<<std::endl;
	}
};

template<typename T>
struct Queue {
	ListNode<T>* begin;
	ListNode<T>* end;

	Queue() {
		this->begin = this->end = nullptr;
	}

	void enqueue(T value) {
		ListNode<T>* new_item = new ListNode<T>(value);
		if (this->end) {
			this->end->next = new_item;
		} else {
			this->begin = new_item;
		}
		this->end = new_item;
	}

	T dequeue() {
		assert(this->begin && "Trying to dequeue from empty queue");

		T result = this->begin->value;
		ListNode<T>* current = this->begin;
		this->begin = this->begin->next;
		if (this->begin == nullptr) {
			this->end = nullptr;
		}
		delete current;

		return result;
	}
};



#endif /* SRC_QUEUE_H_ */
