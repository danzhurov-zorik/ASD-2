#include "Hash.h"

#include <string>

int main()
{
    HashTable<std::string> HT(new QuadraticHash(), 10000);

    srand(0);
    for (int i = 0; i < 100000; i++)
    {
        if (i % 10000 == 0)
        {
            std::cout << i << "\n";
        }
        int index = rand() % 1000;
        std::string str = "Greka ehal cherez reku" + std::to_string(index);
        HT.insert(i, str);
    }

    HT.removeKey(23);

    std::cout << HT[23];
}