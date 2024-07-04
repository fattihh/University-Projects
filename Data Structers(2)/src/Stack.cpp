/**
* @file Stack.cpp
* @description Stack veri yapýsý
* @course Veri Yapilari Grup 2A
* @assignment 2.Ödev
* @date 16.12.2023
* @author Fatih Uçar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include"Stack.hpp"

Stack::Stack() {
	topOfStack = NULL;
}
bool Stack::isEmpty()const {
	return topOfStack == NULL;
}
void Stack::push(const int& item) {
	topOfStack = new StackNode(item, topOfStack);
}
void Stack::pop() {
	if (isEmpty()) throw "Stack is Empty";
	StackNode* tmp = topOfStack;
	topOfStack = topOfStack->next;
	delete tmp;
}
void Stack::print()
{
	StackNode* iter = topOfStack;
	cout << "STACK" << endl;
	while (iter != NULL) { cout << iter->item << endl; iter = iter->next; }
}
const int& Stack::top()const {
	if (isEmpty()) throw "Stack is Empty";
	return topOfStack->item;
}
void Stack::makeEmpty() {
	while (!isEmpty()) pop();
}
Stack::~Stack() {
	makeEmpty();
}