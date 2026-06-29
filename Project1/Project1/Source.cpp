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
	std::cout << "find key: " << BT.findKeyNonRec(2)->key()<< "\n";
	BinaryTree BTCopy(BT);
	BTCopy.removeKey(4);
	BTCopy.printTreeHorizontal(0, 10);
	std::cout << "height of BTCopy: " << BTCopy.height() << " height of key 9: " << BTCopy.nodeHeightIndex(9) << "\n";
	
	if (BTCopy.isBalanced()) 
		std::cout << "BTCopy is balanced\n";
	else 
		std::cout << "BTCopy is not balanced\n";

	BTCopy.removeSubtrees();
	BT = BTCopy;
	BT.printTreeHorizontal(0, 10);
	
}

