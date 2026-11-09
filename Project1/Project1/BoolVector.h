#pragma once

#include <iostream>
#include <assert.h>
#include <string.h>

class BoolVector
{
public:
    class Rank;

public:
    using Cell = unsigned char;
    static const int CellSize = 8;
    BoolVector(int length = CellSize);
    BoolVector(int length, bool value);
    BoolVector(const BoolVector& other);
    BoolVector(const char* other);
    ~BoolVector();

    int length() const;
    int weight() const;

    void swap(BoolVector& other);
    bool bitValue(int index) const;
    void setBitValue(int index, bool value);
    void setKBitsValue(int index, int k, bool value);
    void setAllBitsValue(bool value);

    void invertBit(int index);
    void invertVector();

    BoolVector& operator=(const BoolVector& other);
    BoolVector operator&(const BoolVector& other) const;
    BoolVector& operator&=(const BoolVector& other);
    BoolVector operator|(const BoolVector& other) const;
    BoolVector& operator|=(const BoolVector& other);
    BoolVector operator^(const BoolVector& other) const;
    BoolVector& operator^=(const BoolVector& other);
    BoolVector operator~() const;
    BoolVector operator>>(const int shift) const;
    BoolVector& operator>>=(const int shift);
    BoolVector operator<<(const int shift) const;
    BoolVector& operator<<=(const int shift);
    Rank operator[](int index);
    const Rank operator[](int index) const;

private:
    int _excessRankCount() const;
    static Cell _mask(int index);

private:
    Cell* m_cells = nullptr;
    int m_cellCount = 0;
    int m_length = 0;

};

class BoolVector::Rank
{
public:
    Rank() = default;
    Rank(Cell* cell, Cell mask);
    Rank& operator=(const Rank& other);
    Rank& operator=(bool value);
    operator bool() const;

private:
    Cell* m_cell = nullptr;
    Cell m_mask = 0;
};

std::istream& operator>>(std::istream& is, BoolVector& boolVector);
std::ostream& operator<<(std::ostream& os, const BoolVector& boolVector);