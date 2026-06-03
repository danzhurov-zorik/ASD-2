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
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other);

	virtual ~BinaryTree();

	TreeNode* root() const;


	void clear();
	void removeSubtrees();

	bool isEmpty() const;

	int height() const;
	int nodeHeightIndex(int key) const;
	int indexNode(int key) const;

	int countNodes() const;

	int maxKey() const;
	int minKey() const;

	TreeNode* addKey(int key);
	TreeNode* findKey(int key) const;

	bool removeKey(int key);
	TreeNode* searchParent(TreeNode* root, TreeNode* TreeNode) const;

	bool contains(int key) const;
	std::vector<int> getVectorKeys() const;

	void levelPrint() const;
	void printTreeHorizontal(int marginLeft, int levelSpacing) const;

	bool isBalanced() const;

	BinaryTree& operator=(const BinaryTree& other);
	BinaryTree& operator=(BinaryTree&& other);

	void setRoot(TreeNode* root);

protected:
	virtual int nodeHeightIndex(TreeNode* root, int key, int level) const;

	virtual int maxKey(TreeNode* TreeNode) const;
	virtual int minKey(TreeNode* TreeNode) const;

	virtual TreeNode* addKey(TreeNode* root, int key);

	virtual bool removeKey(TreeNode* root, int key);

	virtual std::vector<int> getVectorKeys(TreeNode* root, std::vector<int>& keys) const;

	virtual TreeNode* findKey(TreeNode* root, int key) const;
private:
	TreeNode* m_root = nullptr;

private:
	TreeNode* copyTree(TreeNode* root);

	void clear(TreeNode* TreeNode);
	void removeSubtrees(TreeNode* TreeNode);

	int height(TreeNode* root) const;
	int indexNode(TreeNode* root, int key) const;

	int countNodes(TreeNode* TreeNode) const;





	bool contains(TreeNode* root, int key) const;

	void levelPrint(TreeNode* root) const;
	void printHorizontal(TreeNode* root, int marginLeft, int levelSpacing) const;

	bool isBalanced(TreeNode* root) const;
};