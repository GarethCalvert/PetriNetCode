//================================================================
//  Vector.cpp - Created by Gareth Calvert.
//  Copyright © 2018 University of Nottingham.
//================================================================
#include "Array_Vector.hpp"

//================================================
// Overridden copy constructor
//================================================
// Allocates memory for new vector, and copies
// entries of other vector into it
Vector::Vector(const Vector& otherVector)
{
   mSize = otherVector.GetSize();
   mData = new double [mSize];
   for (int i=0; i<mSize; i++)
   {
      mData[i] = otherVector.mData[i];
   }
}

//================================================
// Constructor for vector of a given size
//================================================
// Allocates memory, and initialises entries to zero
Vector::Vector(int size)
{
   assert(size > 0);
   mSize = size;
   mData = new double [mSize];
   for (int i=0; i<mSize; i++)
   {
      mData[i] = 0.0;
   }
}

//================================================
// Overridden destructor to correctly free memory
//================================================
Vector::~Vector()
{
   delete[] mData;
}

//================================================
// Function returning the size of a vector
//================================================
int Vector::GetSize() const
{
   return mSize;
}

//================================================
// Overloading square brackets
//================================================
// Note that this uses `zero-based' indexing.
double& Vector::operator[](int i)
{
   assert(i > -1);
   assert(i < mSize);
   return mData[i];
}

//================================================
// Read-only variant of []
//================================================
// Note that this uses `zero-based' indexing.
double Vector::Read(int i) const
{
   assert(i > -1);
   assert(i < mSize);
   return mData[i];
}

//================================================
// Overloading round brackets
//================================================
// Note that this uses `one-based' indexing
double& Vector::operator()(int i)
{
   assert(i > 0);
   assert(i < mSize+1);
   return mData[i-1];
}

//================================================
// Overloading the assignment operator
//================================================
Vector& Vector::operator=(const Vector& otherVector)
{
   assert(mSize == otherVector.mSize);
   for (int i=0; i<mSize; i++)
   {
      mData[i] = otherVector.mData[i];
   }
   return *this;
}

//================================================
// Overloading the unary + operator
//================================================
Vector Vector::operator+() const
{
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i];
   }
   return v;
}

//================================================
// Overloading the unary - operator
//================================================
Vector Vector::operator-() const
{
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = -mData[i];
   }
   return v;
}

//================================================
// Overloading the binary + operator
//================================================
Vector Vector::operator+(const Vector& v1) const
{
   assert(mSize == v1.mSize);
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i] + v1.mData[i];
   }
   return v;
}

//================================================
// Overloading the binary - operator
//================================================
Vector Vector::operator-(const Vector& v1) const
{
   assert(mSize == v1.mSize);
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = mData[i] - v1.mData[i];
   }
   return v;
}

//================================================
// Overloading scalar multiplication
//================================================
Vector Vector::operator*(double a) const
{
   Vector v(mSize);
   for (int i=0; i<mSize; i++)
   {
      v[i] = a*mData[i];
   }
   return v;
}

//================================================
// Method to calculate norm (with default value p=2)
// corresponding to the Euclidean norm
//================================================
double Vector::CalculateNorm(int p) const
{
   double norm_val, sum = 0.0;
   for (int i=0; i<mSize; i++)
   {
      sum += pow(fabs(mData[i]), p);
   }
   norm_val = pow(sum, 1.0/((double)(p)));
   return norm_val;
}

//================================================
// Method to calculate the infinity norm
//================================================
double Vector::CalculateInfinityNorm() const
{
   double norm_val = 0;
   for (int i=0; i<mSize; i++)
   {
     double abs_val = fabs(mData[i]);
     if ( norm_val < abs_val )
     {
       norm_val = abs_val;
     }
   }
   return norm_val;
}

//================================================
// Method to calculate scalar product with another vector
//================================================
double Vector::ScalarProduct(const Vector& v) const
{
   double scalar_product = 0.0;
   assert(mSize == v.GetSize());
   for (int i=0; i<mSize; i++)
   {
      scalar_product += mData[i]*v.Read(i);
   }
   return scalar_product;
}

//================================================
// MATLAB style friend to get the size of a vector
//================================================
int length(const Vector& v)
{
   return v.mSize;
}

//================================================
// Code determining the formatting of output
//================================================
std::ostream& operator<<(std::ostream& output,
                        const Vector& v)
{
   for (int i=0; i<v.mSize; i++)
   {
      output << std::setw(14)
             << std::setprecision(5)
	     << std::scientific 
	     << v.Read(i)
	     << std::endl;
   }
   output << std::endl;

   return output;
}

//================================================
// Code to save Vector to file
//================================================
void Vector::SaveVector(std::string FileName, int size)
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
    for (int i=0; i<size; i++)
    {
        
            output_file << std::setw(15) << mData[i] << " ";
            output_file << std::endl;
    }
    
    // Close file
    output_file.close();
}
