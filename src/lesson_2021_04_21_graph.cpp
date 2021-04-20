/*
 * lesson_2021_04_21_graph.cpp
 *
 *  Created on: Apr 20, 2021
 *      Author: KZ
 */
#include <iostream>
#include <cassert>


namespace lesson_2021_04_21_graph {

struct AdjacentMatrixGraph {
	int ** matrix;
	std::size_t size;

	AdjacentMatrixGraph(std::size_t size) {
		this->size = size;
		this->matrix = new int*[size];
		for (std::size_t i = 0; i<size; i++) {
			this->matrix[i] = new int[size];
			for(std::size_t j = 0; j<size; j++) {
				this->matrix[i][j] = 0;
			}
		}
	}
	~AdjacentMatrixGraph() {
		for (std::size_t i = 0; i<size; i++) {
			delete [] this->matrix[i];
		}
		delete [] this->matrix;
	}

	void add_edge(std::size_t start_vertex, std::size_t end_vertex) {
		assert(start_vertex < size);
		assert(end_vertex < size);
		this->matrix[start_vertex][end_vertex] = 1;
	}

	void remove_edge(std::size_t start_vertex, std::size_t end_vertex) {
		assert(start_vertex < size);
		assert(end_vertex < size);
		this->matrix[start_vertex][end_vertex] = 0;
	}
	void print_matrix() {
		for(std::size_t i = 0; i < size; i++) {
			for(std::size_t j = 0; j < size; j++) {
				std::cout<< matrix[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
	}

	void print_edges() {
		for(std::size_t i = 0; i < size; i++) {
			bool has_edges = false;
			for(std::size_t j = 0; j < size; j++) {
				if (matrix[i][j]) {
					std::cout<<i<<"->"<<j<<", ";
					has_edges = true;
				}
			}
			if (has_edges) {
				std::cout<<std::endl;
			}
		}
	}
};



int main() {

	AdjacentMatrixGraph graph1(4);
	graph1.add_edge(0,1);
	graph1.add_edge(2,3);
	graph1.add_edge(2,0);

	graph1.print_matrix();
	graph1.print_edges();

	std::cout<<"remove edge 2->3"<<std::endl;
	graph1.remove_edge(2,3);
	graph1.print_matrix();




	return 0;
}
}



