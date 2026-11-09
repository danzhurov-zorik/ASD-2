#include "HuffmanTree.h"

#include "iostream"



HuffmanTree::Node::Node()
{
}

std::string HuffmanTree::Node::stringifySymbols() const
{
    std::string str;
    for (int i = 0; i < symbols().length(); ++i)
    {
        if (symbols().bitValue(i))
        {
            str += char(i);
        }
    }
    return str;
}


int HuffmanTree::Node::frequency() const
{
    return m_frequency;
}

void HuffmanTree::Node::setFrequency(int frequency)
{
    m_frequency = frequency;
}

const BoolVector& HuffmanTree::Node::symbols() const
{
    return m_symbols;
}

void HuffmanTree::Node::setSymbols(const BoolVector& symbols)
{
    m_symbols = symbols;
}

HuffmanTree::Node* HuffmanTree::Node::leftChild() const
{
    return m_leftChild;
}

HuffmanTree::Node* HuffmanTree::Node::rightChild() const
{
    return m_rightChild;
}

void HuffmanTree::Node::setLeftChild(Node* leftChild)
{
    m_leftChild = leftChild;
}

void HuffmanTree::Node::setRightChild(Node* rightChild)
{
    m_rightChild = rightChild;
}



HuffmanTree::~HuffmanTree()
{
    clear();
}

void HuffmanTree::clear()
{
    clear(m_root);
    m_root = nullptr;
}

void HuffmanTree::print()
{
    printHorizontal(m_root, 0, 15);
}

void HuffmanTree::build(const std::string& textFilename)
{
    if (m_root)
    {
        clear();
    }
    std::ifstream textFile;
    textFile.open(textFilename);

    char symbol;

    if (!textFile.is_open() || !(textFile >> symbol))
        return;

    BoolVector BV(256, 0);
    std::vector<Node*> nodes;


    while (textFile.good())
    {
        std::vector<Node*>::iterator it = std::find_if(
            nodes.begin(),
            nodes.end(),
            [&symbol](Node* node) // Безымянная функция
            {
                return node->symbols().bitValue(symbol);
            }
        );

        if (it == nodes.end())
        {
            nodes.push_back(new Node());

            BoolVector BV = nodes.back()->symbols();

            BV[symbol] = true;

            nodes.back()->setSymbols(BV);
        }
        else
        {
            Node* node = *it;
            node->setFrequency(node->frequency() + 1);
        }

        textFile >> symbol;
    }

    // Ещё одна безымянная функция, сложили в переменную
    auto sorter = [](Node* a, Node* b) -> bool
        {
            return a->frequency() < b->frequency();
        };
    std::sort(nodes.begin(), nodes.end(), sorter);

    while (nodes.size() > 1)
    {
        Node* root = new Node();
        root->setFrequency(nodes[0]->frequency() + nodes[1]->frequency());

        BoolVector BV = root->symbols();

        for (int i = 0; i < root->symbols().length(); ++i)
        {
            BV[i] = nodes[0]->symbols().bitValue(i) || nodes[1]->symbols().bitValue(i);
        }

        root->setSymbols(BV);

        root->setLeftChild(nodes[0]);
        root->setRightChild(nodes[1]);

        nodes.erase(nodes.begin(), nodes.begin() + 2);
        nodes.push_back(root);
        std::sort(nodes.begin(), nodes.end(), sorter);
    }

    m_root = nodes.front();
}

bool isEndFile(const std::string& fileBI)
{
    std::ifstream fileB(fileBI);
    char ch;
    if (!(fileB >> ch))
    {
        fileB.close();
        return true;
    }
    fileB.close();
    return false;
}

double HuffmanTree::encode(const std::string& textFilename, const std::string& encodedTextFilename)
{
    std::ifstream textFile;
    std::ofstream encodedTextFile;

    std::string encodedText;

    int encodedTextSize = 0;
    char symbol;

    if (m_root == nullptr)
    {
        build(textFilename);
    }

    textFile.open(textFilename);
    encodedTextFile.open(encodedTextFilename);

    if (!m_root || !textFile.is_open() || !encodedTextFile.is_open())
    {
        textFile.close();
        encodedTextFile.close();
        return -1;
    }

    textFile >> symbol;
    if (!m_root->leftChild() && !m_root->rightChild())
    {
        while (textFile.good())
        {
            encodedTextFile << '0';

            textFile >> symbol;
        }
        encodedTextSize = m_root->frequency();
    }
    else
    {
        while (textFile.good())
        {
            for (int i = 0; i < encode(m_root, symbol).size(); i++)
            {
                encodedTextFile << encode(m_root, symbol)[i];
                encodedTextSize++;
            }
            textFile >> symbol;
        }
    }


    double compresСoef = encodedTextSize / (m_root->frequency() * 8.);

    for (int i = 0; i < encodedText.size(); i++)
    {
        encodedTextFile << encodedText[i];
    }

    textFile.close();
    encodedTextFile.close();

    return compresСoef;
}

bool HuffmanTree::decode(const std::string& encodedTextFilename, const std::string& decodedTextFilename)
{

    std::ifstream encodedTextFile;
    std::ofstream decodedTextFile;

    encodedTextFile.open(encodedTextFilename);
    decodedTextFile.open(decodedTextFilename);

    if (!encodedTextFile.is_open() || !decodedTextFile.is_open())
    {
        return false;
    }

    decodedTextFile << decode(m_root, encodedTextFile);

    while (encodedTextFile.good())
    {
        decodedTextFile << decode(m_root, encodedTextFile);
    }

    encodedTextFile.close();
    decodedTextFile.close();

    return true;
}

std::string HuffmanTree::encode(Node* node, const char symbol)
{
    std::string str;

    if (node->leftChild() == nullptr && node->rightChild() == nullptr)
    {
        return str;
    }
    else if (node->leftChild()->symbols().bitValue(symbol))
    {
        str += '0';
        str += encode(node->leftChild(), symbol);
    }
    else
    {
        str += '1';
        str += encode(node->rightChild(), symbol);
    }

    return str;
}

char HuffmanTree::decode(Node* node, std::ifstream& encodedTextFile)
{
    char symbol, letter;
    if (!encodedTextFile.good())
    {
        return ' ';
    }
    if (node->leftChild() == nullptr && node->rightChild() == nullptr)
    {
        return node->stringifySymbols()[0];
    }

    encodedTextFile >> symbol;

    if (symbol == '0')
    {
        letter = decode(node->leftChild(), encodedTextFile);
    }
    else
    {
        letter = decode(node->rightChild(), encodedTextFile);
    }

    return letter;
}

void HuffmanTree::clear(Node* node)
{
    if (node == nullptr)
        return;

    clear(node->leftChild());
    clear(node->rightChild());

    delete node;
    node = nullptr;
}



void HuffmanTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
    if (root == nullptr) {
        return;
    }
    printHorizontal(root->rightChild(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ');
    std::cout << root->frequency() << ' ' << root->stringifySymbols();
    std::cout << std::endl;
    printHorizontal(root->leftChild(), marginLeft + levelSpacing, levelSpacing);
}