#include "HuffmanTree.h"

int main() {
	HuffmanTree HT;


	const std::string fileName = "textFile.txt";
	const std::string encodedFileName = "encodedTextFile.txt";
	const std::string decodedFileName = "decodedTextFile.txt";

	HT.build(fileName);


	std::cout << HT.encode(fileName, encodedFileName);

	puts("");

	HT.decode(encodedFileName, decodedFileName);

	HT.print();
	return 0;
}