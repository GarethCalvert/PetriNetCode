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
Transition_Stochastic::Transition_Stochastic(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, char DistributionCode, unsigned int NumberParameters, vector<double> Parameters)
{
	// Transition Properties
	mTransitionName = TransitionName;
	mNumberInputArcs = NumberIn;
	mNumberOutputArcs = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;

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
		double alpha;
		alpha = mpParameters->at(0);
		mTransitionDelay = -1 * alpha*log(Get_Uniform_Distributed_Random_Number());
	}
	else if (mDistributionCode == 'W')
	{
		double alpha, beta;
		alpha = mpParameters->at(0);
		beta = mpParameters->at(1);
		mTransitionDelay = alpha * pow((-1 * log(Get_Uniform_Distributed_Random_Number())), (1 / beta));
	}

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