#pragma once
#include <iostream>

class Usel {
private:
	int key;
	int next;
public:
	Usel(int k = -1, int N = -1) { key = k, next = N; };
	friend class Hash;
};

class Hash {
private:
	int dim;
	int p;
	Usel* TAB;

public:
	Hash();
	Hash(int a[], int n, int P); 
	~Hash();
	Hash(const Hash& other);
	Hash& operator=(const Hash& other);

	void Add(int k);    
	int Find(int k) const;
	void Del(int k);      
	void Print() const;
};

Hash::Hash() : dim(2), p(2) {
    TAB = new Usel[dim];
}

Hash::Hash(int a[], int n, int P) : dim(n + 5), p(P) {
    TAB = new Usel[dim];
    for (int i = 0; i < n; i++) {
        Add(a[i]);
    }
}

Hash::~Hash() {
    delete[] TAB;
}

Hash::Hash(const Hash& other) : dim(other.dim), p(other.p) {
    TAB = new Usel[dim];
    for (int i = 0; i < dim; i++) {
        TAB[i] = other.TAB[i];
    }
}

Hash& Hash::operator=(const Hash& other) {
    if (this != &other) {
        delete[] TAB;
        dim = other.dim;
        p = other.p;
        TAB = new Usel[dim];
        for (int i = 0; i < dim; i++) {
            TAB[i] = other.TAB[i];
        }
    }
    return *this;
}

void Hash::Add(int k) {
    if (Find(k) != -1) return; 

    int h = k % p;
    if (TAB[h].key == -1) {
        TAB[h].key = k;
        TAB[h].next = -1;
    }
    else {
        int j = dim - 1;
        while (j >= 0 && TAB[j].key != -1) {
            j--;
        }

        if (j < 0) {
            std::cerr << "Error!\n";
            return;
        }

        TAB[j].key = k;
        TAB[j].next = -1;

        int t = h;
        while (TAB[t].next != -1) {
            t = TAB[t].next;
        }
        TAB[t].next = j;
    }
}

int Hash::Find(int k) const {
    int h = k % p;
    if (TAB[h].key == -1) return -1;

    int t = h;
    while (t != -1) {
        if (TAB[t].key == k) {
            return t;
        }
        t = TAB[t].next;
    }
    return -1;
}

void Hash::Del(int k) {
    int h = k % p;
    if (TAB[h].key == -1) return;

    int t = h;
    int prev = -1;

    while (t != -1) {
        if (TAB[t].key == k) {
            if (prev == -1) {
                if (TAB[t].next != -1) {
                    int nxt = TAB[t].next;
                    std::swap(TAB[t].key, TAB[nxt].key);
                    std::swap(TAB[t].next, TAB[nxt].next);
                    TAB[nxt].key = -1;
                    TAB[nxt].next = -1;
                }
                else {
                    TAB[t].key = -1;
                    TAB[t].next = -1;
                }
            }
            else {
                TAB[prev].next = TAB[t].next;
                TAB[t].key = -1;
                TAB[t].next = -1;
            }
            return;
        }
        prev = t;
        t = TAB[t].next;
    }
}

void Hash::Print() const {
    for (int i = 0; i < dim; i++) {
        std::cout << "TAB[" << i << "]: ";
        if (TAB[i].key == -1) {
            std::cout << "пусто";
        }
        else {
            int t = i;
            while (t != -1) {
                std::cout << TAB[t].key;
                if (TAB[t].next != -1) {
                    std::cout << " (next: " << TAB[t].next << ") -> ";
                }
                else {
                    std::cout << " (next: -1)";
                }
                t = TAB[t].next;
            }
        }
        std::cout << "\n";
    }
}