#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(TreeNode* node)
{
	setRoot(node);
}


BinarySearchTree::TreeNode* buildRootForOptimalTree(std::vector<std::vector<int>>& matrixKeyNumbers, std::vector<int>& keys, int i, int j)
{
	int k;

	if (i >= j)
		return nullptr;
	else
		k = matrixKeyNumbers[i][j];

	BinarySearchTree::TreeNode* node = new BinarySearchTree::TreeNode(keys[k - 1]);

	node->setLeftChild(buildRootForOptimalTree(matrixKeyNumbers, keys, i, k - 1));
	node->setRightChild(buildRootForOptimalTree(matrixKeyNumbers, keys, k, j));

	return node;
}

BinarySearchTree BinarySearchTree::buildOptimalTree(std::vector<int>& keys, std::vector<int>& nodeFrequencies, std::vector<int>& trapFrequencies)
{


	std::vector<std::vector<int>> matrixWeight(keys.size() + 1, std::vector<int>(keys.size() + 1, 0));
	std::vector<std::vector<int>> matrixCost = matrixWeight;
	std::vector<std::vector<int>> matrixKeyNumbers = matrixWeight;

	for (int i = 0; i < matrixWeight.size(); i++)
	{
		matrixWeight[i][i] = trapFrequencies[i];
		matrixCost[i][i] = trapFrequencies[i];
	}

	for (int i = 0; i < matrixWeight.size() - 1; i++)
	{
		matrixWeight[i][i + 1] = matrixWeight[i][i] + nodeFrequencies[i] + trapFrequencies[i + 1];
		matrixCost[i][i + 1] = matrixWeight[i][i + 1] + matrixCost[i][i] + matrixCost[i + 1][i + 1];
		matrixKeyNumbers[i][i + 1] = i + 1;
	}

	if (keys.size() >= 2)
	{
		for (int h = 2; h < keys.size() + 1; h++)
		{
			for (int i = 0; i < keys.size() - h + 1; i++)
			{
				int j = i + h;
				matrixWeight[i][j] = matrixWeight[i][j - 1] + nodeFrequencies[j - 1] + trapFrequencies[j];


				int minValueIndex = 0, minValue = INT_MAX;
				for (int k = i + 1; k < j + 1; k++)
				{
					if (minValue > (matrixCost[i][k - 1] + matrixCost[k][j]))
					{
						minValue = matrixCost[i][k - 1] + matrixCost[k][j];
						minValueIndex = k;
					}
				}

				matrixCost[i][j] = matrixWeight[i][j] + matrixCost[i][minValueIndex - 1] + matrixCost[minValueIndex][j];

				matrixKeyNumbers[i][j] = minValueIndex;
			}
		}
	}

	BinarySearchTree BST;
	BST.setRoot(buildRootForOptimalTree(matrixKeyNumbers, keys, 0, keys.size()));


	return BST;
}

BinarySearchTree::TreeNode* BinarySearchTree::findKey(int key) const
{
	return findKey(root(), key);
}

BinarySearchTree::TreeNode* BinarySearchTree::addKey(TreeNode* root, int key)
{
	if (!root) {
		root = new TreeNode(key);
	}
	else if (key < root->key()) {
		root->setLeftChild(addKey(root->leftChild(), key));
	}
	else if (key > root->key()) {
		root->setRightChild(addKey(root->rightChild(), key));
	}
	return root;
}

bool BinarySearchTree::removeKey(TreeNode* root, int key)
{
	TreeNode* node = findKey(key);
	TreeNode* nodeParent = searchParent(root, node);
	if (node == nullptr)
		return false;

	if (node->leftChild() == nullptr && node->rightChild() == nullptr)
	{
		if (nodeParent != nullptr)
		{
			if (nodeParent->leftChild() == node)
				nodeParent->setLeftChild(nullptr);
			else
				nodeParent->setRightChild(nullptr);
			delete node;
			node = nullptr;
		}
		else
		{
			delete node;
			setRoot(nullptr);
		}
	}
	else if ((node->leftChild() != nullptr && node->rightChild() == nullptr) || (node->leftChild() == nullptr && node->rightChild() != nullptr))
	{
		if (nodeParent != nullptr)
		{
			if (nodeParent->leftChild() == node)
			{
				if (node->leftChild() != nullptr)
					nodeParent->setLeftChild(node->leftChild());
				else
					nodeParent->setLeftChild(node->rightChild());
				delete node;
			}
			else
			{
				if (node->leftChild() != nullptr)
					nodeParent->setRightChild(node->leftChild());
				else
					nodeParent->setRightChild(node->rightChild());
				delete node;
			}
		}
		else
		{
			if (node->leftChild() != nullptr)
				setRoot(node->leftChild());
			else
				setRoot(node->rightChild());
			delete node;
		}
	}
	else
	{
		TreeNode* replacementNode, * replacementNodeParent;
		replacementNode = node->rightChild();
		replacementNodeParent = node;

		while (replacementNode->leftChild() != nullptr)
		{
			replacementNodeParent = replacementNode;
			replacementNode = replacementNode->leftChild();
		}

		if (replacementNodeParent != node)
		{
			replacementNodeParent->setLeftChild(replacementNode->rightChild());
			replacementNode->setRightChild(node->rightChild());
		}
		replacementNode->setLeftChild(node->leftChild());

		if (nodeParent != nullptr)
		{
			if (nodeParent->rightChild() == node)
			{
				nodeParent->setRightChild(replacementNode);
			}
			else
			{
				nodeParent->setLeftChild(replacementNode);
			}
		}
		else
		{
			setRoot(replacementNode);
		}
		delete node;

	}
	return true;
}

BinarySearchTree::TreeNode* BinarySearchTree::findKey(TreeNode* root, int key) const
{
	if (root == nullptr)
		return nullptr;

	if (root->key() == key)
		return root;

	if (key < root->key())
		findKey(root->leftChild(), key);
	else
		findKey(root->rightChild(), key);
}

int BinarySearchTree::minKey(TreeNode* root) const
{
	if (root == nullptr)
		return INT_MAX;

	TreeNode* nodeMin = root;

	while (nodeMin->leftChild() != nullptr)
	{
		nodeMin = nodeMin->leftChild();
	}
	return nodeMin->key();
}

int BinarySearchTree::maxKey(TreeNode* root) const
{
	if (root == nullptr)
		return INT_MIN;

	TreeNode* nodeMax = root;

	while (nodeMax->rightChild() != nullptr)
	{
		nodeMax = nodeMax->rightChild();
	}

	return nodeMax->key();
}

int BinarySearchTree::nodeHeightIndex(TreeNode* node, int key, int level) const
{
	if (node == nullptr)
		return -1;
	if (key < node->key())
		level = nodeHeightIndex(node->leftChild(), key, level + 1);
	else if (key > node->key())
		level = nodeHeightIndex(node->rightChild(), key, level + 1);

	return level;
}

std::vector<int> BinarySearchTree::getVectorKeys(TreeNode* root, std::vector<int>& keys) const
{
	if (!root) {
		return keys;
	}
	getVectorKeys(root->leftChild(), keys);
	keys.push_back(root->key());
	getVectorKeys(root->rightChild(), keys);

	return keys;
}