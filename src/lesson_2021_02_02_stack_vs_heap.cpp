/*
 * lesson_2021_02_02_stack_vs_heap.cpp
 *
 *  Created on: Feb 2, 2021
 *      Author: KZ
 */
#include <iostream>

const std::size_t DATA_SIZE = 100000;

void print_array(int* data) {
	for (std::size_t i = 0; i < DATA_SIZE; i++) {
		std::cout << "data[" << i << "]=" << data[i] << std::endl;
	}
}

void process_array_on_stack() {
	int data[DATA_SIZE];
	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		data[i] = i*5+3;
	}

	print_array(data);
}


void process_array_on_heap() {
	int* data = new int[DATA_SIZE];
	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		data[i] = i*5+3;
	}

	print_array(data);
}

int main() {
	std::cout<<"stack:"<<std::endl;
	process_array_on_stack();
	std::cout<<"heap:"<<std::endl;
	process_array_on_heap();
	return 0;
}

