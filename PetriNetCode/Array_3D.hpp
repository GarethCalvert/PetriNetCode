//================================================================
//  Array3D.hpp - Created by Gareth Calvert on 11/01/2018.
//  Copyright © 2018 University of Nottingham.
//================================================================
#include <stdio.h>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Array_Matrix.hpp"
//================================================================
#ifndef Array3D_hpp
#define Array3D_hpp

class Array3D
{
public:
    
    // Specialised Constructor
    Array3D(int numRows, int numCols, int numPages);
    
    // Destructor
    ~Array3D();
    
    // Accessors
    int GetNumberOfRows() const;
    int GetNumberOfColumns() const;
    int GetNumberOfPages() const;
    
    // One-based indexing - Read & Write
    double& operator()(int i, int j, int k);
    
    // Zero-based indexing - Read Only
    double Read(int i, int j, int k) const;
    
    // Overridden << operator
    friend std::ostream& operator<<(std::ostream& output, const Array3D& A3D);
    
    // Copy Matrix to Page
    void CopyMatrixToPage(int PageIndex0, Matrix inputMatrix);
    
    // Compute Matrix mean of the entire Array3D
    void ComputeMatrixMean();
    
    // Compute Matrix mean of the first n Pages of the Array3D
    void ComputeMatrixMeanFirstPages(int n);
    
    // Compute Cumulative Sum for Pages
    void ComputeCumulativeSum(int PageIndexSum);
    
    // Compute Partial Mean
    //*** Partial element index is the most recent Sumulative sum index ***
    void ComputePartialMean();
    
    // Accessor to Matrix mean
    Matrix GetMatrixMean();
    
    // Accessor to Cumulative Sum
    Matrix GetCumulativeSum();
    
    // Accessor to Partial Mean
    Matrix GetPartialMean();
    
    // Accessor to Matrix mean element
    double GetMatrixMeanElement(int rowIndex0, int colIndex0);
    
    // Accessor to Partial mean Matrix element
    double GetPartialMeanMatrixElement(int rowIndex0, int colIndex0);
    
private:
    
    // Dimensions of the Array3D
    int mNumberRows;
    int mNumberCols;
    int mNumberPages;
    
    // Entries of the 3D Array
    double*** mpData;
    
    // Matrix for computation and storing matrix mean of all the pages
    Matrix* mpMatrixMean;
    
    // Matrix for Cumulative Sum
    Matrix* mpMatrixCumulativeSum;
    
    // Matrix for Partial Mean
    Matrix* mpMatrixPartialMean;
    
    // Parameters to ensure running sum functions operates
    int mCumulativeSumPageIndex;
    
};

#endif /* Array3D_hpp */
