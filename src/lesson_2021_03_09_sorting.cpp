/*
 * lesson_2021_03_09_sorting.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: KZ
 */

#include <iostream>
#include <utility>

#include <cmath>
#include <climits>

namespace lesson_2021_03_09_sorting {

std::size_t get_bucket_size(std::size_t size) {
	return std::ceil(std::sqrt(size));
}

std::size_t get_num_buckets(std::size_t size) {
	return std::round(std::sqrt(size));
}


void quadratic_select_sort(int* arr, std::size_t size) {
	std::size_t bucket_size = get_bucket_size(size);
	std::size_t num_buckets = get_num_buckets(size);

	// calculate minimum in each bucket
	int* bucket_min_index = new int[num_buckets]; // stores index of min element in arr, the value can be obtained from array
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

	int* output_arr = new int[size];
	for(std::size_t i = 0; i < size; i++) {
		// find min out of mins
		current_min = INT_MAX;
		std::size_t min_bucket = 0;
		for (std::size_t j = 0; j< num_buckets; j++) {
			int current_value = arr[bucket_min_index[j]];
			if (current_value < current_min) {
				current_min = current_value;
				min_bucket = j;
			}
		}
		//move to output_arr, replace with some value
		output_arr[i] = current_min;
		arr[ bucket_min_index[min_bucket] ] = INT_MAX;

		//update min in bucket
		// 0: [0, bucket_size); 1:[bucket_size; 2*bucket_size); 2:[2*bucket_size; 3*bucket_size)


		std::size_t bucket_start = min_bucket * bucket_size;
		std::size_t bucket_end = (min_bucket+1) * bucket_size;
		if(bucket_end>size) { bucket_end = size;}

		current_min = INT_MAX;
		for (std::size_t j = bucket_start; j<bucket_end; j++) {
			if (arr[j] < current_min) {
				current_min = arr[j];
				bucket_min_index[min_bucket] = j;
			}
		}
	}





	//copy output_arr to arr, delete output_arr
	for(std::size_t i = 0; i < size; i++) {
		arr[i] = output_arr[i];
	}
	delete [] output_arr;

//	for(std::size_t i=0; i<num_buckets; i++) {
//		std::cout<<bucket_min_index[i]<<" ";
//	} std::cout<<std::endl;

	delete [] bucket_min_index;
}


void selection_sort(int* arr, std::size_t size) {
	for (std::size_t i = 0; i<size; i++) {
		int min_value = arr[i];
		std::size_t min_index = i;
		for (std::size_t j = i+1; j<size; j++) {
			if (arr[j]<min_value) {
				min_value = arr[j];
				min_index = j;
			}
		}
		if (min_index != i) {
			std::swap(arr[i], arr[min_index]);
		}
	}
}


int* generate_random_array(std::size_t size) {
	int* arr = new int[size];
	for(std::size_t i = 0; i< size; i++) {
		arr[i] = rand() % 20;
	}
	return arr;
}


int main(){
//	std::cout<<get_bucket_size(24)<<std::endl;
//	std::cout<<get_bucket_size(25)<<std::endl;

	//int arr[5] = {1, 2, 3, 4, 5};
	//int arr[5] = {5, 4, 3, 2, 1};

	for (std::size_t size = 4; size<26; size++) {
		int * arr = generate_random_array(size);
		std::cout<<"Random array of size "<<size<<std::endl;
		for(std::size_t i = 0; i<size; i++) {
			std::cout<<arr[i]<<" ";
		}
		std::cout<<std::endl;

		//quadratic_select_sort(arr,size);
		selection_sort(arr,size);
		std::cout<<"Sorted array: "<<std::endl;
		for(std::size_t i = 0; i<size; i++) {
			std::cout<<arr[i]<<" ";
		}
		std::cout<<std::endl;
	}



	return 0;
}
}

