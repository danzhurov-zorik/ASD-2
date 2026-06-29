#include "BinarySearchTree.h"
#include <ctime>
#include <iostream>

int main() {
	BinarySearchTree::TreeNode* load = new BinarySearchTree::TreeNode(10, nullptr, nullptr);

	BinarySearchTree BT(load);

	BT.addKey(22);
	BT.addKey(37);
	BT.addKey(42);
	BT.addKey(-6);
	BT.addKey(95);

	std::vector<int> keys, nodeFrequencies, trapFrequencies;

	keys = BT.getVectorKeys();
	srand(time(0));

	for (int i = 0; i < keys.size(); i++)
	{
		int value = rand() % 30;

		nodeFrequencies.push_back(value);
	}
	for (int i = 0; i < keys.size() + 1; i++)
	{
		int value = rand() % 100;

		trapFrequencies.push_back(value);
	}

	std::cout << "vector nodeFrequencies: ";
	for (int i = 0; i < nodeFrequencies.size(); i++)
	{
		std::cout << nodeFrequencies[i] << " ";
	}
	std::cout << "\nvector trapFrequencies: ";
	for (int i = 0; i < trapFrequencies.size(); i++)
	{
		std::cout << trapFrequencies[i] << " ";
	}
	std::cout << "\n\n\n\n\n";

	BT = BT.buildOptimalTree(keys, nodeFrequencies, trapFrequencies);

	BT.printTreeHorizontal(0, 15);

	return 0;
}

