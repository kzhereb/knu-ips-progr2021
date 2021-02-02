/*
 * lesson_2021_02_02_stack_vs_heap.cpp
 *
 *  Created on: Feb 2, 2021
 *      Author: KZ
 */
#include <iostream>

const std::size_t DATA_SIZE = 10000000;


void process_array_on_stack() {
	int data[DATA_SIZE];
	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		data[i] = i*5+3;
	}

	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		std::cout<<"data["<<i<<"]="<<data[i]<<std::endl;
	}
}


void process_array_on_heap() {
	int* data = new int[DATA_SIZE];
	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		data[i] = i*5+3;
	}

	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		std::cout<<"data["<<i<<"]="<<data[i]<<std::endl;
	}
}

int main() {
	process_array_on_heap();
	return 0;
}

