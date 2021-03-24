/*
 * lesson_2021_03_24_sort_multikey.cpp
 *
 *  Created on: Mar 24, 2021
 *      Author: KZ
 */

#include <iostream>
#include <algorithm>

namespace lesson_2021_03_24_sort_multikey {

struct Point {
	int x;
	int y;
};

bool compare_x_y(const Point& first, const Point& second) {
	if (first.x != second.x) {
		return first.x < second.x;
	} else { return first.y < second.y; }
}

void sort_x_y(Point* arr, std::size_t size) {
	std::sort(arr, arr+size, compare_x_y);

}

int main() {


	Point arr[5] { {1, 2}, {5, 7}, {1, 3}, {9, 1}, {5, 7}};
	sort_x_y(arr, 5);
	for(std::size_t i = 0; i<5; i++) {
		std::cout<<arr[i].x<<" "<<arr[i].y<<std::endl;
	}
	return 0;
}

}


