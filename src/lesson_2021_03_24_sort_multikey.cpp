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
	int z;
};

bool compare_x_y(const Point& first, const Point& second) {
	if (first.x != second.x) {
		return first.x < second.x;
	} else { return first.y < second.y; }
}

typedef bool (*comparator)(const Point&, const Point&);
typedef bool (*comparator_extended)(const Point&, const Point&, comparator next);

bool compare_multi_x(const Point& first, const Point& second, comparator next_compare) {
	if (first.x != second.x) {
		return first.x < second.x;
	} else { return next_compare(first, second); }
}

bool compare_multi_y(const Point& first, const Point& second, comparator next_compare) {
	if (first.y != second.y) {
		return first.y < second.y;
	} else { return next_compare(first, second); }
}

bool compare_multi_z(const Point& first, const Point& second, comparator next_compare) {
	if (first.z != second.z) {
		return first.z < second.z;
	} else { return next_compare(first, second); }
}

bool compare_x(const Point& first, const Point& second) {
	return first.x < second.x;
}

bool compare_y(const Point& first, const Point& second) {
	return first.y < second.y;
}

bool compare_z(const Point& first, const Point& second) {
	return first.z < second.z;
}

//comparator combine(comparator_extended start, comparator next) {
//	return [start, next](const Point& first, const Point& second) {
//		return start(first, second, next);
//	};
//
//}


struct Comparator{
	Comparator* next_comparator;
	Comparator(Comparator* next_comparator = nullptr) {
		this->next_comparator = next_comparator;
	}
	virtual bool less(const Point& first, const Point& second)=0;
	virtual bool equals(const Point& first, const Point& second)=0;
	bool operator()(const Point& first, const Point& second) {
		if (!equals(first, second)) {
			return less(first, second);
		} else if (next_comparator) {
			return (*next_comparator)(first, second);
		} else { return false; }
	}
};

struct ComparatorX: public Comparator {
	ComparatorX(Comparator* next = nullptr): Comparator(next) {}
	bool less(const Point& first, const Point& second) override {
		return first.x < second.x;
	}
	bool equals(const Point& first, const Point& second) override {
		return first.x == second.x;
	}
};

struct ComparatorY: public Comparator {
	ComparatorY(Comparator* next = nullptr): Comparator(next) {}
	bool less(const Point& first, const Point& second) override {
		return first.y < second.y;
	}
	bool equals(const Point& first, const Point& second) override {
		return first.y == second.y;
	}
};

struct ComparatorZ: public Comparator {
	ComparatorZ(Comparator* next = nullptr): Comparator(next) {}
	bool less(const Point& first, const Point& second) override {
		return first.z < second.z;
	}
	bool equals(const Point& first, const Point& second) override {
		return first.z == second.z;
	}
};

void sort_x_y(Point* arr, std::size_t size) {
	//std::sort(arr, arr+size, compare_x_y);
//	std::sort(arr, arr+size, [](const Point& first, const Point& second) {
//		return compare_multi_x(first, second, compare_y);
//	});
	//std::sort(arr, arr+size, combine(compare_multi_x, compare_y));
	Comparator* comparator = new ComparatorX(new ComparatorY);
	std::sort(arr, arr + size,
			[comparator](const Point& first, const Point& second) {
				return (*comparator)(first, second);
			});

}

void sort_x_y_z(Point* arr, std::size_t size) {
	//std::sort(arr, arr+size, compare_x_y);
//	std::sort(arr, arr+size, [](const Point& first, const Point& second) {
//		return compare_multi_x(first, second, [](const Point& first, const Point& second) {
//			return compare_multi_y(first, second, compare_z);
//		});
//	});

	Comparator* comparator = new ComparatorX(new ComparatorY(new ComparatorZ));
	std::sort(arr, arr + size,
			[comparator](const Point& first, const Point& second) {
				return (*comparator)(first, second);
			});

}


int main() {


	Point arr[5] { {1, 2, 1}, {5, 7, 3}, {1, 3, 9}, {9, 1, 5}, {5, 7, 1}};
	sort_x_y_z(arr, 5);
	for(std::size_t i = 0; i<5; i++) {
		std::cout<<arr[i].x<<" "<<arr[i].y<<" "<<arr[i].z<<std::endl;
	}
	return 0;
}

}


