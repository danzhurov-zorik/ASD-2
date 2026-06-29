#pragma once
#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{public:
	BinarySearchTree() = default;
	BinarySearchTree(TreeNode* node);
	BinarySearchTree(const BinarySearchTree& other) = default;
	BinarySearchTree(BinarySearchTree&& other) = default;

	~BinarySearchTree() override = default;

	using BinaryTree::addKey;
	using BinaryTree::removeKey;
	using BinaryTree::minKey;
	using BinaryTree::maxKey;
	using BinaryTree::nodeHeightIndex;
	using BinaryTree::getVectorKeys;
	using BinaryTree::findKey;

	static BinarySearchTree buildOptimalTree(std::vector<int>& keys, std::vector<int>& frequenciesP, std::vector<int>& frequenciesQ);
	BinarySearchTree& operator=(const BinarySearchTree& other) = default;
	BinarySearchTree& operator=(BinarySearchTree&& other) = default;
	TreeNode* findKey(int key) const;

protected:
	TreeNode* addKey(TreeNode* root, int key) override;

	bool removeKey(TreeNode* root, int key) override;

	int minKey(TreeNode* root) const override;
	int maxKey(TreeNode* root) const override;

	int nodeHeightIndex(TreeNode* node, int key, int level) const override;

	std::vector<int> getVectorKeys(TreeNode* root, std::vector<int>& keys) const override;
	
	TreeNode* findKey(TreeNode* root, int key) const override; };

