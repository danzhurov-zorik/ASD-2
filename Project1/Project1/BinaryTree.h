#pragma once

#include <vector>


class BinaryTree
{
public:
	class TreeNode {
	public:
		TreeNode();
		TreeNode(int key = 0, TreeNode* leftChild = nullptr, TreeNode* rightChild = nullptr);
		~TreeNode() = default;

		int key() const;
		void setKey(const int key);

		TreeNode* leftChild() const;
		TreeNode* rightChild() const;

		void setLeftChild(TreeNode* leftChild);
		void setRightChild(TreeNode* rightChild);

	private:
		int m_key = 0;
		TreeNode* m_leftChild = nullptr;
		TreeNode* m_rightChild = nullptr;
	};

	BinaryTree() = default;
	BinaryTree(TreeNode* root);

private: 
	TreeNode* m_root = nullptr;
};