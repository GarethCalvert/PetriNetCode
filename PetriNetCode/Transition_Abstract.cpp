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
void Transition_Abstract::Set_Input_Arcs_Vector(std::vector<Place*> InputPlaces, std::vector<unsigned int> InputWeights)
{
	*mpInputPlaces = InputPlaces;
	*mpInputWeights = InputWeights;
}

//=======================================================================
// Set vector containing all the output places for the transition
//=======================================================================
void Transition_Abstract::Set_Output_Arcs_Vector(std::vector<Place*> OutputPlaces, std::vector<unsigned int> OutputWeights)
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
void Transition_Abstract::Set_Input_Arc(Place *InputPlace, unsigned int InputWeight)
{
	mpInputPlaces->push_back(&*InputPlace);
	mpInputWeights->push_back(InputWeight);
}

//=======================================================================
// Add an ouput place to the input place vector for the transition
//=======================================================================
void Transition_Abstract::Set_Output_Arc(Place *OutputPlace, unsigned int OutputWeight)
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
// Function included here, so that each unique transition type can print
// transition properties out
//=======================================================================
void Transition_Abstract::Transition_Type_Properties()
{

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
// Vitural Function - Reset_Transition_To_Initial() - Default definition unless 
// overridden
//=======================================================================
void Transition_Abstract::Reset_Transition_To_Initial()
{
	mNumberTransitionFires = 0;
	Transition_Resample();
}

//=======================================================================
// Vitural Function - Transition_Fire() - Default definition unless 
// overridden
//=======================================================================
void Transition_Abstract::Transition_Fire()
{
	// Remove Tokens from Input Places
	for (unsigned int i = 0; i < mNumberInputArcs; i++)
	{
		mpInputPlaces->at(i)->Remove_Tokens(mpInputWeights->at(i));
	}

	// Add Tokens to Output Places
	for (unsigned int i = 0; i < mNumberOutputArcs; i++)
	{
		mpOutputPlaces->at(i)->Add_Tokens(mpOutputWeights->at(i));
	}

	mTransitionEnabled = false;
	mNumberTransitionFires++;

	// Resampling a new transition delay for the transition using the any pre-defined distribution
	Transition_Resample();
		
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
				mTransitionEnabled = false;
				Enabled_Test = false;
			}
		}
	}

	// If Transition is already enabled, check that it still is
	if (mTransitionEnabled == true && mTransitionInhibited == false)
	{
		for (unsigned int i = 0; i < mNumberInputArcs; i++)
		{
			if (Enabled_Test == true)
			{
				if (mpInputPlaces->at(i)->Get_Place_Marking() < mpInputWeights->at(i))
				{
					mTransitionEnabled = false;
					Enabled_Test = false;
					mCumulativeTime = 0.0; // Reset cumulative time
					mRemainingDelay = mTransitionDelay;

					// ***********************
					// If a transition is enabled and then finds itself disabled. It should be resampled for a new time, if it is stochastic etc
					Transition_Resample();
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

	// If transition is not already, and it is not inhibited, then check if it is enabled now
	if (Enabled_Test == true)
	{
		for (unsigned int i = 0; i < mNumberInputArcs; i++)
		{
			if (Enabled_Test == true)
			{
				if (mpInputPlaces->at(i)->Get_Place_Marking() < mpInputWeights->at(i))
				{
					mTransitionEnabled = false;
					Enabled_Test = false;
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

//=======================================================================
// Function to get a random number
//=======================================================================
double Transition_Abstract::Get_Uniform_Distributed_Random_Number()
{
	// std::random_device is a uniformly-distributed integer random number generator that produces non-deterministic random numbers.
	//std::random_device rd;

	// A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
	std::mt19937_64 gen(rd());

	std::uniform_real_distribution<> d(0.0, 1.0);

	return d(gen);
}

//=======================================================================
// Accessor Function to get number of input arcs
//=======================================================================
unsigned int Transition_Abstract::Get_Number_Input_Arcs()
{
	return mNumberInputArcs;
}

//=======================================================================
// Accessor Function to get number of output arcs
//=======================================================================
unsigned int Transition_Abstract::Get_Number_Output_Arcs()
{
	return mNumberOutputArcs;
}

//=======================================================================
// Accessor Function to get number of inhibitor arcs
//=======================================================================
unsigned int Transition_Abstract::Get_Number_Inhibitor_Arcs()
{
	return mNumberInhibitorArcs;
}

//=======================================================================
// Accessor Function to get number of reset arcs
//=======================================================================
unsigned int Transition_Abstract::Get_Number_Reset_Arcs()
{
	return mNumberResetArcs;
}

//=======================================================================
// Accessor Function to get number of inhibitor arcs
//=======================================================================
unsigned int Transition_Abstract::Get_Number_Causal_Arcs()
{
	return mNumberCausalArcs;
}

//=======================================================================
// Accessor Function to get transition fire count
//=======================================================================
unsigned int Transition_Abstract::Get_Transition_Fire_Count()
{
	return mNumberTransitionFires;
}

//=======================================================================
// Accessor Function to get remaining delay before fire
//=======================================================================
double Transition_Abstract::Get_Remaining_Delay()
{
	return mRemainingDelay;
}

//=======================================================================
// Function to print out Transition Properties
//=======================================================================
void Transition_Abstract::Print_Transition_Properties()
{
	// Print out name
	string temp;
	cout << endl << "The properties of " << mTransitionName << " are: " << endl;

	// Prints out specific properties of the transition depending on the transition type
	Transition_Type_Properties();

	// Input Arcs
	cout << "Input Arcs: "; 
	for (unsigned int i = 0; i < mNumberInputArcs; i++)
	{
		temp = mpInputPlaces->at(i)->Get_Place_Name() + " (" + to_string(mpInputWeights->at(i)) + ") ";
		cout << temp;
	}

	// Output Arcs
	cout << endl << "Output Arcs: ";
	for (unsigned int i = 0; i < mNumberOutputArcs; i++)
	{
		temp = mpOutputPlaces->at(i)->Get_Place_Name() + " (" + to_string(mpOutputWeights->at(i)) + ") ";
		cout << temp;
	}
	if (mNumberInhibitorArcs == 0)
	{
		cout << endl << "No Assigned Inhibitor Arcs";
	}

	// Inhibitor Arcs
	else
	{
		cout << endl << "Inhibitor Arcs: ";
		for (unsigned int i = 0; i < mNumberInhibitorArcs; i++)
		{
			temp = mpInhibitorPlaces->at(i)->Get_Place_Name() + " (" + to_string(mpInhibitorWeights->at(i)) + ") ";
			cout << temp;
		}
	}
	cout << endl;
}