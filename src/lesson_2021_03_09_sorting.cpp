/*
 * lesson_2021_03_09_sorting.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: KZ
 */

#include <iostream>
#include <cmath>

namespace lesson_2021_03_09_sorting {

std::size_t get_bucket_size(std::size_t size) {
	return std::ceil(std::sqrt(size));
}


void quadratic_select_sort(int* arr, std::size_t size) {
	std::size_t bucket_size = std::sqrt(size);
}


int main(){
	std::cout<<get_bucket_size(24)<<std::endl;
	std::cout<<get_bucket_size(25)<<std::endl;
	return 0;
}
}

