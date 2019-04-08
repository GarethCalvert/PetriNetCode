//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Abstract.cpp - Abstract Transition file for providing an 
// an interface for all derived transition classes
//=======================================================================
#include "pch.h"
#include "Transition_Abstract.h"
//=======================================================================


//=======================================================================
// Set vector containing all the input places for the transition
//=======================================================================
void Transition_Abstract::Set_Input_Place_Vector(std::vector<Place*> InputPlaces, std::vector<unsigned int> InputWeights)
{
	*mpInputPlaces = InputPlaces;
	*mpInputWeights = InputWeights;
}

//=======================================================================
// Set vector containing all the output places for the transition
//=======================================================================
void Transition_Abstract::Set_Output_Place_Vector(std::vector<Place*> OutputPlaces, std::vector<unsigned int> OutputWeights)
{
	*mpOutputPlaces = OutputPlaces;
	*mpOutputWeights = OutputWeights;
}

//=======================================================================
// Set vector containing all the inhibitor arc, places for the transition
//=======================================================================
void Transition_Abstract::Set_Inhibitor_Arcs_Vector(vector<Place*> InhibitorPlaces, vector<unsigned int> InihibitorWeights)
{
	*mpInhibitorPlaces = InhibitorPlaces;
	*mpInhibitorWeights = InihibitorWeights;
}

//=======================================================================
// Add an input place to the input place vector for the transition
//=======================================================================
void Transition_Abstract::Set_Input_Place(Place *InputPlace, unsigned int InputWeight)
{
	mpInputPlaces->push_back(&*InputPlace);
	mpInputWeights->push_back(InputWeight);
}

//=======================================================================
// Add an ouput place to the input place vector for the transition
//=======================================================================
void Transition_Abstract::Set_Output_Place(Place *OutputPlace, unsigned int OutputWeight)
{
	mpOutputPlaces->push_back(&*OutputPlace);
	mpOutputWeights->push_back(OutputWeight);
}

//=======================================================================
// Add an inhibitor place to the input place vector for the transition
//=======================================================================
void Transition_Abstract::Set_Inhibitor_Arc(Place *InhibitorPlace, unsigned int InhibitorWeight)
{
	mpInhibitorPlaces->push_back(&*InhibitorPlace);
	mpInhibitorWeights->push_back(InhibitorWeight);
}

//=======================================================================
// Return Transition Name as a string
//=======================================================================
string Transition_Abstract::Get_Transition_Name()
{
	return mTransitionName;
}

//=======================================================================
// Returns boolean of the enabled status of the transition 
//=======================================================================
bool Transition_Abstract::Get_Enabled_Status()
{
	return mTransitionEnabled;
}

//=======================================================================
// Vitural Function - Transition_Fire() - Default definition unless 
// overridden
//=======================================================================
void Transition_Abstract::Transition_Fire()
{
	// Remove Tokens from Input Places
	for (unsigned int i = 0; i < mNumberInputPlaces; i++)
	{
		mpInputPlaces->at(i)->Remove_Tokens(mpInputWeights->at(i));
	}

	// Add Tokens to Output Places
	for (unsigned int i = 0; i < mNumberOutputPlaces; i++)
	{
		mpOutputPlaces->at(i)->Add_Tokens(mpOutputWeights->at(i));
	}
		
}

//=======================================================================
// Vitural Function - Transition_Fire() - Default definition unless 
// overridden
//=======================================================================
void Transition_Abstract::Transition_Enabled_Check(double GlobalTime)
{
	bool Enabled_Test = true;

	// If Inhibitor Arcs are present, check their status
	if (mNumberInhibitorArcs > 0)
	{
		for (unsigned int i = 0; i < mNumberInhibitorArcs; i++)
		{
			if (mpInhibitorPlaces->at(i)->Get_Place_Marking() >= mpInhibitorWeights->at(i))
			{
				mTransitionInhibited = true;
				Enabled_Test = false;
			}
		}
	}

	// If Transition is already enabled check that it still is
	if (mTransitionEnabled == true && mTransitionInhibited == false)
	{
		for (unsigned int i = 0; i < mNumberInputPlaces; i++)
		{
			if (Enabled_Test == true)
			{
				if (mpInputPlaces->at(i)->Get_Place_Marking() < mpInputWeights->at(i))
				{
					mTransitionEnabled = false;
					Enabled_Test = false;
					// *** Cumulative Time probably would need reset
				}
			}
		}
	}

	// If Transition is already enabled, how long is the remaining delay
	if (Enabled_Test == true && mTransitionEnabled == true)
	{
		mCumulativeTime = GlobalTime - mEnabledTime;
		mRemainingDelay = mTransitionDelay - mCumulativeTime;
		// Error Message to catch negative times
		if (mRemainingDelay < 0)
		{
			cout << "****ERROR: Negative Remaining Delay in Transition";
		}
		Enabled_Test = false;
	}

	// If transition is not already, and it is not inhibited then check if it is
	if (Enabled_Test == true)
	{
		for (unsigned int i = 0; i < mNumberInputPlaces; i++)
		{
			if (Enabled_Test == true)
			{
				if (mpInputPlaces->at(i)->Get_Place_Marking() < mpInputWeights->at(i))
				{
					mTransitionEnabled = false;
				}
			}
		}
	}

	// If Test is still true, then Transition is enabled
	if (Enabled_Test == true)
	{
		mTransitionEnabled = true;
		mEnabledTime = GlobalTime;
		mRemainingDelay = mTransitionDelay;
	}
}