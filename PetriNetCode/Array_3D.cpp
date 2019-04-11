//================================================================
//  Array3D.cpp - Created by Gareth Calvert.
//  Copyright © 2018 University of Nottingham.
//================================================================
#include "Array_3D.hpp"

//================================================
// Constructor
//================================================
Array3D::Array3D(int numRows, int numCols, int numPages)
{
    assert(numRows>0);
    assert(numCols>0);
    assert(numPages);
    mNumberRows = numRows;
    mNumberCols = numCols;
    mNumberPages = numPages;
    
    mpData = new double** [mNumberRows];
    for (int i=0; i<mNumberRows; i++)
    {
        mpData[i] = new double* [mNumberCols];
    }
    
    for (int i=0; i<mNumberRows; i++)
    {
        for(int j=0; j<mNumberCols; j++)
        {
            mpData[i][j] = new double [mNumberPages];
        }
    }
    
    for (int i=0; i<mNumberRows; i++)
    {
        for (int j=0; j<mNumberCols; j++)
        {
            for (int k = 0; k<mNumberPages; k++)
            {
                mpData[i][j][k] = 0.0;
            }
        }
    }

    // Constructing instances of matrices for some class functionality
    mpMatrixMean = new Matrix(mNumberRows, mNumberCols);
    mpMatrixCumulativeSum = new Matrix(mNumberRows, mNumberCols);
    mpMatrixPartialMean = new Matrix(mNumberPages, mNumberCols);
    
    mCumulativeSumPageIndex = 0;
    
}

//================================================
// Destructor
//================================================
Array3D::~Array3D()
{
    // Deleting Pages
    for (int i=0; i<mNumberRows; i++)
    {
        for (int j=0; j<mNumberCols; j++)
        {
            
             delete[] mpData[i][j];
            
        }
    }
    
    // Deleting Cols
    for (int i=0; i<mNumberRows; i++)
    {
        delete[] mpData[i];
    }
    
    //Deleting Rows
    delete[] mpData;
    
    // Deleting other Matrices in class
    delete mpMatrixMean;
    delete mpMatrixPartialMean;
    delete mpMatrixCumulativeSum;
}

//========================================================
// Method to get number of rows of matrix
//========================================================
int Array3D::GetNumberOfRows() const
{
    return mNumberRows;
}

//========================================================
// Method to get number of columns of matrix
//========================================================
int Array3D::GetNumberOfColumns() const
{
    return mNumberCols;
}

//========================================================
// Method to get number of columns of matrix
//========================================================
int Array3D::GetNumberOfPages() const
{
    return mNumberPages;
}

//========================================================
// Overloading the round brackets
//========================================================
// Note that this uses `one-based' indexing,
// and a check on the validity of the index
double& Array3D::operator()(int i, int j, int k)
{
    assert(i > 0);
    assert(i < mNumberRows+1);
    assert(j > 0);
    assert(j < mNumberCols+1);
    assert(k > 0);
    assert(k < mNumberPages+1);
    return mpData[i-1][j-1][k-1];
}

//========================================================
// Read-only variant of []
//========================================================
// Note that this uses `zero-based' indexing,
// and a check on the validity of the index
double Array3D::Read(int i, int j, int k) const
{
    assert(i > -1);
    assert(i < mNumberRows);
    assert(j > -1);
    assert(j < mNumberCols);
    assert(j > -1);
    assert(j < mNumberPages);
    return mpData[i][j][k];
}

//========================================================
// Defining output formatting
//========================================================
std::ostream& operator<<(std::ostream& output, const Array3D& A3D)
{
    for (int k=0; k<A3D.GetNumberOfPages(); k++)
    {
        output<< "******* Page " << k+1 << " ******** \n" << std::endl ;
        
        for (int i=0; i< A3D.GetNumberOfRows(); i++)
        {
            for (int j=0; j< A3D.GetNumberOfColumns(); j++)
            {
                output << std::setw(14)
                << std::setprecision(5)
                << std::scientific
                << A3D.mpData[i][j][k];
            }
            output << std::endl;
        }
        output << std::endl;
    }
    output << std::endl;
    
    return output;
}

//========================================================
// Copy Matrix To Page
//========================================================
void Array3D::CopyMatrixToPage(int PageIndex0, Matrix inputMatrix)
{
    assert(inputMatrix.GetNumberOfRows() <= mNumberRows);
    assert(inputMatrix.GetNumberOfColumns() <= mNumberCols);
    
    for(int i = 0; i<inputMatrix.GetNumberOfRows(); i++)
    {
        for(int j = 0; j<inputMatrix.GetNumberOfColumns(); j++)
        {
            mpData[i][j][PageIndex0] = inputMatrix.Read(i, j);
        }
    }
    
};

//========================================================
// Compute the Matrix mean of the entire Array3D
//========================================================
void Array3D::ComputeMatrixMean()
{
    // Ensuring that the Matrix Mean has been reset
    *mpMatrixMean = *mpMatrixMean*0;
    
    // Creating a matrix with each element being a sum of respective element of each page
    for(int k=0; k<mNumberPages; k++)
    {
        for(int i=0; i<mNumberRows; i++)
        {
            for(int j=0; j<mNumberCols; j++)
            {
                mpMatrixMean->operator()(i+1, j+1) += mpData[i][j][k];
            }
        }
    }
    
    // Dividing the summed matrix by the number of pages
    *mpMatrixMean = *mpMatrixMean*(1.0/double(mNumberPages));
}

//========================================================
// Compute the Matrix mean of the First n pages of Array3D
//========================================================
void Array3D::ComputeMatrixMeanFirstPages(int n)
{
    // Checking that n is greater than 0 and less than or equal to the Number of Pages
    assert(n>0);
    assert(n<=mNumberPages);
    
    // Ensuring that the Matrix Mean has been reset
    *mpMatrixMean = *mpMatrixMean*0;
    
    // Creating a matrix with each element being a sum of respective element of each page
    for(int k=0; k<n; k++)
    {
        for(int i=0; i<mNumberRows; i++)
        {
            for(int j=0; j<mNumberCols; j++)
            {
                mpMatrixMean->operator()(i+1, j+1) += mpData[i][j][k];
            }
        }
    }
    
    // Dividing the summed matrix by the number of pages
    *mpMatrixMean = *mpMatrixMean*(1.0/double(n));
}

//========================================================
// Compute Cumulative Sum
//========================================================
void Array3D::ComputeCumulativeSum(int PageIndexSum1)
{
    assert(PageIndexSum1 >= 1);
    assert(PageIndexSum1 <= mNumberPages);
    assert(PageIndexSum1 >= mCumulativeSumPageIndex);
    
    for(int k = mCumulativeSumPageIndex; k<PageIndexSum1; k++)
    {
        for(int i=0; i<mNumberRows; i++)
        {
            for(int j=0; j<mNumberCols; j++)
            {
                mpMatrixCumulativeSum->operator()(i+1, j+1) += mpData[i][j][k];
            }
        }
    }
    
    mCumulativeSumPageIndex = PageIndexSum1;
}

//========================================================
// Compute Partial Mean
//========================================================
void Array3D::ComputePartialMean()
{
    *mpMatrixPartialMean = *mpMatrixCumulativeSum;
    *mpMatrixPartialMean = *mpMatrixPartialMean*(1.0/mCumulativeSumPageIndex);
}

//========================================================
// Accessor for the Matrix Mean
//========================================================
Matrix Array3D::GetMatrixMean()
{
    return *mpMatrixMean;
}

//========================================================
// Accessor for the Cumulative Sum Matrix
//========================================================
Matrix Array3D::GetCumulativeSum()
{
    return *mpMatrixCumulativeSum;
}

//========================================================
// Accessor for the Partial Mean
//========================================================
Matrix Array3D::GetPartialMean()
{
    return *mpMatrixPartialMean;
}

//========================================================
// Accessor for an element of the Matrix Mean
//========================================================
double Array3D::GetMatrixMeanElement(int rowIndex0, int colIndex0)
{
    return mpMatrixMean->Read(rowIndex0, colIndex0);
}

//========================================================
// Accessor for an element of the Matrix Mean
//========================================================
double Array3D::GetPartialMeanMatrixElement(int rowIndex0, int colIndex0)
{
    return mpMatrixPartialMean->Read(rowIndex0, colIndex0);
}
