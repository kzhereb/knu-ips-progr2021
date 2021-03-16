/*
 * lesson_2021_03_09_sorting.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: KZ
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <chrono>
#include <cmath>
#include <climits>

namespace lesson_2021_03_09_sorting {

using namespace std::chrono;

class Time {
public:
	static int GetInSeconds() {
		auto currentTime = system_clock::now();
		return (int) system_clock::to_time_t(currentTime);
	}

	static std::string GetParsed() {
		auto currentTimeRaw = system_clock::now();
		auto currentTime = system_clock::to_time_t(currentTimeRaw);
		return ctime(&currentTime);
	}
};

class Timer {
private:
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
	Timer(std::string name) {
		this->name = name;
		this->start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Timer " << name << ": "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(
						end - start).count() << "ms" << std::endl;
	}
};

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
	for (std::size_t i = 0; i < size; i++) {
		if (arr[i] < current_min) {
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
	for (std::size_t i = 0; i < size; i++) {
		// find min out of mins
		current_min = INT_MAX;
		std::size_t min_bucket = 0;
		for (std::size_t j = 0; j < num_buckets; j++) {
			int current_value = arr[bucket_min_index[j]];
			if (current_value < current_min) {
				current_min = current_value;
				min_bucket = j;
			}
		}
		//move to output_arr, replace with some value
		output_arr[i] = current_min;
		arr[bucket_min_index[min_bucket]] = INT_MAX;

		//update min in bucket
		// 0: [0, bucket_size); 1:[bucket_size; 2*bucket_size); 2:[2*bucket_size; 3*bucket_size)

		std::size_t bucket_start = min_bucket * bucket_size;
		std::size_t bucket_end = (min_bucket + 1) * bucket_size;
		if (bucket_end > size) {
			bucket_end = size;
		}

		current_min = INT_MAX;
		for (std::size_t j = bucket_start; j < bucket_end; j++) {
			if (arr[j] < current_min) {
				current_min = arr[j];
				bucket_min_index[min_bucket] = j;
			}
		}
	}

	//copy output_arr to arr, delete output_arr
	for (std::size_t i = 0; i < size; i++) {
		arr[i] = output_arr[i];
	}
	delete[] output_arr;

//	for(std::size_t i=0; i<num_buckets; i++) {
//		std::cout<<bucket_min_index[i]<<" ";
//	} std::cout<<std::endl;

	delete[] bucket_min_index;
}

void selection_sort(int* arr, std::size_t size) {
	for (std::size_t i = 0; i < size; i++) {
		int min_value = arr[i];
		std::size_t min_index = i;
		for (std::size_t j = i + 1; j < size; j++) {
			if (arr[j] < min_value) {
				min_value = arr[j];
				min_index = j;
			}
		}
		if (min_index != i) {
			std::swap(arr[i], arr[min_index]);
		}
	}
}

void external_sort_merge_runs(std::string filename, std::size_t buffer_size =
		100) {
	std::ifstream infile(filename);

	std::fstream extra_files[4];
	for (std::size_t i = 0; i < 4; i++) {
		extra_files[i] = fstream(filename + std::to_string(i));
	}
	int * buffer = new int[buffer_size];
	std::size_t buffer_position = 0;
	std::size_t current_extra = 0;
	while (!infile.eof()) {
		int value;
		infile >> value;
		if (buffer_position == 0 || buffer[buffer_position - 1] <= value) {
			buffer[buffer_position] = value;
			buffer_position++;
			if (buffer_position >= buffer_size) {
				for (std::size_t i = 0; i < buffer_size; i++) {
					extra_files[current_extra] << buffer[i] << " ";
				}
				extra_files[current_extra] << std::endl;
				current_extra++;
				if (current_extra > 1) {
					current_extra = 0;
				}
				buffer_position = 0;
			} else {
				for (std::size_t i = 0; i < buffer_position; i++) {
					extra_files[current_extra] << buffer[i] << " ";
				}
				extra_files[current_extra] << std::endl;
				current_extra++;
				if (current_extra > 1) {
					current_extra = 0;
				}
				buffer_position = 0;
			}
		}
	}
}

int* generate_random_array(std::size_t size) {
	int* arr = new int[size];
	for (std::size_t i = 0; i < size; i++) {
		arr[i] = rand() % 20;
	}
	return arr;
}

int* generate_almost_sorted_array_equation(std::size_t size) {
	int* arr = new int[size];
	for (std::size_t i = 0; i < size; i++) {
		arr[i] = (i % 10 == 0) ? 5 : 2 * i + 1;
	}
	return arr;
}

int* generate_almost_sorted_array_swap(std::size_t size) {
	int* arr = generate_random_array(size);

	std::sort(arr, arr + size);

	std::size_t swap_count = 10;

	for (std::size_t i = 0; i < swap_count; i++) {
		std::size_t from = rand() % size;
		std::size_t to = rand() % size;
		std::swap(arr[from], arr[to]);
	}
	return arr;
}

int* copy_array_loop(int* arr, std::size_t size) {
	int* result = new int[size];
	for (std::size_t i = 0; i < size; i++) {
		result[i] = arr[i];
	}
	return result;
}

void print_array(int* arr, std::size_t size) {
	for (std::size_t i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	int* almost_sorted = generate_almost_sorted_array_swap(100);
	print_array(almost_sorted, 100);
	delete[] almost_sorted;

	for (std::size_t size = 4; size < 26; size++) {
		int * arr = generate_random_array(size);
		std::cout << "Random array of size " << size << std::endl;
		for (std::size_t i = 0; i < size; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;

		//quadratic_select_sort(arr,size);
		selection_sort(arr, size);
		std::cout << "Sorted array: " << std::endl;
		for (std::size_t i = 0; i < size; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
		delete[] arr;
	}

	int* arr = generate_random_array(20000);
	{
		Timer timer { "select_sort" };
		selection_sort(arr, 20000);
	}
	delete[] arr;

	for (std::size_t size = 10000; size <= 50000; size += 10000) {
		int* arr1 = generate_random_array(size);
		int* arr2 = copy_array_loop(arr1, size);
		{
			Timer timer("select_sort " + std::to_string(size));
			selection_sort(arr1, size);
		}
		{
			Timer timer("quadratic_select_sort " + std::to_string(size));
			quadratic_select_sort(arr2, size);
		}
		delete[] arr1;
		delete[] arr2;
	}

	return 0;
}
}

