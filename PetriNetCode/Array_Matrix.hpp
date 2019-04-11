//================================================================
//  Matrix.hpp -Created by Gareth Calvert.
//  Copyright © 2018 University of Nottingham.
//================================================================
// Class adapted from Whiteley, Pitt-Francis
#include "Array_Vector.hpp"
#include <cmath>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
//================================================================


#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF


class Matrix
{
public:

  // Copy constructor
  Matrix(const Matrix& otherMatrix);

  // Specialised Constructor 
  Matrix(int numRows, int numCols);

  // Destructor
  ~Matrix();

  // Accessors
  int GetNumberOfRows() const;
  int GetNumberOfColumns() const;

  // 1-based indexing
  double& operator()(int i, int j);

  //Overloaded assignment operator
  Matrix& operator=(const Matrix& otherMatrix);

  // Unary +
  Matrix operator+() const;

  // Unary -
  Matrix operator-() const;

  // Binary + 
  Matrix operator+(const Matrix& m1) const;

  // Binary - 
  Matrix operator-(const Matrix& m1) const; 

  // Scalar multiplication
  Matrix operator*(double a) const;

  // Determinant
  double CalculateDeterminant() const;

  // Declare vector multiplication friendship
  friend Vector operator*(const Matrix& m, 
                          const Vector& v);
  friend Vector operator*(const Vector& v, 
                          const Matrix& m);

  // Overridden << operator
  friend std::ostream& operator<<(std::ostream& output,
                        const Matrix& m);
    
  // Overridden * operator
  Matrix operator*(const Matrix& m1) const;
  
  // Kronekcer Product
  Matrix KroneckerProduct(const Matrix& m1) const;
   
  // Read the value of an element of the matrix
  double Read(int i, int j) const;
    
  // Save the matrix to file
  void SaveMatrix(const std::string FileName, const int rows, const int cols);
    
private:
    
    // Entries of matrix
    double** mData;
    
    // Dimensions
    int mNumRows, mNumCols; 

};

// Prototype signatures for friend operators
Vector operator*(const Matrix& m, const Vector& v);
Vector operator*(const Vector& v, const Matrix& m);

#endif
