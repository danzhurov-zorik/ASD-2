#include "List.h"
#include <time.h>
#include <random>

int main() {
	int* array = new int[50];
	std::random_device rd;
	std::mt19937 gen(rd());
	srand(time(0));
	for (int i = 0; i < 50; i++) {
		array[i] = rd() % 100;
	}
	int p = 7, h;
	List<int> H[7];
	
	for (int i = 0; i < 50; i++) {
		h = array[i] % p;
		H[h].addToTail(array[i]);
	}
	std::cout << "Hash table:\n";
	for (int i = 0; i < p; i++) {
		std::cout << "H[" << i << "]: ";
		H[i].print();
		std::cout << std::endl;
	}

	int x, y;
	std::cout << "Enter a number x (which is present in the array): ";
	std::cin >> x;
	std::cout << "Enter a number y (which is not present in the array): ";
	std::cin >> y;

	h = x % p;
	if (H[h].searchElement(x) == nullptr) {
		H[h].addToTail(x);
		std::cout << "Element " << x << " was not found. Add to Hash table\n";
	}
	else {
		H[h].deleteElement(H[h].searchElement(x));
		std::cout << "Element " << x << " was found. Remove from Hash table\n";
	}

	h = y % p;
	if (H[h].searchElement(y) == nullptr) {
		H[h].addToTail(y);
		std::cout << "Element " << y << " was not found. Add to Hash table\n";
	}
	else {
		H[h].deleteElement(H[h].searchElement(y));
		std::cout << "Element " << y << " was found. Remove from Hash table\n";
	}

	std::cout << "Hash table:\n";
	for (int i = 0; i < p; i++) {
		std::cout << "H[" << i << "]: ";
		H[i].print();
		std::cout << std::endl;
	}

	return 0;
}