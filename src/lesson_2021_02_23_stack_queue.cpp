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


