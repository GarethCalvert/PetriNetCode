#include "pch.h"
#include "Transition.h"

// Constructor
Transition::Transition(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs)
{
	mTransitionName = TransitionName;
	mNumberInputPlaces = NumberIn;
	mNumberOutputPlaces = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;
	
	mTransitionEnabled = false;
	mTransitionInhibited = false;

	// Initalising Arrays 
	mpInputPlaces = new vector<Place*>[mNumberInputPlaces];
	mpOutputPlaces = new vector<Place*>[mNumberOutputPlaces];
	mpInputWeights = new vector<unsigned int>[mNumberInputPlaces];
	mpOutputWeights = new vector<unsigned int>[mNumberOutputPlaces];
	mpInhibitorPlaces = new vector<Place*>[mNumberInhibitorArcs];
	mpInhibitorWeights = new vector<unsigned int>[mNumberInhibitorArcs];

	mTransitionEnabled = 0.0;

}

// Destructor
Transition::~Transition()
{
	delete[] mpInputPlaces;
	delete[] mpOutputPlaces;
	delete[] mpInhibitorPlaces;
	delete[] mpInputWeights;
	delete[] mpOutputWeights;
	delete[] mpInhibitorWeights;
}

// Set In Place
void Transition::Set_Input_Place(Place *InPlace, unsigned int InWeight)
{
	mpInputPlaces->push_back(&*InPlace);
	mpInputWeights->push_back(InWeight);
}

// Set Out Place
void Transition::Set_Output_Place(Place *OutPlace, unsigned int OutWeight)
{
	mpOutputPlaces->push_back(&*OutPlace);
	mpOutputWeights->push_back(OutWeight);
}

// Set Distribution Parameters
void Transition::Set_Stochastic_Parameters(char DistributionCode, unsigned int NumberParameters, vector<double> Parameters)
{
	mDistributionCode = DistributionCode;
	mNumberParameters = NumberParameters;
	mpParameters = new vector<double>[mNumberParameters];
	*mpParameters = Parameters;
}

// Sample Transition Delay
void Transition::Sample_Transition_Delay()
{
	// This needs to be made random
	double randNum;
	randNum = 0.5; 

	if (mDistributionCode == 'E')
	{
		double alpha;
		alpha = mpParameters->at(0);
		mTransitionDelay = -1 * alpha*log(randNum);
	}
	else if (mDistributionCode == 'W')
	{
		double alpha, beta;
		alpha = mpParameters->at(0);
		beta = mpParameters->at(1);
		mTransitionDelay = alpha*pow((-1*log(randNum)),(1/beta));
	}

}

// Check if Transition is enabled
void Transition::Transition_Enabled_Check(double GlobalTime)
{
	bool Enabled_Test = true;

	// If Inhibitor Arcs are present, check their status
	if (mNumberInhibitorArcs > 0)
	{
		for (int i = 0; i < mNumberInhibitorArcs; i++)
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
		for (int i = 0; i < mNumberInputPlaces; i++)
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
		for (int i = 0; i < mNumberInputPlaces; i++)
		{
			if (Enabled_Test == true)
			{
				if (mpInputPlaces->at(i)->Get_Place_Marking()<mpInputWeights->at(i))
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

// Transition Fire
void Transition::Fire_Transition()
{
	// Remove Tokens from Input Places
	for (int i = 0; i < mNumberInputPlaces; i++)
	{
		mpInputPlaces->at(i)->Remove_Tokens(mpInputWeights->at(i));
	}

	// Add Tokens to Output Places
	for (int i = 0; i < mNumberOutputPlaces; i++)
	{
		mpOutputPlaces->at(i)->Add_Tokens(mpOutputWeights->at(i));
	}
}

// Return Transition Name
string Transition::Get_Transition_Name()
{
	return mTransitionName;
}

// Return Remaining Firing Time Delay
double Transition::Get_Remaining_Firing_Delay()
{
	return mRemainingDelay;
}

// Return Enabled Status 
bool Transition::Get_Enabled_Status()
{
	return mTransitionEnabled;
}