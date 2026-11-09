#include "utility"
#include "assert.h"

#include "BoolVector.h"

BoolVector::BoolVector(int lenght) :m_length(lenght) {
    assert(lenght >= 0);
    m_cellCount = m_length / CellSize;
    if (m_length % CellSize != 0)
    {
        m_cellCount++;
    }

    m_cells = new Cell[m_cellCount];

    for (int i = 0; i < m_cellCount; i++) {
        m_cells[i] = 0;
    }
}

BoolVector::BoolVector(const BoolVector& other) {
    m_cellCount = other.m_cellCount;
    m_length = other.m_length;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; i++)
    {
        m_cells[i] = other.m_cells[i];
    }
}

BoolVector::BoolVector(int length, bool value) :m_length(length) {
    assert(length >= 0);
    m_cellCount = m_length / CellSize;

    if (m_length % CellSize != 0) {
        m_cellCount++;
    }
    m_cells = new Cell[m_cellCount];
    Cell cellValue = 0;
    if (value) {
        cellValue = ~cellValue;
    }
    for (int i = 0; i < m_cellCount; i++) {
        m_cells[i] = cellValue;
    }
}

BoolVector::BoolVector(const char* other)
    : BoolVector(strlen(other), false)
{
    for (int i = 0; i < m_length; i++) {
        if (other[i] == '1') {
            setBitValue(i, 1);
        }
    }
}


BoolVector::~BoolVector() {
    delete[] m_cells;
}

int BoolVector::length() const {
    return m_length;
}

int BoolVector::weight() const {
    int weight = 0;
    for (int i = 0; i < m_length; i++) {
        if (bitValue(i)) {
            weight++;
        }
    }
    return weight;
}

void BoolVector::swap(BoolVector& other) {
    std::swap(m_cells, other.m_cells);
    std::swap(m_cellCount, other.m_cellCount);
    std::swap(m_length, other.m_length);
}

bool BoolVector::bitValue(int index) const {
    assert(index >= 0 && index < m_length);
    Cell mask = _mask(index);
    return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(int index, bool value) {
    assert(index >= 0 && index < m_length);
    Cell mask = _mask(index);
    if (value)
    {
        m_cells[index / CellSize] |= mask;
    }
    else
    {
        m_cells[index / CellSize] &= ~mask;
    }
}

void BoolVector::setKBitsValue(int index, int k, bool value) {
    assert(index >= 0 && index + k - 1 < m_length);
    for (int i = index; i < index + k; i++) {
        setBitValue(i, value);
    }
}

void BoolVector::setAllBitsValue(bool value) {

    if (value == 0) {
        for (int i = 0; i < m_cellCount; i++) {
            m_cells[i] = 0;
        }
    }
    else {
        for (int i = 0; i < m_cellCount; i++) {
            m_cells[i] = ~0;
        }
    }

}

void BoolVector::invertBit(int index) {
    assert(index >= 0 && index < m_length);
    Cell mask = _mask(index);
    m_cells[index / CellSize] = ~(m_cells[index / CellSize] ^ ~mask);
}

void BoolVector::invertVector() {
    for (int i = 0; i < m_cellCount; i++) {
        m_cells[i] = ~m_cells[i];
    }
}

BoolVector& BoolVector::operator=(const BoolVector& other) {
    BoolVector newBv(other);
    swap(newBv);
    return *this;
}

BoolVector::Rank BoolVector::operator[](int index) {
    assert(index >= 0 && index < m_length);

    return Rank(&m_cells[index / CellSize], _mask(index));
}

const BoolVector::Rank BoolVector::operator[](int index) const {
    assert(index >= 0 && index < m_length);

    return Rank(&m_cells[index / CellSize], _mask(index));
}

BoolVector BoolVector::operator&(const BoolVector& other) const {
    BoolVector newBv(*this);
    for (int i = 0; i < m_cellCount; i++) {
        newBv.m_cells[i] = m_cells[i] & other.m_cells[i];
    }
    return newBv;
}

BoolVector& BoolVector::operator&=(const BoolVector& other) {
    (other & *this).swap(*this);
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector& other) const {
    BoolVector newBv(*this);
    for (int i = 0; i < m_cellCount; i++) {
        newBv.m_cells[i] = m_cells[i] | other.m_cells[i];
    }
    return newBv;
}

BoolVector& BoolVector::operator|=(const BoolVector& other) {
    *this = *this | other;
    return *this;
}

BoolVector BoolVector::operator^(const BoolVector& other) const {
    BoolVector newBv(*this);
    for (int i = 0; i < m_cellCount; i++) {
        newBv.m_cells[i] = m_cells[i] ^ other.m_cells[i];
    }
    return newBv;
}

BoolVector& BoolVector::operator^=(const BoolVector& other) {
    *this = *this ^ other;
    return *this;
}

BoolVector BoolVector::operator~() const {
    BoolVector newBv(*this);
    newBv.invertVector();
    return newBv;
}

BoolVector BoolVector::operator>>(const int shift) const {

    if (shift <= 0) {
        return *this;
    }

    BoolVector newBv(m_length);

    if (shift >= m_length) {
        return newBv;
    }

    for (int i = shift; i < m_length; i++) {
        if (bitValue(i - shift)) {
            newBv.setBitValue(i, true);
        }
    }

    return newBv;
}

BoolVector& BoolVector::operator>>=(const int shift) {
    *this = *this >> shift;
    return *this;
}

BoolVector BoolVector::operator<<(const int shift) const {
    if (shift <= 0) {
        return *this;
    }

    BoolVector newBv(m_length);

    if (shift >= m_length) {
        return newBv;
    }

    for (int i = m_length - 1; i >= shift; i--) {
        if (bitValue(i)) {
            newBv.setBitValue(i - shift, true);
        }
    }

    return newBv;
}

BoolVector& BoolVector::operator<<=(const int shift) {
    *this = *this << shift;
    return *this;
}

int BoolVector::_excessRankCount() const {
    return(m_cellCount * CellSize - m_length);
}

BoolVector::Cell BoolVector::_mask(int index) {
    Cell mask = 1;
    mask <<= CellSize - 1 - (index % CellSize);
    return mask;
}

BoolVector::Rank::Rank(Cell* cell, Cell mask) : m_cell(cell), m_mask(mask) {
    assert(m_cell != nullptr);
    assert(m_mask > 0);
}

BoolVector::Rank& BoolVector::Rank::operator=(const Rank& other) {
    return operator=(static_cast<bool>(other));
}

BoolVector::Rank& BoolVector::Rank::operator=(bool value) {
    if (value)
    {
        *m_cell |= m_mask;
    }
    else
    {
        *m_cell &= ~m_mask;
    }
    return *this;
}

BoolVector::Rank::operator bool() const {
    return (*m_cell & m_mask) != 0;
}


std::istream& operator>>(std::istream& is, BoolVector& boolVector) {
    for (int i = 0; i < boolVector.length(); i++) {
        bool bit;
        is >> bit;
        boolVector.setBitValue(i, bit);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const BoolVector& boolVector) {
    for (int i = 0; i < boolVector.length(); i++) {
        os << boolVector.bitValue(i);
    }
    return os;
}