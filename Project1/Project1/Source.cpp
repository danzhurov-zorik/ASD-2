#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

bool isFileContainsSortedArray(const std::string& fileName)
{
	int valueNow = 0, valuePrev = 0;
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file." << std::endl;
		return 1;
	}

	file >> valuePrev;
	while (file >> valueNow)
	{
		if (valueNow < valuePrev)
		{
			return false;
		}
		valuePrev = valueNow;
	}
	file.close();
	return true;
}

bool isEndFile(const std::string& fileBI)
{
	std::ifstream fileB(fileBI);
	int ch;
	if (!(fileB >> ch))
	{
		fileB.close();
		return true;
	}
	fileB.close();
	return false;
}

void splitting(const std::string& filename, const std::string& fileSplit1, const std::string& fileSplit2)
{
	std::ofstream fileSplit[2];
	fileSplit[0].open(fileSplit1);
	fileSplit[1].open(fileSplit2);
	std::ifstream file(filename);

	int n = 0, x, i;
	file >> x;
	while (file.good())
	{
		i = 0;
		while (file.good() && i < 1)
		{
			fileSplit[n] << x << " ";
			file >> x;
			i++;
		}
		n = 1 - n;
	}
	file.close();
	fileSplit[0].close();
	fileSplit[1].close();
}

void fileMerges(const int p, const std::string& inputFile1, const std::string& inputFile2, const std::string& outputFile1, const std::string& outputFile2)
{

	std::ifstream inputFile[2];
	std::ofstream outputFile[2];

	inputFile[0].open(inputFile1);
	inputFile[1].open(inputFile2);
	outputFile[0].open(outputFile1);
	outputFile[1].open(outputFile2);

	int mas[2];

	inputFile[0] >> mas[0];
	inputFile[1] >> mas[1];
	int n = 0;
	while (inputFile[0].good() && inputFile[1].good())
	{
		int i = 0, j = 0;
		while (inputFile[0].good() && inputFile[1].good() && i < p && j < p)
		{
			if (mas[0] < mas[1])
			{
				outputFile[n] << mas[0] << " ";
				inputFile[0] >> mas[0];
				i++;
			}
			else
			{
				outputFile[n] << mas[1] << " ";
				inputFile[1] >> mas[1];
				j++;
			}
		}
		while (inputFile[0].good() && i < p)
		{
			outputFile[n] << mas[0] << " ";
			inputFile[0] >> mas[0];
			i++;
		}
		while (inputFile[1].good() && j < p)
		{
			outputFile[n] << mas[1] << " ";
			inputFile[1] >> mas[1];
			j++;
		}
		n = 1 - n;
	}
	while (inputFile[0].good())
	{
		outputFile[n] << mas[0] << " ";
		inputFile[0] >> mas[0];
	}
	while (inputFile[1].good())
	{
		outputFile[n] << mas[1] << " ";
		inputFile[1] >> mas[1];
	}

	inputFile[0].close();
	inputFile[1].close();
	outputFile[0].close();
	outputFile[1].close();
}

bool fileSort(const std::string& filename)
{
	const std::string file_0 = "file_0";
	const std::string file_1 = "file_1";
	const std::string file_2 = "file_2";
	const std::string file_3 = "file_3";

	splitting(filename, file_0, file_1);

	int p = 1;

	while (!isEndFile(file_1))
	{
		fileMerges(p, file_0, file_1, file_2, file_3);

		p *= 2;

		fileMerges(p, file_2, file_3, file_0, file_1);

		p *= 2;
	}

	if (isFileContainsSortedArray(file_0))
		return true;
	return false;

}

void splittingWithSegments(const std::string& filename, const std::string& fileSplit1, const std::string& fileSplit2) {
	std::ofstream fileSplit[2];
	fileSplit[0].open(fileSplit1);
	fileSplit[1].open(fileSplit2);
	std::ifstream file(filename);

	int n = 0, i, prev, now;
	file >> prev;
	fileSplit[0] << prev << " ";
	while (file >> now) {
		
		if (now < prev) {
			n = 1 - n;
		}
		fileSplit[n] << now << " ";
		prev = now;
	}
	file.close();
	fileSplit[0].close();
	fileSplit[1].close();
}

void fileMergesWithSegments(const std::string& inputFile1, const std::string& inputFile2,
    const std::string& outputFile1, const std::string& outputFile2)
{
    std::ifstream S[2];
    S[0].open(inputFile1);
    S[1].open(inputFile2);
    std::ofstream F[2];
    F[0].open(outputFile1);
    F[1].open(outputFile2);

    int x[2];                    
    bool has[2];                 

    for (int i = 0; i < 2; ++i) {
        if (S[i] >> x[i])
            has[i] = true;
        else
            has[i] = false;
    }

    int n = 0;

    while (has[0] || has[1]) {
        bool active[2] = { has[0], has[1] };

        while (active[0] && active[1])
        {
            int m = (x[0] <= x[1]) ? 0 : 1;
            F[n] << x[m] << " ";

            int next;
            if (S[m] >> next) {
                if (next >= x[m]) {
                    x[m] = next;
                }
                else {
                    x[m] = next;
                    active[m] = false;
                }
            }
            else {
                has[m] = false;
                active[m] = false;
            }
        }

        for (int i = 0; i < 2; ++i) {
            if (active[i]) {
                F[n] << x[i] << " ";
                int next;
                while (S[i] >> next) {
                    if (next >= x[i]) {
                        x[i] = next;
                        F[n] << x[i] << " ";
                    }
                    else {
                        x[i] = next;
                        break;
                    }
                }
                if (S[i].eof()) {
                    has[i] = false;
                }
            }
        }

        n = 1 - n;
    }

    S[0].close();
    S[1].close();
    F[0].close();
    F[1].close();
}

bool fileSortWithSegments(const std::string& filename) {
	const std::string file_0 = "file_0";
	const std::string file_1 = "file_1";
	const std::string file_2 = "file_2";
	const std::string file_3 = "file_3";

	splittingWithSegments(filename, file_0, file_1);

	while (!isEndFile(file_1)) {
		fileMergesWithSegments(file_0, file_1, file_2, file_3);
		fileMergesWithSegments(file_2, file_3, file_0, file_1);
	}

	if (isFileContainsSortedArray(file_0))
		return true;
	return false;
}
void main()
{	
	clock_t start, stop;
	double time, timeSort = 0;
	for (int border = 10; border <= 100000; border *= 100)
		for (int size = 100000; size <= 100000; size *= 10)
		{
			std::string filename = "random_array_" + std::to_string(size) + "_" + std::to_string(border) + ".txt";
			start = clock();
			if (fileSort(filename))
				std::cout << "File sorted\n";
			else
				std::cout << "File is not sorting\n";
			stop = clock();
			time = (double)(stop - start) / CLOCKS_PER_SEC;
			timeSort += time;
		}
	std::cout << "sort time: " << timeSort<<"\n";
	timeSort = 0;

	for (int border = 10; border <= 100000; border *= 100)
		for (int size = 100000; size <= 100000; size *= 10)
		{
			std::string filename = "random_array_" + std::to_string(size) + "_" + std::to_string(border) + ".txt";
			start = clock();
			if (fileSortWithSegments(filename))
				std::cout << "File sorted\n";
			else
				std::cout << "File is not sorting\n";
			stop = clock();
			time = (double)(stop - start) / CLOCKS_PER_SEC;
			timeSort += time;
		}
	std::cout << "sort time: " << timeSort << "\n";
}
