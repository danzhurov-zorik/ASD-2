#include "Hash.h"
#include <time.h>
#include <random>

int main1() {
	int* array = new int[50];
	std::random_device rd;
	std::mt19937 gen(rd());
	srand(time(0));
	for (int i = 0; i < 50; i++) {
		array[i] = rd() % 100;
	}
	int p = 7, h;
	
	Hash H(array, 50, p);
	std::cout << "Hash table:\n";
	H.Print();

	int x, y;
	std::cout << "Enter a number x (which is present in the array): ";
	std::cin >> x;
	std::cout << "Enter a number y (which is not present in the array): ";
	std::cin >> y;

	h = x % p;
	if (H.Find(x) != -1) {
		H.Del(x);
		std::cout << "Element " << x << " was found. Remove from Hash table\n";
	}
	else {
		H.Add(x);
		std::cout << "Element " << x << " was not found. Add to Hash table\n";
	}

	h = y % p;
	if (H.Find(y) != -1) {
		H.Del(y);
		std::cout << "Element " << y << " was found. Remove from Hash table\n";
	}
	else {
		H.Add(y);
		std::cout << "Element " << y << " was not found. Add to Hash table\n";
	}

	std::cout << "Hash table:\n";
	H.Print();

	return 0;
}