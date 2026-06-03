#include "BinaryTree.h"
#include <iostream>
#include <list>
#include <algorithm>

BinaryTree::TreeNode::TreeNode() {}

BinaryTree::TreeNode::TreeNode(int key, TreeNode* leftChild, TreeNode* rightChild)
	:m_key(key), m_leftChild(leftChild), m_rightChild(rightChild){}

int BinaryTree::TreeNode::key() const{
	return m_key;
}

void BinaryTree::TreeNode::setKey(const int key){
	m_key = key;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::leftChild() const{
	return m_leftChild;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::rightChild() const{

	return m_rightChild;
}

void BinaryTree::TreeNode::setLeftChild(TreeNode* leftChild){
	m_leftChild = leftChild;
}

void BinaryTree::TreeNode::setRightChild(TreeNode* rightChild){
	m_rightChild = rightChild;
}

BinaryTree::BinaryTree(TreeNode* root)
	:m_root(root){}

BinaryTree::BinaryTree(const BinaryTree& other){
	m_root = copyTree(other.root());
}

BinaryTree::BinaryTree(BinaryTree&& other){
	m_root = other.root();
	other.setRoot(nullptr);
}

BinaryTree::~BinaryTree(){
	clear(m_root);
}

BinaryTree::TreeNode* BinaryTree::root() const{
	return m_root;
}

void BinaryTree::clear(){
	clear(m_root);
	m_root = nullptr;
}

void BinaryTree::removeSubtrees(){
	removeSubtrees(m_root);
}

bool BinaryTree::isEmpty() const{
	return (m_root == nullptr);
}

int BinaryTree::height() const{
	return height(m_root);
}

int BinaryTree::nodeHeightIndex(int key) const{
	return nodeHeightIndex(m_root, key, 0);
}

int BinaryTree::indexNode(int key) const{
	return indexNode(m_root, key);
}

int BinaryTree::countNodes() const{
	return countNodes(m_root);
}

int BinaryTree::maxKey() const{
	return maxKey(m_root);
}

int BinaryTree::minKey() const{
	return minKey(m_root);
}

BinaryTree::TreeNode* BinaryTree::addKey(int key){
	return addKey(m_root, key);
}

BinaryTree::TreeNode* BinaryTree::findKey(int key) const{
	return findKey(m_root, key);
}

bool BinaryTree::removeKey(int key){
	return removeKey(m_root, key);
}

bool BinaryTree::contains(int key) const{
	return contains(m_root, key);
}

std::vector<int> BinaryTree::getVectorKeys() const{
	std::vector<int> keys;
	getVectorKeys(m_root, keys);
	return keys;
}

void BinaryTree::levelPrint() const{
	levelPrint(m_root);
}

void BinaryTree::printTreeHorizontal(int marginLeft, int levelSpacing) const{
	printHorizontal(m_root, marginLeft, levelSpacing);
}

bool BinaryTree::isBalanced() const{
	return isBalanced(m_root);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other){
	clear();

	m_root = copyTree(other.root());
	return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& other){
	clear();

	m_root = other.root();
	other.setRoot(nullptr);

	return *this;
}

void BinaryTree::setRoot(TreeNode* root){
	m_root = root;
}

BinaryTree::TreeNode* BinaryTree::copyTree(TreeNode* root){
	if (root == nullptr)
		return nullptr;

	TreeNode* newNode = new TreeNode(0, nullptr, nullptr);
	newNode->setKey(root->key());

	newNode->setLeftChild(copyTree(root->leftChild()));
	newNode->setRightChild(copyTree(root->rightChild()));

	return newNode;
}

void BinaryTree::clear(TreeNode* TreeNode){
	if (TreeNode == nullptr)
		return;

	clear(TreeNode->leftChild());
	clear(TreeNode->rightChild());

	delete TreeNode;
	TreeNode = nullptr;
}

void BinaryTree::removeSubtrees(TreeNode* TreeNode){
	clear(TreeNode->leftChild());
	clear(TreeNode->rightChild());
	TreeNode->setLeftChild(nullptr);
	TreeNode->setRightChild(nullptr);
}

int BinaryTree::height(TreeNode* root) const{
	if (root == nullptr)
		return 0;

	int left = height(root->leftChild());
	int right = height(root->rightChild());

	return 1 + std::max(left, right);
}

int BinaryTree::nodeHeightIndex(TreeNode* root, int key, int level) const{
	if (root == nullptr)
		return -1;

	if (root->key() == key)
		return level;

	int left = nodeHeightIndex(root->leftChild(), key, level + 1);
	if (left != -1)
		return left;

	int right = nodeHeightIndex(root->rightChild(), key, level + 1);
	if (right != -1)
		return right;
}

int BinaryTree::indexNode(TreeNode* root, int key) const{
	if (root == nullptr)
		return -1;

	std::list<TreeNode*> unprocessedNodes(1, root);
	int index = 0, level = 0;
	while (!unprocessedNodes.empty()) {
		level = unprocessedNodes.size();

		while (level != 0)
		{
			TreeNode* TreeNode = unprocessedNodes.front();
			unprocessedNodes.pop_front();

			if (TreeNode->leftChild())
				unprocessedNodes.push_back(TreeNode->leftChild());
			if (TreeNode->rightChild())
				unprocessedNodes.push_back(TreeNode->rightChild());

			if (TreeNode->key() == key)
				return index;

			level--;
			index++;
		}
	}
	return -1;
}

int BinaryTree::countNodes(TreeNode* TreeNode) const{
	if (TreeNode == nullptr)
		return 0;

	return (1 + countNodes(TreeNode->leftChild()) + countNodes(TreeNode->rightChild()));
}

int BinaryTree::maxKey(TreeNode* TreeNode) const{
	if (TreeNode == nullptr)
		return INT_MIN;

	int maxLeft = maxKey(TreeNode->leftChild());
	int maxRight = maxKey(TreeNode->rightChild());

	return std::max(TreeNode->key(), std::max(maxLeft, maxRight));

}

int BinaryTree::minKey(TreeNode* TreeNode) const{
	if (TreeNode == nullptr)
		return INT_MAX;

	int minLeft = minKey(TreeNode->leftChild());
	int minRight = minKey(TreeNode->rightChild());

	return std::min(TreeNode->key(), std::min(minLeft, minRight));
}

BinaryTree::TreeNode* BinaryTree::addKey(TreeNode* root, int key){
	if (!root)
	{
		root = new TreeNode(key);
		if (m_root == nullptr)
		{
			m_root = root;
			return root;
		}
	}
	else if (rand() % 2) {
		root->setLeftChild(addKey(root->leftChild(), key));
	}
	else {
		root->setRightChild(addKey(root->rightChild(), key));
	}
	return root;
}

BinaryTree::TreeNode* BinaryTree::findKey(TreeNode* root, int key) const{
	if (!root || root->key() == key) {
		return root;
	}
	TreeNode* subTreeSearchResult = findKey(root->leftChild(), key);
	if (!subTreeSearchResult) {
		subTreeSearchResult = findKey(root->rightChild(), key);
	}
	return subTreeSearchResult;
}

bool BinaryTree::removeKey(TreeNode* root, int key){
	TreeNode* Node = findKey(key);
	TreeNode* nodeParent = searchParent(root, Node);

	if (Node == nullptr)
		return false;

	if (Node->leftChild() == nullptr && Node->rightChild() == nullptr)
	{
		if (nodeParent != nullptr)
		{
			if (nodeParent->leftChild() == Node)
				nodeParent->setLeftChild(nullptr);
			else
				nodeParent->setRightChild(nullptr);
			delete Node;
			Node = nullptr;
		}
		else
		{
			delete Node;
			m_root = nullptr;
		}
	}
	else if ((Node->leftChild() != nullptr && Node->rightChild() == nullptr) || (Node->leftChild() == nullptr && Node->rightChild() != nullptr))
	{
		if (nodeParent != nullptr)
		{
			if (nodeParent->leftChild() == Node)
			{
				if (Node->leftChild() != nullptr)
					nodeParent->setLeftChild(Node->leftChild());
				else
					nodeParent->setLeftChild(Node->rightChild());
			}
			else
			{
				if (Node->leftChild() != nullptr)
					nodeParent->setRightChild(Node->leftChild());
				else
					nodeParent->setRightChild(Node->rightChild());
			}
			delete Node;
		}
		else
		{
			if (Node->leftChild() != nullptr)
				m_root = Node->leftChild();
			else
				m_root = Node->rightChild();
			delete Node;
		}
	}
	else
	{
		TreeNode* replacementNode, * replacementNodeParent;
		replacementNodeParent = Node;
		replacementNode = Node;

		while (replacementNode->rightChild() != nullptr)
		{
			replacementNodeParent = replacementNode;
			replacementNode = replacementNode->rightChild();
		}
		if (nodeParent != nullptr)
		{
			if (Node == replacementNodeParent)
			{
				replacementNode->setRightChild(replacementNode->leftChild());
				replacementNode->setLeftChild(Node->leftChild());
			}
			else
			{
				replacementNodeParent->setRightChild(replacementNode->leftChild());
				replacementNode->setLeftChild(Node->leftChild());
				replacementNode->setRightChild(Node->rightChild());

			}
			if (nodeParent->rightChild() == Node)
				nodeParent->setRightChild(replacementNode);
			else
				nodeParent->setLeftChild(replacementNode);
			delete Node;
		}
		else
		{
			if (Node != replacementNodeParent)
			{
				replacementNodeParent->setRightChild(replacementNode->leftChild());
			}
			replacementNode->setLeftChild(Node->leftChild());
			replacementNode->setRightChild(Node->rightChild());

			m_root = replacementNode;
			delete Node;
		}
	}
	return true;
}

BinaryTree::TreeNode* BinaryTree::searchParent(TreeNode* root, TreeNode* Node) const{
	if (root == nullptr)
		return nullptr;
	if (root->rightChild() == Node || root->leftChild() == Node)
		return root;
	TreeNode* subTreeSearchParentResult = searchParent(root->leftChild(), Node);
	if (!subTreeSearchParentResult)
	{
		subTreeSearchParentResult = searchParent(root->rightChild(), Node);
	}
	return subTreeSearchParentResult;
}

bool BinaryTree::contains(TreeNode* root, int key) const{
	return findKey(key);
}

std::vector<int> BinaryTree::getVectorKeys(TreeNode* root, std::vector<int>& keys) const{

	if (root->leftChild())
		getVectorKeys(root->leftChild(), keys);

	if (root->rightChild())
		getVectorKeys(root->rightChild(), keys);

	keys.push_back(root->key());

	std::sort(keys.begin(), keys.end());

	return keys;
}

void BinaryTree::levelPrint(TreeNode* root) const{
	if (root == nullptr)
		return;
	std::list<TreeNode*> unprocessedNodes(1, root);

	while (!unprocessedNodes.empty()) {
		int level = unprocessedNodes.size();

		while (level != 0)
		{
			TreeNode* TreeNode = unprocessedNodes.front();
			unprocessedNodes.pop_front();

			std::cout << TreeNode->key() << " ";

			if (TreeNode->leftChild())
				unprocessedNodes.push_back(TreeNode->leftChild());
			if (TreeNode->rightChild())
				unprocessedNodes.push_back(TreeNode->rightChild());

			level--;
		}
		std::cout << "\n";
	}
}

void BinaryTree::printHorizontal(TreeNode* root, int marginLeft, int levelSpacing) const{
	if (root == nullptr)
	{
		return;
	}
	printHorizontal(root->rightChild(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft,
		' ') << root->key() << std::endl;
	printHorizontal(root->leftChild(), marginLeft + levelSpacing, levelSpacing);
}

bool BinaryTree::isBalanced(TreeNode* root) const{
	if (root == nullptr)
		return true;

	int leftHeight = height(root->leftChild());
	int rightHeight = height(root->rightChild());

	return std::abs(leftHeight - rightHeight) <= 1 && isBalanced(root->leftChild()) && isBalanced(root->rightChild());
}
