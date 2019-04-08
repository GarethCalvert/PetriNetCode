#include <string>
#include <iostream>
#include <cassert>
using namespace std;
#pragma once


class Place
{
public:

	// Constructor 
	Place(string PlaceName, int InitialTokenCount);
	// Destructor
	~Place();

	// Public Functions
	void Remove_Tokens(int num2remove);
	void Add_Tokens(int num2add);
	void Reset_To_Initial_Marking();
	void Print_Place_Marking();

	// Accessor Functions
	string Get_Place_Name();
	unsigned int Get_Place_Marking();


private:

	// Private members
	string mPlaceName;
	unsigned int mInitialTokenCount;
	unsigned int mCurrentTokenCount;
};

