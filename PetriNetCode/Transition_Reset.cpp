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
// Transition Fire - Defined for Reset Transition
//=======================================================================
void Transition_Reset::Transition_Fire()
{
	// Transition Resets Marking before firing
	for (int i = 0; i < mNumberResetArcs; i++)
	{
		mpResetPlaces->at(i)->Change_Marking(mpResetWeights->at(i));
	}

	// *** Traditional Transition Fire Onwards ***
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
// Definition for the pure virtual function from Transition_Abstract
//=======================================================================
void Transition_Reset::Transition_Resample()
{
	if (mDistributionCode == 'E')
	{
		mTransitionDelay = -1 * (mpParameters->at(0)) * log(Get_Uniform_Distributed_Random_Number());
	}
	else if (mDistributionCode == 'W')
	{
		double eta, beta;
		// mpParameters->at(0) is the Scale Parameter
		// mpParameters->at(1) is the Shape Parameter
		mTransitionDelay = (mpParameters->at(0)) * pow((-1 * log(Get_Uniform_Distributed_Random_Number())), (1 / (mpParameters->at(1))));
	}
	else if (mDistributionCode == 'N')
	{
		double X = 0.0;
		// mpParameters->at(0) is the Mean
		// mpParameters->at(1) is the SD
		for (int i = 0; i < 12; i++)
		{
			X = +Get_Uniform_Distributed_Random_Number();
		}

		mTransitionDelay = (X - 6) * (mpParameters->at(1)) + mpParameters->at(0);

		while (mTransitionDelay < 0)
		{
			double X = 0.0;
			// mpParameters->at(0) is the Mean
			// mpParameters->at(1) is the SD
			for (int i = 0; i < 12; i++)
			{
				X = +Get_Uniform_Distributed_Random_Number();
			}

			mTransitionDelay = (X - 6) * (mpParameters->at(1)) + mpParameters->at(0);
		}
	}
	else if (mDistributionCode == 'F')
	{
		mTransitionDelay = mpParameters->at(0);
	}

	// Reset of timing variables
	mTransitionEnabled = false;
	mTransitionInhibited = false;
	mCumulativeTime = 0.0;
	mRemainingDelay = mTransitionDelay;
}

//=======================================================================
// Function included here, so that each unique transition type can print
// transition properties out
//=======================================================================
void Transition_Reset::Transition_Type_Properties()
{
	cout << "Reset Transition: " + to_string(mNumberResetArcs) + " Reset Arcs"<<endl;

	cout << "Reset Arcs: ";

	string temp;
	for (unsigned int i = 0; i < mNumberResetArcs; i++)
	{
		temp = mpResetPlaces->at(i)->Get_Place_Name() + " (" + to_string(mpResetWeights->at(i)) + ") ";
		cout << temp;
	}

	cout << endl;

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