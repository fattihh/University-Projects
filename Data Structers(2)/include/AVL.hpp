#ifndef AVL_HPP
#define AVL_HPP

#include "Node.hpp"
#include "Stack.hpp"

class AVL{
	private:	
		Node* root;
		Stack* postorderYapraklar;
		int ascii;

		Node* SearchAndAdd(Node*,const int&);
		Node* SwapWithLeftChild(Node*);
		Node* SwapWithRightChild(Node*);
		bool DeleteNode(Node*&);
		void inorder(Node*);
		void preorder(Node*);
		void postorder(Node*);
		void postorderYaprak(Node*);
		void asciiDegeriOlustur(Node*);
		int Height(Node*);
		void PrintLevel(Node*,int);
		bool Search(Node*,const int&);

	public:
		AVL();
		bool isEmpty()const;
		void Add(const int&);
		void inorder();
		void preorder();
		void postorder();
		void levelorder();
		int Height();
		bool Search(const int&);
		void Clear();
		void stackleriOlustur();
		Stack* getPostorderYaprak();
		int getascii();
		~AVL();
};

#endif