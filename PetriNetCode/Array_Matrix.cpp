//================================================================
//  Matrix.cpp - Created by Gareth Calvert.
//  Copyright © 2018 University of Nottingham.
//================================================================
#include "Array_Matrix.hpp"
#include "Array_Vector.hpp"

//========================================================
// Overwritten copy constructor
//========================================================
// Allocate memory for new matrix, and copy
// entries into this matrix
Matrix::Matrix(const Matrix& otherMatrix)
{
   mNumRows = otherMatrix.mNumRows;
   mNumCols = otherMatrix.mNumCols;
   mData = new double* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new double [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = otherMatrix.mData[i][j];
      }
   }
}

//========================================================
// Constructor for vector of a given length
//========================================================
// Allocates memory, and initialises entries to zero
Matrix::Matrix(int numRows, int numCols)
{
   assert(numRows > 0);
   assert(numCols > 0);
   mNumRows = numRows;
   mNumCols = numCols;
   mData = new double* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new double [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = 0.0;
      }
   }
}

//========================================================
// Overwritten destructor to correctly free memory
//========================================================
Matrix::~Matrix()
{
   for (int i=0; i<mNumRows; i++)
   {
      delete[] mData[i];
   }
   delete[] mData;
}

//========================================================
// Method to get number of rows of matrix
//========================================================
int Matrix::GetNumberOfRows() const
{
   return mNumRows;
}

//========================================================
// Method to get number of columns of matrix
//========================================================
int Matrix::GetNumberOfColumns() const
{
   return mNumCols;
}

//========================================================
// Overloading the round brackets
//========================================================
// Note that this uses `one-based' indexing,
// and a check on the validity of the index
double& Matrix::operator()(int i, int j)
{
   assert(i > 0);
   assert(i < mNumRows+1);
   assert(j > 0);
   assert(j < mNumCols+1);
   return mData[i-1][j-1];
}

//========================================================
// Overloading the assignment operator
//========================================================
Matrix& Matrix::operator=(const Matrix& otherMatrix)
{
   assert(mNumRows = otherMatrix.mNumRows);
   assert(mNumCols = otherMatrix.mNumCols);

   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = otherMatrix.mData[i][j];
      }
   }
   return *this;
}

//========================================================
// Overloading the unary + operator
//========================================================
Matrix Matrix::operator+() const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = mData[i][j];
      }
   }
   return mat;
}

//========================================================
// Overloading the unary - operator
//========================================================
Matrix Matrix::operator-() const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = -mData[i][j];
      }
   }
   return mat;
}

//========================================================
// Overloading the binary + operator
//========================================================
Matrix Matrix::operator+(const Matrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = mData[i][j] + m1.mData[i][j];
      }
   }
   return mat;
}

//========================================================
// Overloading the binary - operator
//========================================================
Matrix Matrix::operator-(const Matrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = mData[i][j] - m1.mData[i][j];
      }
   }
   return mat;
}

//========================================================
// Overloading scalar multiplication
//========================================================
Matrix Matrix::operator*(double a) const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i+1,j+1) = a*mData[i][j];
      }
   }
   return mat;
}

//========================================================
// Overloading matrix multiplied by a vector
//========================================================
Vector operator*(const Matrix& m, const Vector& v)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfColumns() == original_vector_size);
   int new_vector_length = m.GetNumberOfRows();
   Vector new_vector(new_vector_length);

   for (int i=0; i<new_vector_length; i++)
   {
      for (int j=0; j<original_vector_size; j++)
      {
         new_vector[i] += m.mData[i][j]*v.Read(j);
      }
   }

   return new_vector;
}

//========================================================
// Overloading vector multiplied by a matrix
//========================================================
Vector operator*(const Vector& v, const Matrix& m)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfRows() == original_vector_size);
   int new_vector_length = m.GetNumberOfColumns();
   Vector new_vector(new_vector_length);

   for (int i=0; i<new_vector_length; i++)
   {
      for (int j=0; j<original_vector_size; j++)
      {
         new_vector[i] += v.Read(j)*m.mData[j][i];
      }
   }

   return new_vector;
}

//========================================================
// Calculate determinant of square matrix recursively
//========================================================
double Matrix::CalculateDeterminant() const
{
   assert(mNumRows == mNumCols);
   double determinant = 0.0;

   if (mNumRows == 1)
   {
      determinant = mData[0][0];
   }
   else
   {
      // More than one entry of matrix
      for (int i_outer=0; i_outer<mNumRows; i_outer++)
      {
         Matrix sub_matrix(mNumRows-1, 
                             mNumRows-1);
         for (int i=0; i<mNumRows-1; i++)
         {
            for (int j=0; j<i_outer; j++)
            {
               sub_matrix(i+1,j+1) = mData[i+1][j];
            }
            for (int j=i_outer; j<mNumRows-1; j++)
            {
               sub_matrix(i+1,j+1) = mData[i+1][j+1];
            }
         }
         double sub_matrix_determinant = 
                  sub_matrix.CalculateDeterminant();

         determinant += pow(-1.0, i_outer)*
                  mData[0][i_outer]*sub_matrix_determinant;
      }
   }
   return determinant;
}

//========================================================
// Defining cout formatting
//========================================================
std::ostream& operator<<(std::ostream& output,
                        const Matrix& m)
{

  // Print formatted output
  for (int i=0; i< m.GetNumberOfRows(); i++)
  {
    for (int j=0; j< m.GetNumberOfColumns(); j++)
    {
      output << std::setw(14)
             << std::setprecision(5)
	     << std::scientific 
	     << m.mData[i][j];
    }
    output << std::endl;
  }
  output << std::endl;

  return output;

}

//========================================================
// Overloading matrix multiplication
//========================================================
Matrix Matrix::operator*(const Matrix& m1) const
{
    
    //Checking to see if matrix multiplication is possible
    assert((mNumRows == m1.GetNumberOfColumns()) && (mNumCols == m1.GetNumberOfRows()));
    
    Matrix mat(mNumRows, mNumCols);
    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; j<mNumCols; j++)
        {
            
            for (int k=0; k<mNumCols; k++)
            {
                mat(i+1,j+1) += mData[i][k]*m1.mData[k][j];
            }
            
            
        }
    }
    
    return mat;
}
//========================================================
// Kronecker Product
//========================================================
Matrix Matrix::KroneckerProduct(const Matrix& m1) const
{
    Matrix mat(mNumRows*m1.mNumRows, mNumCols*m1.mNumCols);
    
    for (int i =1; i<mNumRows+1; i++)
    {
        for (int j =1; j<mNumCols+1; j++)
        {
            for (int k=1; k<m1.mNumRows+1; k++)
            {
                for (int l=1; l<m1.mNumCols+1; l++)
                {
                    mat(m1.mNumRows*(i-1)+k, m1.mNumCols*(j-1)+l) = mData[i-1][j-1]*m1.mData[k-1][l-1];
                }
            }
        }
    }
    
    return mat;
}

//========================================================
// Read-only variant of []
//========================================================
// Note that this uses `zero-based' indexing,
// and a check on the validity of the index
double Matrix::Read(int i, int j) const
{
    assert(i > -1);
    assert(i < mNumRows);
    assert(j > -1);
    assert(j < mNumCols);
    return mData[i][j];
}

//========================================================
// Save Matrix
//========================================================
void Matrix::SaveMatrix(const std::string FileName, const int rows, const int cols)
{
    // Setting strem file precision
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(6);
    
    // Opening file
    std::string file_name = FileName;
    output_file.open(file_name);
    assert(output_file.is_open());
    
    // Write data
    for (int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            output_file << std::setw(15) << mData[i][j] << " ";
        }
        output_file << std::endl;
    }
    
    // Close file
    output_file.close();
}
