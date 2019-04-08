#include "pch.h"
#include "Place.h"

//=======================================================================
// Constructor
//=======================================================================
Place::Place(string PlaceName, int InitialTokenCount)
{
	mPlaceName = PlaceName;
	mInitialTokenCount = InitialTokenCount;
	mCurrentTokenCount = mInitialTokenCount;
}

//=======================================================================
// Destructor 
//=======================================================================
Place::~Place()
{

}

//=======================================================================
// Remove Tokens Function
//=======================================================================
void Place::Remove_Tokens(int num2remove)
{
	assert(mCurrentTokenCount - num2remove >= 0);
	mCurrentTokenCount = mCurrentTokenCount - num2remove;
}

//=======================================================================
// Add Tokens Function
//=======================================================================
void Place::Add_Tokens(int num2add)
{
	mCurrentTokenCount += num2add;
}

//=======================================================================
// Reset To Initial Marking
//=======================================================================
void Place::Reset_To_Initial_Marking()
{
	mCurrentTokenCount = mInitialTokenCount;
}

//=======================================================================
// Accessor to Place Name
//=======================================================================
string Place::Get_Place_Name()
{
	return mPlaceName;
}

//=======================================================================
// Accessor to Place Marking
//=======================================================================
unsigned int Place::Get_Place_Marking()
{
	return mCurrentTokenCount;
}

//=======================================================================
// Print Place Marking
//=======================================================================
void Place::Print_Place_Marking()
{
	cout << "Marking of " << mPlaceName << ": " << mCurrentTokenCount << endl;
}