#pragma once

#include "BoolVector.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


class HuffmanTree
{
	class Node
	{
	public:
		Node();
		~Node() = default;

		std::string stringifySymbols() const;

		int frequency() const;
		void setFrequency(int frequency);

		const BoolVector& symbols() const;
		void setSymbols(const BoolVector& symbols);

		Node* leftChild() const;
		Node* rightChild() const;

		void setLeftChild(Node* leftChild);
		void setRightChild(Node* rightChild);



	private:
		int m_frequency = 1;

		BoolVector m_symbols = BoolVector(256, 0);

		Node* m_leftChild = nullptr;
		Node* m_rightChild = nullptr;
	};
public:
	HuffmanTree() = default;
	~HuffmanTree();

	void clear();

	void print();

	void build(const std::string& textFilename);

	double encode(const std::string& textFilename, const std::string& encodedTextFilename);

	bool decode(const std::string& encodedTextFilename, const std::string& decodedTextFilename);

private:

	std::string encode(Node* node, const char symbol);

	char decode(Node* node, std::ifstream& encodedTextFilename);

	void clear(Node* node);

	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
private:
	Node* m_root = nullptr;


};