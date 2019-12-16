//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Stochastic.cpp - Stochastic Transition class, inherits 
// functions from the Transition_Abstract class
//=======================================================================
#include "pch.h"
#include "Transition_Stochastic.h"
using namespace std;
//=======================================================================

//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_Stochastic::Transition_Stochastic(string TransitionName, unsigned int NumberIn, unsigned int NumberOut, unsigned int NumberInhibitorArcs, char DistributionCode, unsigned int NumberParameters, vector<double> Parameters)
{
	// Transition Properties
	mTransitionName = TransitionName;
	mNumberInputArcs = NumberIn;
	mNumberOutputArcs = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;
	mTransitionCode = 2; // Code is 2 for Stochastic Transitions

	// Properties of the probability distribution for sampling times
	mDistributionCode = DistributionCode;
	mNumberParameters = NumberParameters;
	mpParameters = new vector<double>[mNumberParameters];
	*mpParameters = Parameters;
	

	// Initalising Arrays 
	mpInputPlaces = new vector<Place*>[mNumberInputArcs];
	mpOutputPlaces = new vector<Place*>[mNumberOutputArcs];
	mpInhibitorPlaces = new vector<Place*>[mNumberInhibitorArcs];
	mpInputWeights = new vector<unsigned int>[mNumberInputArcs];
	mpOutputWeights = new vector<unsigned int>[mNumberOutputArcs];
	mpInhibitorWeights = new vector<unsigned int>[mNumberInhibitorArcs];

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
Transition_Stochastic::~Transition_Stochastic()
{
	delete[] mpInputPlaces;
	delete[] mpOutputPlaces;
	delete[] mpInhibitorPlaces;
	delete[] mpInputWeights;
	delete[] mpOutputWeights;
	delete[] mpInhibitorWeights;
}

//=======================================================================
// Function samples a new time from the specified distribution for the 
// transition
//=======================================================================
void Transition_Stochastic::Transition_Resample()
{
	if (mDistributionCode == 'E')
	{
		mTransitionDelay = -1 * (mpParameters->at(0))*log(Get_Uniform_Distributed_Random_Number());
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
			X += Get_Uniform_Distributed_Random_Number();
		}

		mTransitionDelay = ((X-6)*(mpParameters->at(1))) + mpParameters->at(0);

		while (mTransitionDelay < 0)
		{
			double X = 0.0;
			// mpParameters->at(0) is the Mean
			// mpParameters->at(1) is the SD
			for (int i = 0; i < 12; i++)
			{
				X += Get_Uniform_Distributed_Random_Number();
			}

			mTransitionDelay = ((X - 6)*(mpParameters->at(1))) + mpParameters->at(0);

		}
	}

	// Reset of timing variables
	mTransitionEnabled = false;
	mTransitionInhibited = false;
	mCumulativeTime = 0.0;
	mRemainingDelay = mTransitionDelay;

}

//=======================================================================
// Function to set the distribution which firing times are sampled from
//=======================================================================
void Transition_Stochastic::Set_Distribution_Parameters(char DistributionCode, unsigned int NumberParameters, vector<double> Parameters)
{
	mDistributionCode = DistributionCode;
	mNumberParameters = NumberParameters;
	mpParameters = new vector<double>[mNumberParameters];
	*mpParameters = Parameters;
}

//=======================================================================
// Function included here, so that each unique transition type can print
// transition properties out
//=======================================================================
void Transition_Stochastic::Transition_Type_Properties()
{
	if (mDistributionCode == 'E')
	{
		cout << "Stochastic Transition: Exponential Distribution" << endl;
		cout << "Parameters: " + to_string(mpParameters->at(0)) << endl;
	}
	else if (mDistributionCode == 'W')
	{
		cout << "Stochastic Transition: Weibull Distribution" << endl;
		cout << "Parameters: " + to_string(mpParameters->at(0)) + ", "+ to_string(mpParameters->at(1)) << endl;
	}
	else if (mDistributionCode == 'N')
	{
		cout << "Stochastic Transition: Normal Distribution" << endl;
		cout << "Parameters: " + to_string(mpParameters->at(0)) + ", " + to_string(mpParameters->at(1)) << endl;
	}

}