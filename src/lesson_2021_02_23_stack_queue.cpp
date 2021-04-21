/*
 * lesson_2021_02_23_stack_queue.cpp
 *
 *  Created on: Feb 23, 2021
 *      Author: KZ
 */




//#define NDEBUG  // disable asserts; should be enabled automatically in release mode

#include "queue.h"
#include <iostream>
#include <cassert>

namespace lesson_2021_02_23_stack_queue {

//struct ListNode {
//	int value;
//	ListNode* next;
//	ListNode(int value, ListNode* next = nullptr) {
//		this->value = value;
//		this->next = next;
//	}
//};
//
//struct Stack {
//	std::size_t size;
//	ListNode* top;
//
//	Stack() {
//		this->size = 0;
//		this->top = nullptr;
//	}
//
//
//	void push(int value) {
//		ListNode* new_node = new ListNode(value, this->top);
//		this->top = new_node;
//		size++;
//	}
//
//	int pop_minus1() {
//		if (this->top == nullptr) {
//			std::cout<<"Trying to pop item from empty stack"<<std::endl;
//			return -1;
//		}
//		ListNode* current = this->top;
//		this->top = this->top->next;
//		int result = current->value;
//		delete current;
//		size--;
//		return result;
//
//	}
//
//	bool pop_bool(int& result) {
//		if (this->top == nullptr) {
//			std::cout<<"Trying to pop item from empty stack"<<std::endl;
//			return false;
//		}
//		ListNode* current = this->top;
//		this->top = this->top->next;
//		result = current->value;
//		delete current;
//		size--;
//		return true;
//	}
//
//	int* pop_pointer() {
//		if (this->top == nullptr) {
//			std::cout<<"Trying to pop item from empty stack"<<std::endl;
//			return nullptr;
//		}
//		ListNode* current = this->top;
//		this->top = this->top->next;
//		int* result = new int;
//		*result = current->value;
//		delete current;
//		size--;
//		return result;
//	}
//
//	int pop_exception_string() {
//		if (this->top == nullptr) {
//			std::cout<<"Trying to pop item from empty stack"<<std::endl;
//			throw "Trying to pop item from empty stack";
//		}
//		ListNode* current = this->top;
//		this->top = this->top->next;
//		int result = current->value;
//		delete current;
//		size--;
//		return result;
//
//	}
//
//	int pop_exception() {
//		if (this->top == nullptr) {
//			//std::cout<<"Trying to pop item from empty stack"<<std::endl;
//			throw std::logic_error("Trying to pop item from empty stack");
//		}
//		ListNode* current = this->top;
//		this->top = this->top->next;
//		int result = current->value;
//		delete current;
//		size--;
//		return result;
//
//	}
//
//	int pop_assert() {
//		assert(this->top != nullptr); // Trying to pop item from empty stack
//
//		ListNode* current = this->top;
//		this->top = this->top->next;
//		int result = current->value;
//		delete current;
//		size--;
//		return result;
//
//	}
//
//	int pop_assert_with_message() {
//		assert(this->top != nullptr && "Trying to pop item from empty stack");
//
//		ListNode* current = this->top;
//		this->top = this->top->next;
//		int result = current->value;
//		delete current;
//		size--;
//		return result;
//
//	}
//
//	int pop() {
//		return pop_assert_with_message();
//	}
//	int peek() {
//		assert(this->top && "Trying to peek into empty stack");
//		return this->top->value;
//	}
//
//	void clear() {
//		ListNode* current = this->top;
//		while (this->top) {
//			this->top = this->top->next;
//			delete current;
//			current = this->top;
//		}
//		this->size = 0;
//	}
//
//	bool is_empty() {
//		return this->top == nullptr;
//	}
//
//	void print() {
//		ListNode* current = this->top;
//		while (current) {
//			std::cout<<current->value<<" ";
//			current = current->next;
//		}
//		std::cout<<std::endl;
//	}
//};
//
//
//struct Queue {
//	ListNode* begin;
//	ListNode* end;
//
//	Queue() {
//		this->begin = this->end = nullptr;
//	}
//
//	void enqueue(int value) {
//		ListNode* new_item = new ListNode(value);
//		if (this->end) {
//			this->end->next = new_item;
//		} else {
//			this->begin = new_item;
//		}
//		this->end = new_item;
//	}
//
//	int dequeue() {
//		assert(this->begin && "Trying to dequeue from empty queue");
//
//		int result = this->begin->value;
//		ListNode* current = this->begin;
//		this->begin = this->begin->next;
//		if (this->begin == nullptr) {
//			this->end = nullptr;
//		}
//		delete current;
//
//		return result;
//	}
//};



#define POP_PRINT std::cout<<mystack.pop()<<std::endl;
//#define POP_PRINT if (mystack.pop_bool(result)) {std::cout<<result<<std::endl;}
//#define POP_PRINT std::cout<<*mystack.pop_pointer()<<std::endl; //error
//#define POP_PRINT if(mystack.pop_pointer() != nullptr) {std::cout<<*mystack.pop_pointer()<<std::endl;} // call pop twice
//#define POP_PRINT p_result = mystack.pop_pointer(); if(p_result) {std::cout<<*p_result<<std::endl;} // memory leak
//#define POP_PRINT p_result = mystack.pop_pointer(); if(p_result) {std::cout<<*p_result<<std::endl; delete p_result;}
//#define POP_PRINT std::cout<<mystack.pop_exception()<<std::endl; //crashes on exception
//#define POP_PRINT try { std::cout<<mystack.pop_exception_string()<<std::endl; } catch (...) {std::cout<<"exception"<<std::endl;}
//#define POP_PRINT try { std::cout<<mystack.pop_exception()<<std::endl; } catch (const std::logic_error& e) {std::cerr<<e.what()<<std::endl;}
//#define POP_PRINT std::cout<<mystack.pop_assert()<<std::endl;
//#define POP_PRINT std::cout<<mystack.pop_assert_with_message()<<std::endl;

int main() {
	Stack<int> mystack;
	mystack.push(123);
	mystack.push(45);
	mystack.print();

	std::cout<<"Peek should not remove items from stack"<<std::endl;
	std::cout<<mystack.peek()<<std::endl;
	std::cout<<mystack.peek()<<std::endl;

	int result = 0;
	int* p_result = nullptr;

	std::cout<<"Pop should remove items from stack"<<std::endl;
	POP_PRINT
	POP_PRINT

	mystack.push(12345);

	POP_PRINT
	//POP_PRINT
	//POP_PRINT

	mystack.push(1);
	mystack.push(2);
	mystack.push(3);
	mystack.print();

	std::cout<<mystack.size<<std::endl;

	mystack.clear();

	if (mystack.is_empty()) {
		std::cout<< "Empty stack after clear()"<<std::endl;
	} else {
		std::cerr<< "Should not happen! Stack not empty after clear()"<<std::endl;
	}


	//POP_PRINT

	Queue<int> myqueue;
	myqueue.enqueue(123);
	myqueue.enqueue(456);
	myqueue.enqueue(789);

	std::cout<<myqueue.dequeue()<<std::endl;
	std::cout<<myqueue.dequeue()<<std::endl;
	std::cout<<myqueue.dequeue()<<std::endl;

	return 0;
}
}


