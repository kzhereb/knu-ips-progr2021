/*
 * lesson_2021_02_02_stack_vs_heap.cpp
 *
 *  Created on: Feb 2, 2021
 *      Author: KZ
 */
#include <iostream>

const std::size_t DATA_SIZE = 10000000;

void print_array(int* data, std::size_t data_size) {
	std::size_t output_size = data_size < 10 ? data_size : 10;
	for (std::size_t i = 0; i < output_size; i++) {
		std::cout << "data[" << i << "]=" << data[i] << std::endl;
	}
}

void process_array_on_stack() {
	int data[DATA_SIZE];
	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		data[i] = i*5+3;
	}

	print_array(data, DATA_SIZE);
}


void process_array_on_heap() {
	int* data = new int[DATA_SIZE];
	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		data[i] = i*5+3;
	}

	print_array(data, DATA_SIZE);
}

// will result in compiler warning
//int* create_array_on_stack() {
//	int data[DATA_SIZE];
//	for (std::size_t i = 0; i<DATA_SIZE; i++) {
//		data[i] = i*5+3;
//	}
//
//	return data;
//}

int* create_array_on_heap() {
	int* data = new int[DATA_SIZE];
	for (std::size_t i = 0; i<DATA_SIZE; i++) {
		data[i] = i*5+3;
	}

	return data;
}

int main() {
	std::cout<<"stack:"<<std::endl;
	//ERROR: can't return address of local variable
	//int * result_data = create_array_on_stack();
	//print_array(result_data, DATA_SIZE);

	std::cout<<"heap:"<<std::endl;
//	int * result_data = create_array_on_heap();
//	print_array(result_data, DATA_SIZE);

	while(true) {
		process_array_on_heap();
	}
	return 0;
}

