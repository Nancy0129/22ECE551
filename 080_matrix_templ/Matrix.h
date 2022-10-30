#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
template<typename T>

//YOUR CODE GOES HERE!

class Matrix {
 private:
  int numRows;
  int numColumns;
  vector<vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    for (int i = 0; i < r; i++) {
      rows.push_back(vector<T>(c));
    }
  }

  Matrix(const Matrix<T> & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = rhs.rows;
  }

  ~Matrix() {}

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = rhs.rows;
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  vector<T> & operator[](int index) {
    assert(index < numRows);
    assert(index >= 0);
    return rows[index];
  }

  const vector<T> & operator[](int index) const {
    assert(index < numRows);
    assert(index >= 0);
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
    return (rows == rhs.rows);
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix<T> temp(rhs.numRows, rhs.numColumns);
    for (int i = 0; i < rhs.numRows; i++) {
      for (int j = 0; j < rhs.numColumns; j++) {
        temp[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return temp;
  }
};

template<typename T>
ostream & operator<<(ostream & s, const vector<T> & rhs) {
  if (rhs.size() < 1) {
    s << "{}";
    return s;
  }
  s << "{";
  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i];
    s << ", ";
  }
  s << rhs[rhs.size() - 1];
  s << "}";
  return s;
}

template<typename T>
ostream & operator<<(ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() < 1) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i];
    s << ",\n";
  }
  s << rhs[rhs.getRows() - 1];
  s << " ]";
  return s;
}
#endif
