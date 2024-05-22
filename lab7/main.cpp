#include <iostream>
#include "BSTree.h"
#include <vector>
template <class T>
void print_node(Node<T>* node)
{
	std::cout << "Адрес узла: " << node << std::endl;
	if (node) std::cout << "Значение: " << node->value << std::endl;
	else std::cout << "Узел не найден!" << std::endl;;
}

int main(int argc, char** argv)
{
	std::setlocale(0, "");
	BSTree<int> tree = BSTree<int>();
	std::vector<int> keys = {};
	for (int i = 0; i < 10; i++)
	{
		keys.push_back(rand() % 10);
	}
	for (auto k : keys) tree.insert(tree.get_root(), k);
	std::cout << "Обход дерева: " << std::endl;
	tree.straight(tree.get_root());
	std::cout << "\nПечать дерева: " << std::endl;

	tree.print_tree(tree.get_root(), 3);

	auto found = tree.find(tree.get_root(), keys[0]);
	auto not_found = tree.find(tree.get_root(), 999);
	std::cout << std::endl;
	print_node<int>(found);
	print_node<int>(not_found);

	std::cout << "\nУдаляем элемент " << keys[0] << " из дерева: " << std::endl;
	tree.remove(tree.get_root(), keys[0]);
	tree.print_tree(tree.get_root(), 3);

	return 0;
}