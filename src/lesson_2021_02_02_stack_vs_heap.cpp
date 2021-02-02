/*
 * lesson_2021_02_02_stack_vs_heap.cpp
 *
 *  Created on: Feb 2, 2021
 *      Author: KZ
 */
#include <iostream>

void process_array_on_stack() {
	int data[5];
	for (std::size_t i = 0; i<5; i++) {
		data[i] = i*5+3;
	}

	for (std::size_t i = 0; i<5; i++) {
		std::cout<<"data["<<i<<"]="<<data[i]<<std::endl;
	}
}

int main() {
	process_array_on_stack();
	return 0;
}

