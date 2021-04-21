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

	void print_matrix() {
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
};


int main() {
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

	std::cout<<"remove edge 2->3"<<std::endl;
	graph2.remove_edge(2,3);

	graph2.print_matrix();
	graph2.print_edges();

	return 0;
}
}



