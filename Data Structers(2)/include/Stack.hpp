#ifndef STACK_HPP
#define STACK_HPP

#include"StackNode.hpp"

class Stack {
private:
	StackNode* topOfStack;

public:
	Stack();
	bool isEmpty()const;
	void push(const int& item);
	void pop();
	void print();
	const int& top()const;
	void makeEmpty();
	~Stack();

};

#endif