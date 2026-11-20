#pragma once

#include <math.h>
#include <iostream>
#include <vector>
#include <utility>
#include "List.h"

class Hash {
public:
    virtual int hash(const int key, const int capacity) const = 0;
    virtual Hash* other() const = 0;
};

class QuadraticHash : public Hash {
public:
    int hash(const int  key, const int capacity) const override {
        int h0 = key % capacity;
        int hash = (h0 + 4) % capacity;
        return abs(hash);
    }
    Hash* other() const override
    {
        return new QuadraticHash();
    }
};

class MultiplicationHash : public Hash {
public:
    int hash(const int key, const int capacity) const override {
        int h0 = key % capacity;
        double a = -(1. - std::sqrt(5)) / 2.;

        int hash = int(h0 * a * capacity) % capacity;

        return abs(hash);
    }

    Hash* other() const override {
        return new MultiplicationHash();
    }
};

class ThirdHash : public Hash {
public:
    int hash(const int key, const int capacity) const override
    {
        int h0 = key % capacity;
        int hash = ((h0 + 1) * (1 + key % (capacity - 2))) % capacity;

        return abs(hash);
    }

    Hash* other() const override
    {
        return new ThirdHash();
    }
};

template <typename T>
class HashTable
{
public:
    HashTable() = default;
    HashTable(Hash* hashFunction, int capacity);
    HashTable(const HashTable& other);
    ~HashTable();

    void setCapacity(int capacity);
    int capacity() const;

    void setFunction(Hash* someFunction);
    Hash* hashFunction() const;

    void setValue(int key, T value);

    std::vector<List<std::pair<int, T>>> hashTable() const;

    void clear();

    bool contains(const int& key) const;
    int indexKey(const int& key) const;

    void insert(const int& key, const T& value);
    void removeKey(const int& key);

    void swap(HashTable& other);

    T& operator[](int const key);

    HashTable<T>& operator=(const HashTable<T>& other);

    friend std::ostream& operator<<(std::ostream& os, const HashTable<T>& other);

private:

    Hash* m_hashFunction = new QuadraticHash();

    std::vector<List<std::pair<int, T>>> m_hashTable;

    int m_capacity = 0;
};

template <typename T>
HashTable<T>::HashTable(Hash* hashFunction, int capacity)
    :m_hashFunction(hashFunction), m_capacity(capacity)
{
    for (int i = 0; i < m_capacity; i++)
    {
        List<std::pair<int, T>> list = List<std::pair<int, T>>();
        m_hashTable.push_back(list);
    }
}

template <typename T>
HashTable<T>::HashTable(const HashTable& other)
    :m_capacity(other.capacity()), m_hashTable(other.hashTable())
{
    m_hashFunction = other.hashFunction()->copy();
}

template <typename T>
HashTable<T>::~HashTable()
{
    delete m_hashFunction;
}

template <typename T>
void HashTable<T>::setCapacity(int capacity)
{
    HashTable<T> HTcopy(*this);

    m_hashTable.clear();

    for (int i = 0; i < capacity; i++)
    {
        List<std::pair<int, T>> list = List<std::pair<int, T>>();
        m_hashTable.push_back(list);
    }

    m_capacity = capacity;

    for (int i = 0; i < HTcopy.capacity(); i++)
    {
        for (int j = 0; j < HTcopy.hashTable()[i].size(); j++)
        {
            insert(HTcopy.hashTable()[i][j].first, HTcopy.hashTable()[i][j].second);
        }
    }
}

template <typename T>
int HashTable<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void HashTable<T>::setValue(int key, T value)
{
    int hash = m_hashFunction->hash(key, m_capacity);
    for (int i = 0; i < m_hashTable[hash].size(); i++)
    {
        if (m_hashTable[hash][i].first == key)
        {
            m_hashTable[hash][i].second = value;
            return;
        }

    }

}

template<typename T>
void HashTable<T>::setFunction(Hash* someFunction)
{
    HashTable<T> HTcopy(*this);

    for (int i = 0; i < m_hashTable.size(); i++)
    {
        m_hashTable[i].clear();
    }

    m_hashFunction = someFunction;

    for (int i = 0; i < HTcopy.capacity(); i++)
    {
        for (int j = 0; j < HTcopy.hashTable()[i].size(); j++)
        {
            insert(HTcopy.hashTable()[i][j].first, HTcopy.hashTable()[i][j].second);
        }
    }
}

template<typename T>
Hash* HashTable<T>::hashFunction() const
{
    return m_hashFunction;
}

template <typename T>
std::vector<List<std::pair<int, T>>> HashTable<T>::hashTable() const
{
    return m_hashTable;
}

template<typename T>
void HashTable<T>::clear()
{
    m_hashTable.clear();
}

template<typename T>
bool HashTable<T>::contains(const int& key) const
{
    int hash = m_hashFunction->hash(key, m_capacity);

    for (int i = 0; i < m_hashTable[hash].size(); i++)
    {
        if (m_hashTable[hash][i].first == key)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
int HashTable<T>::indexKey(const int& key) const
{
    int hash = m_hashFunction->hash(key, m_capacity);

    for (int i = 0; i < m_hashTable[hash].size(); i++)
    {
        if (m_hashTable[hash][i].first == key)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
void HashTable<T>::insert(const int& key, const T& value)
{
    if (contains(key))
    {
        return;
    }
    int hash = m_hashFunction->hash(key, m_capacity);

    m_hashTable[hash].addToTail(std::pair<int, T>(key, value));
}

template<typename T>
void HashTable<T>::removeKey(const int& key)
{

    int hash = m_hashFunction->hash(key, m_capacity);
    for (int i = 0; i < m_hashTable[hash].size(); i++)
    {
        if (m_hashTable[hash][i].first == key)
        {
            m_hashTable[hash].deleteElementFromPosition(i);
        }
    }
}

template<typename T>
void HashTable<T>::swap(HashTable& other)
{
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_hashFunction, other.m_hashFunction);
    std::swap(m_hashTable, other.m_hashTable);
}

template<typename T>
T& HashTable<T>::operator[](int const key)
{
    int hash = m_hashFunction->hash(key, m_capacity);

    for (int i = 0; i < m_hashTable[hash].size(); i++)
    {
        if (m_hashTable[hash][i].first == key)
        {
            return m_hashTable[hash][i].second;
        }
    }
}

template<typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other)
{
    clear();

    m_hashTable = other.hashTable();
    return *this;

}

template <typename T>
std::ostream& operator<<(std::ostream& os, HashTable<T>& other)
{
    for (int i = 0; i < other.capacity(); i++)
    {
        os << "hash = " << i << ":\t";
        for (int j = 0; j < other.hashTable()[i].size(); j++)
        {
            os << "key = " << other.hashTable()[i][j].first << ", value = " << other.hashTable()[i][j].second << " -----> ";
        }
        os << "NULL" << std::endl;
    }
    return os;
}