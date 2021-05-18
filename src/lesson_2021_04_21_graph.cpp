/*
 * lesson_2021_04_21_graph.cpp
 *
 *  Created on: Apr 20, 2021
 *      Author: KZ
 */

#include "queue.h"
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
					std::cout<<i<<"->"<<j<<" ";
					has_edges = true;
				}
			}
			if (has_edges) {
				std::cout<<std::endl;
			}
		}
	}
};

bool get_bit(unsigned bit_vector, std::size_t index) {
	return (bit_vector >> index) & 1;
}
void set_bit(unsigned& bit_vector, std::size_t index, bool value) {
	unsigned mask = 1 << index;
	if (value) {
		bit_vector |= mask;
	} else {
		mask = ~mask;
		bit_vector &= mask;
	}
}

struct BitVectorGraph {
	unsigned * matrix_rows;
	std::size_t size;
	BitVectorGraph(std::size_t size) {
		assert(size <= sizeof(unsigned));

		this->size = size;
		this->matrix_rows = new unsigned[size];
		for (std::size_t i = 0; i<size; i++) {
			this->matrix_rows[i] = 0;
		}
	}
	~BitVectorGraph() {
		delete [] this->matrix_rows;
	}
	void add_edge(std::size_t start_vertex, std::size_t end_vertex) {
		assert(start_vertex < size);
		assert(end_vertex < size);
		//this->matrix[start_vertex][end_vertex] = 1;
		set_bit(this->matrix_rows[start_vertex], end_vertex, 1);
	}
	void remove_edge(std::size_t start_vertex, std::size_t end_vertex) {
		assert(start_vertex < size);
		assert(end_vertex < size);
		//this->matrix[start_vertex][end_vertex] = 0;
		set_bit(this->matrix_rows[start_vertex], end_vertex, 0);
	}

	void print_matrix() {
		for(std::size_t i = 0; i < size; i++) {
			for(std::size_t j = 0; j < size; j++) {
				//std::cout<< matrix[i][j]<<" ";
				std::cout<< get_bit(this->matrix_rows[i],j)<<" ";
			}
			std::cout<<std::endl;
		}
	}

	void print_edges() {
		for(std::size_t i = 0; i < size; i++) {
			bool has_edges = false;
			for(std::size_t j = 0; j < size; j++) {
				//if (matrix[i][j]) {
				if (get_bit(this->matrix_rows[i],j)) {
					std::cout<<i<<"->"<<j<<" ";
					has_edges = true;
				}
			}
			if (has_edges) {
				std::cout<<std::endl;
			}
		}
	}



};


struct GraphNode {
	std::size_t end_vertex;
	GraphNode* next;
	GraphNode(std::size_t end_vertex, GraphNode* next = nullptr) {
		this->end_vertex = end_vertex;
		this->next = next;
	}
};

struct AdjacentStructureGraph {
	GraphNode **edges;
	std::size_t size;

	AdjacentStructureGraph(std::size_t size) {
		this->size = size;
		this->edges = new GraphNode*[size];
		for(std::size_t i = 0; i<size; i++) {
			this->edges[i] = nullptr;
		}
	}

	~AdjacentStructureGraph() {
		for(std::size_t i = 0; i<size; i++) {
			GraphNode* current = this->edges[i];
			while(current) {
				GraphNode* to_delete = current;
				current = current->next;
				delete to_delete;
			}
		}
		delete [] this->edges;
	}

	void add_edge(std::size_t start_vertex, std::size_t end_vertex) {
		GraphNode* current = this->edges[start_vertex];
		if (current) {
			if (current->end_vertex > end_vertex) {
				GraphNode* new_node = new GraphNode(end_vertex, current);
				this->edges[start_vertex] = new_node;
				return;
			}
		} else {
			GraphNode* new_node = new GraphNode(end_vertex);
			this->edges[start_vertex] = new_node;
			return;
		}
		while(current) {
			if (current->next == nullptr || end_vertex > current->next->end_vertex) {
				GraphNode* new_node = new GraphNode(end_vertex, current->next);
				current->next = new_node;
				return;
			}
			current = current->next;
		}
	}

	void remove_edge(std::size_t start_vertex, std::size_t end_vertex) {
		GraphNode* current = this->edges[start_vertex];
		GraphNode* previous = nullptr;
		while(current && current->end_vertex < end_vertex) {
			previous = current;
			current = current->next;
		}
		if (current && current->end_vertex == end_vertex) {
			if (previous) {
				previous->next = current->next;
			} else {
				this->edges[start_vertex] = current->next;
			}
			delete current;
		}
	}

	void print_matrix_inefficient() {
		for(std::size_t start_vertex = 0; start_vertex < size; start_vertex++){
			GraphNode* current = this->edges[start_vertex];
			std::size_t end_vertex = 0;
			if (current == nullptr) {
				for(end_vertex = 0; end_vertex<size; end_vertex++) {
					std::cout<<"0 ";
				}
			}
			while(current) {
				if (current->end_vertex == end_vertex) {
					std::cout<<"1 ";
					current = current->next;
				} else {
					std::cout<<"0 ";
				}
				end_vertex++;
				if (end_vertex >= size) { break;}
			}
			for (std::size_t j = end_vertex; j<size; j++) {
				std::cout<<"0 ";
			}
			std::cout<<std::endl;
		}
	}

	void print_matrix() {
		for(std::size_t start_vertex = 0; start_vertex < size; start_vertex++){
			GraphNode* current = this->edges[start_vertex];
			for(std::size_t end_vertex = 0; end_vertex < size; end_vertex++){
				if (current && current->end_vertex == end_vertex) {
					std::cout<<"1 ";
					current = current->next;
				} else {
					std::cout<<"0 ";
				}
			}
			std::cout<<std::endl;
		}
	}

	void print_edges() {
		for(std::size_t i = 0; i < size; i++){
			GraphNode* current = this->edges[i];
			if (current == nullptr) { continue;}
			while(current) {
				std::cout<<i<<"->"<<current->end_vertex<<" ";
				current = current->next;
			}
			std::cout<<std::endl;
		}
	}

	template<typename Callable>
	void breadth_first_all(Callable process) {
		bool* already_processed = new bool[size];
		for(std::size_t i = 0; i< size; i++) {
			already_processed[i] = false;
		}
		for(std::size_t start_vertex = 0; start_vertex<size; start_vertex++) {
			if (already_processed[start_vertex]) {continue;}
			breadth_first_impl(start_vertex, process, already_processed);
		}
		delete [] already_processed;
	}

	template<typename Callable>
	void breadth_first_single_component(std::size_t start_vertex, Callable process) {
		assert(start_vertex < size);
		bool* already_processed = new bool[size];
		for(std::size_t i = 0; i< size; i++) {
			already_processed[i] = false;
		}
		breadth_first_impl(start_vertex, process, already_processed);
		delete [] already_processed;
	}

	template<typename Callable>
	void depth_first_all(Callable process) {
		bool* already_processed = new bool[size];
		for(std::size_t i = 0; i< size; i++) {
			already_processed[i] = false;
		}
		for(std::size_t start_vertex = 0; start_vertex<size; start_vertex++) {
			if (already_processed[start_vertex]) {continue;}
			depth_first_impl(start_vertex, process, already_processed);
		}
		delete [] already_processed;
	}

	template<typename Callable>
	void depth_first_single_component(std::size_t start_vertex, Callable process) {
		assert(start_vertex < size);
		bool* already_processed = new bool[size];
		for(std::size_t i = 0; i< size; i++) {
			already_processed[i] = false;
		}
		depth_first_impl(start_vertex, process, already_processed);
		delete [] already_processed;
	}

private:
	template<typename Callable>
	void breadth_first_impl(std::size_t start_vertex, Callable process, bool* already_processed) {
		Queue<std::size_t> to_visit;
		to_visit.enqueue(start_vertex);
		already_processed[start_vertex] = true;
		while(! to_visit.is_empty() ) {
			std::size_t current_vertex = to_visit.dequeue();
			process(current_vertex);

			GraphNode* current = this->edges[current_vertex];
			while(current) {
				std::size_t end_vertex = current->end_vertex;
				current = current->next;
				if (already_processed[end_vertex]) {continue;}

				to_visit.enqueue(end_vertex);
				already_processed[end_vertex] = true;
			}
		}
	}

	template<typename Callable>
	void depth_first_impl(std::size_t start_vertex, Callable process, bool* already_processed) {
		process(start_vertex);
		already_processed[start_vertex] = true;

		GraphNode* current = this->edges[start_vertex];
		while(current) {
			std::size_t end_vertex = current->end_vertex;
			current = current->next;
			if (already_processed[end_vertex]) {continue;}
			depth_first_impl(end_vertex, process, already_processed);
		}
	}

};

void process_print(std::size_t vertex) {
	std::cout<<"Visited vertex "<<vertex<<std::endl;
}

int main() {

	std::cout<<"shift operations"<<std::endl;
	unsigned char bits = 0b1010;
	std::cout<<(unsigned)bits<<std::endl;
	std::cout<< 0b10100<<"="<< (bits << 1) <<std::endl;
	std::cout<< 0b1010000<<"="<< (bits << 3) <<std::endl;
	std::cout<< 0b10100000<<"="<< (bits << 4) <<std::endl;
	unsigned char shifted = bits << 5;
	std::cout<< 0b01000000<<"="<< (unsigned)shifted <<std::endl;

	std::cout<< 0b101<<"="<< (bits >> 1) <<std::endl;
	std::cout<< 0b10<<"="<< (bits >> 2) <<std::endl;
	std::cout<< 0b1<<"="<< (bits >> 3) <<std::endl;
	std::cout<< 0b0<<"="<< (bits >> 4) <<std::endl;

	std::cout<<"bit vector operations"<<std::endl;
	unsigned bit_vector = 0;
	std::cout<<get_bit(bit_vector, 3)<<std::endl;
	set_bit(bit_vector, 3, true);
	std::cout<<get_bit(bit_vector, 3)<<std::endl;
	set_bit(bit_vector, 3, false);
	std::cout<<get_bit(bit_vector, 3)<<std::endl;



	std::cout<<"Matrix:"<<std::endl;
	AdjacentMatrixGraph graph1(4);
	graph1.add_edge(0,1);
	graph1.add_edge(2,3);
	graph1.add_edge(2,0);

	graph1.print_matrix();
	graph1.print_edges();

	std::cout<<"remove edge 2->3"<<std::endl;
	graph1.remove_edge(2,3);
	graph1.print_matrix();
	graph1.print_edges();

	std::cout<<"Adjacent structure (linked list of connected vertices):"<<std::endl;
	AdjacentStructureGraph graph2(4);
	graph2.add_edge(0,1);
	graph2.add_edge(2,3);
	graph2.add_edge(2,0);

	graph2.print_matrix();
	graph2.print_edges();

	std::cout<<"BFS all"<<std::endl;
	graph2.breadth_first_all(process_print);
	std::cout<<"BFS starting from 2"<<std::endl;
	graph2.breadth_first_single_component(2,process_print);

	std::cout<<"DFS all"<<std::endl;
	graph2.depth_first_all(process_print);
	std::cout<<"DFS starting from 2"<<std::endl;
	graph2.depth_first_single_component(2,process_print);

	std::cout<<"remove edge 2->3"<<std::endl;
	graph2.remove_edge(2,3);

	graph2.print_matrix();
	graph2.print_edges();



	std::cout<<"Bit Vector:"<<std::endl;
	BitVectorGraph graph3(4);
	graph3.add_edge(0,1);
	graph3.add_edge(2,3);
	graph3.add_edge(2,0);

	graph3.print_matrix();
	graph3.print_edges();

	std::cout<<"remove edge 2->3"<<std::endl;
	graph3.remove_edge(2,3);
	graph3.print_matrix();
	graph3.print_edges();

	return 0;
}
}



