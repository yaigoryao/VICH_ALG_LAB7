#pragma once
#include <iostream>
#include <math.h>
template <class T>
struct Node
{
public:
	T value = {};
	Node* left = nullptr;
	Node* right = nullptr;
	int height = 1;
	Node(T _value = {}, Node* _left = nullptr, Node* _right = nullptr, int _height = 1) : value{ _value }, left { _left }, right{ _right }, height{ _height } {};
};

template <class T>
class BSTree
{
private:
	Node<T>* root = nullptr;
private:
	int get_height(Node<T>* node) const
	{
		return node ? node->height : 0;
	}

	int balance_factor(const Node<T>* node) const
	{
		return get_height(node->left) - get_height(node->right);
	}

	void fix_height(Node<T>* node)
	{
		int left = get_height(node->left);
		int right = get_height(node->right);
		node->height = (left > right ? left : right) + 1;
	}

	void rotate_left(Node<T>*& node)
	{
		Node<T>* tmp = node->right;
		node->right = tmp->left;
		tmp->left = node;
		fix_height(node);
		fix_height(tmp);
		node = tmp;
	}

	void rotate_right(Node<T>*& node)
	{
		Node<T>* tmp = node->left;
		node->left = tmp->right;
		tmp->right = node;
		fix_height(node);
		fix_height(tmp);
		node = tmp;
	}

	void balance(Node<T>*& node)
	{
		if (node)
		{
			fix_height(node);
			if (balance_factor(node) == -2)
			{
				if (balance_factor(node->right) > 0)
				{
					rotate_right(node->right);
				}
				rotate_left(node);
			}
			if (balance_factor(node) == 2)
			{
				if (balance_factor(node->left) < 0)
				{
					rotate_left(node->left);
				}
				rotate_right(node);
			}
		}
	}

	Node<T>* find_min(Node<T>* node)
	{
		return node->left ? find_min(node->left) : node;
	}

	Node<T>* remove_min(Node<T>* node)
	{
		if (!node->left)
		{
			return node->right;
		}
		node->left = remove_min(node->left);
		balance(node);
	}

	Node<T>* get_min_node(Node<T>* node)
	{
		if (node)
		{
			if (node->left)
			{
				return node->left;
			}
			else
			{
				return node;
			}
		}
		else return nullptr;
	}
public:
	BSTree() : root{ nullptr } {};

	~BSTree()
	{
		this->clear(this->root);
	}
	Node<T>*& get_root() { return this->root;  }
	void insert(Node<T>*& node, T value)
	{
		if (!node) node = new Node<T>(value, nullptr, nullptr);
		else
		{
			if (value >= node->value)
			{
				if (!node->right) node->right = new Node<T>(value, nullptr, nullptr);
				else insert(node->right, value);
			}
			else if (value < node->value)
			{
				if (!node->left) node->left = new Node<T>(value, nullptr, nullptr);
				else insert(node->left, value);
			}
			balance(node);
		}
		
	}

	void clear(Node<T>*& node)
	{
		if (node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
		/*if (!node) return;
		else if (!node->left && !node->right)
		{
			delete node;
			node = nullptr;
		}
		else
		{
			if (node->left) clear(node->left);
			if (node->right) clear(node->right);
		}*/
	}

	Node<T>* find(Node<T>* node, T value) const
	{
		if (!node) return nullptr;
		else
		{
			if (value > node->value)
			{
				find(node->right, value);
			}
			else if (value < node->value)
			{
				find(node->left, value);
			}
			else if (value == node->value)
			{
				return node;
			}
		}
	}

	void remove(Node<T>*& node, T value)
	{
		if (!node) return;
		else if (value < node->value)
		{
			remove(node->left, value);
		}
		else if (value > node->value)
		{
			remove(node->right, value);
		}
		else
		{
			if (!node->left && !node->right)
			{
				delete node;
				node = nullptr;
			}
			else if (!node->left && node->right)
			{
				Node<T>* temp = node->right;
				delete node;
				node = temp;
			}
			else if (node->left && !node->right)
			{
				Node<T>* temp = node->left;
				delete node;
				node = temp;
			}
			else
			{
				node->value = get_min_node(node->right)->value;
				remove(node->right, node->value);
			}
		}
		balance(node);
	}

	void print_tree(Node<T>* node, int spaces)
	{
		if(node)
		{
			print_tree(node->right, spaces + 3);
			std::cout << "\r";
			for (int i = 0; i < spaces + 1; i++) std::cout << ' ';
			std::cout << std::endl;
			for (int i = 0; i < spaces; i++) std::cout << ' ';
			std::cout << node->value << std::endl;
			for (int i = 0; i < spaces + 1; i++) std::cout << ' ';
			print_tree(node->left, spaces + 3);
		}
	}

	void straight(Node<T>* node) const
	{
		if (node)
		{
			std::cout << node->value << ' ';
			straight(node->left);
			straight(node->right);
		}
	}
};