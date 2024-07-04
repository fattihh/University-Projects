/**
* @file AVL.cpp
* @description AVL aðaci veri yapýsý kodlarý
* @course Veri Yapilari Grup 2A
* @assignment 2.Ödev
* @date 16-23.12.2023
* @author Fatih Uçar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include "AVL.hpp"

Node* AVL::SearchAndAdd(Node* subNode, const int& item) {
	if (subNode == NULL) subNode = new Node(item);
	else if (item < subNode->data) {
		subNode->left = SearchAndAdd(subNode->left, item);

		if (Height(subNode->left) == Height(subNode->right) + 2) {
			if (item < subNode->left->data)
				subNode = SwapWithLeftChild(subNode);
			else {
				subNode->left = SwapWithRightChild(subNode->left);
				subNode = SwapWithLeftChild(subNode);
			}
		}
	}
	else if (item > subNode->data) {
		subNode->right = SearchAndAdd(subNode->right, item);

		if (Height(subNode->right) == Height(subNode->left) + 2) {
			if (item > subNode->right->data)
				subNode = SwapWithRightChild(subNode);
			else {
				subNode->right = SwapWithLeftChild(subNode->right);
				subNode = SwapWithRightChild(subNode);
			}
		}
	}
	else;

	subNode->height = Height(subNode);
	return subNode;
}
Node* AVL::SwapWithLeftChild(Node* subNode) {
	Node* tmp = subNode->left;
	subNode->left = tmp->right;
	tmp->right = subNode;

	subNode->height = Height(subNode);
	tmp->height = 1 + max(Height(tmp->left), subNode->height);

	return tmp;
}
Node* AVL::SwapWithRightChild(Node* subNode) {
	Node* tmp = subNode->right;
	subNode->right = tmp->left;
	tmp->left = subNode;

	subNode->height = Height(subNode);
	tmp->height = 1 + max(Height(tmp->right), subNode->height);

	return tmp;
}
bool AVL::DeleteNode(Node*& subNode) {
	Node* delNode = subNode;

	if (subNode->right == NULL) subNode = subNode->left;
	else if (subNode->left == NULL) subNode = subNode->right;
	else {
		delNode = subNode->left;
		Node* parentNode = subNode;
		while (delNode->right != NULL) {
			parentNode = delNode;
			delNode = delNode->right;
		}
		subNode->data = delNode->data;
		if (parentNode == subNode) subNode->left = delNode->left;
		else parentNode->right = delNode->left;
	}
	delete delNode;
	return true;
}
void AVL::inorder(Node* subNode) {
	if (subNode != NULL) {
		inorder(subNode->left);
		cout << subNode->data << " ";
		inorder(subNode->right);
	}
}
void AVL::preorder(Node* subNode) {
	if (subNode != NULL) {
		cout << subNode->data << " ";
		preorder(subNode->left);
		preorder(subNode->right);
	}
}
void AVL::postorder(Node* subNode) {
	if (subNode != NULL) {
		postorder(subNode->left);
		postorder(subNode->right);
		cout << subNode->data << " ";
		
	}
}
void AVL::postorderYaprak(Node* subNode) {
	if (subNode != NULL) {
		postorderYaprak(subNode->left);
		postorderYaprak(subNode->right);
		if (subNode->height == 0) { postorderYapraklar->push(subNode->data); }
	}
}
void AVL::asciiDegeriOlustur(Node* subNode)
{
	if (subNode != NULL) {
		asciiDegeriOlustur(subNode->left);
		asciiDegeriOlustur(subNode->right);
		if (subNode->height != 0) { ascii += subNode->data; }
	}
}
int AVL::Height(Node* subNode) {
	if (subNode == NULL) return -1;
	return 1 + max(Height(subNode->left), Height(subNode->right));
}
void AVL::PrintLevel(Node* subNode, int level) {
	if (subNode == NULL) return;
	if (level == 0) cout << subNode->data << " ";
	else {
		PrintLevel(subNode->left, level - 1);
		PrintLevel(subNode->right, level - 1);
	}
}
bool AVL::Search(Node* subNode, const int& item) {
	if (subNode == NULL) return false;
	if (subNode->data == item) return true;
	if (item < subNode->data) return Search(subNode->left, item);
	else return Search(subNode->right, item);
}
AVL::AVL() {
	root = NULL;
	postorderYapraklar = NULL;
}
bool AVL::isEmpty()const {
	return root == NULL;
}
void AVL::Add(const int& item) {
	root = SearchAndAdd(root, item);
}
void AVL::inorder() {
	inorder(root);
}
void AVL::preorder() {
	preorder(root);
}
void AVL::postorder() {
	postorder(root);
	cout << endl;
}
Stack* AVL::getPostorderYaprak() 
{
	if (this->postorderYapraklar == NULL)
	{
		stackleriOlustur();
	}
	return postorderYapraklar;
}
void AVL::stackleriOlustur()
{
	if (this->postorderYapraklar != NULL)
	{
		delete this->postorderYapraklar;
		this->postorderYapraklar = NULL;
	}
	this->postorderYapraklar = new Stack();
	postorderYaprak(root);
}
void AVL::levelorder() {
	int h = Height();
	for (int level = 0; level <= h; level++) {
		PrintLevel(root, level);
	}
}
int AVL::Height() {
	return Height(root);
}
bool AVL::Search(const int& item) {
	return Search(root, item);
}
void AVL::Clear() {
	while (!isEmpty()) DeleteNode(root);
}
int AVL::getascii()
{
	ascii = 0;
	asciiDegeriOlustur(root);
	ascii = ascii % (90 - 65 + 1) + 65;

	return ascii;
}
AVL::~AVL() {
	Clear();
}