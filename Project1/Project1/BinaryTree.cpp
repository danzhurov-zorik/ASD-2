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