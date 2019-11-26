//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Reset.h - Reset Transition header file -- it is a 
// derived class from Transition_Abstract
//=======================================================================
#include "pch.h"
#include "Transition_Reset.h"
//=======================================================================


//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_Reset::Transition_Reset(string TransitionName, unsigned int NumberIn, unsigned int NumberOut, unsigned int NumberInhibitorArcs, unsigned int NumberResetArcs, char DistributionCode, unsigned int NumberParameters, vector<double> Parameters)
{
	

	// Transition Properties
	mTransitionName = TransitionName;
	mNumberInputArcs = NumberIn;
	mNumberOutputArcs = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;
	mNumberResetArcs = NumberResetArcs;
	mTransitionCode = 3; // Code is 3 for Reset Transitions

	// Properties of the probability distribution for sampling times
	mDistributionCode = DistributionCode;
	mNumberParameters = NumberParameters;
	mpParameters = new vector<double>[mNumberParameters];
	*mpParameters = Parameters;

	// Initalising Arrays 
	mpInputPlaces = new vector<Place*>[mNumberInputArcs];
	mpOutputPlaces = new vector<Place*>[mNumberOutputArcs];
	mpInhibitorPlaces = new vector<Place*>[mNumberInhibitorArcs];
	mpResetPlaces = new vector<Place*>[mNumberResetArcs];
	mpInputWeights = new vector<unsigned int>[mNumberInputArcs];
	mpOutputWeights = new vector<unsigned int>[mNumberOutputArcs];
	mpInhibitorWeights = new vector<unsigned int>[mNumberInhibitorArcs];
	mpResetWeights = new vector<unsigned int>[mNumberResetArcs];

	// Reset of timing variables
	mTransitionEnabled = false;
	mTransitionInhibited = false;
	mCumulativeTime = 0.0;
	Transition_Resample();
	mRemainingDelay = mTransitionDelay;
}

//=======================================================================
// Destructor
//=======================================================================
Transition_Reset::~Transition_Reset()
{
	delete[] mpInputPlaces;
	delete[] mpOutputPlaces;
	delete[] mpInhibitorPlaces;
	delete[] mpResetPlaces;
	delete[] mpInputWeights;
	delete[] mpOutputWeights;
	delete[] mpInhibitorWeights;
	delete[] mpResetWeights;
}

//=======================================================================
// Definition for the pure virtual function from Transition_Abstract
//=======================================================================
void Transition_Reset::Transition_Resample()
{

}

//=======================================================================
// Function included here, so that each unique transition type can print
// transition properties out
//=======================================================================
void Transition_Reset::Transition_Type_Properties()
{
	cout << "Reset Transition: " + to_string(mNumberResetArcs) + " Reset Arcs"<<endl;

	if (mDistributionCode == 'E')
	{
		cout << "Time Properties: Exponential Distribution" << endl;
		cout << "Parameters: " + to_string(mpParameters->at(0)) << endl;
	}
	else if (mDistributionCode == 'W')
	{
		cout << "Time Transition: Weibull Distribution" << endl;
		cout << "Parameters: " + to_string(mpParameters->at(0)) + ", " + to_string(mpParameters->at(1)) << endl;
	}
	else if (mDistributionCode == 'N')
	{
		cout << "Time Transition: Normal Distribution" << endl;
		cout << "Parameters: " + to_string(mpParameters->at(0)) + ", " + to_string(mpParameters->at(1)) << endl;
	}
	else if (mDistributionCode == 'F')
	{
		cout << "Time Transition: Fixed Time" << endl;
		cout << "Delay Size: " + to_string(mpParameters->at(0)) << endl;
	}

}