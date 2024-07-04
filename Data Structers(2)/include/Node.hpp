#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <cmath>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	int height;

	Node(const int& vr, Node* sl = NULL, Node* sg = NULL) {
		data = vr;
		left = sl;
		right = sg;
		height = 0;
	}
};

#endif