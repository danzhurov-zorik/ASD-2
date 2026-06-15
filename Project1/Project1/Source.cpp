#include "BinaryTree.h"
#include <iostream>

int main() {
	BinaryTree::TreeNode* root3 = new BinaryTree::TreeNode(2, nullptr, nullptr);
	BinaryTree::TreeNode* root4 = new BinaryTree::TreeNode(4, nullptr, nullptr);
	BinaryTree::TreeNode* root2 = new BinaryTree::TreeNode(1, root4, nullptr);
	BinaryTree::TreeNode* root = new BinaryTree::TreeNode(0, root2, root3);
	

	BinaryTree BT(root);
	BT.printTreeHorizontal(0, 10);
	BT.addKey(3);
	BT.addKey(-1);
	BT.addKey(9);
	BT.printTreeHorizontal(0, 10);
	std::cout << "max key: " << BT.maxKeyNonRec() << " min key: " << BT.minKeyNonRec() << "\n";
	std::cout << "find key: " << BT.findKey(2)->key();
	
}
//поиск не через рекурсию
