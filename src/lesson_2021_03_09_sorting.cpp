/*
 * lesson_2021_03_09_sorting.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: KZ
 */

#include <iostream>
#include <cmath>
#include <climits>

namespace lesson_2021_03_09_sorting {

std::size_t get_bucket_size(std::size_t size) {
	return std::ceil(std::sqrt(size));
}


void quadratic_select_sort(int* arr, std::size_t size) {
	std::size_t bucket_size = get_bucket_size(size);
	std::size_t num_buckets = bucket_size;

	// calculate minimum in each bucket
	int* bucket_min_index = new int[num_buckets];

	std::size_t current_bucket = 0;
	std::size_t index_in_bucket = 0;
	int current_min = INT_MAX;
	for(std::size_t i = 0; i < size; i++) {
		if (arr[i]<current_min) {
			current_min = arr[i];
			bucket_min_index[current_bucket] = i;
		}
		index_in_bucket++;
		if (index_in_bucket >= bucket_size) {
			index_in_bucket = 0;
			current_bucket++;
			current_min = INT_MAX;
		}
	}

	for(std::size_t i=0; i<num_buckets; i++) {
		std::cout<<bucket_min_index[i]<<" ";
	} std::cout<<std::endl;

	delete [] bucket_min_index;
}


int main(){
//	std::cout<<get_bucket_size(24)<<std::endl;
//	std::cout<<get_bucket_size(25)<<std::endl;

	int arr[5] = {1, 2, 3, 4, 5};
	//int arr[5] = {5, 4, 3, 2, 1};
	quadratic_select_sort(arr,5);

	return 0;
}
}

