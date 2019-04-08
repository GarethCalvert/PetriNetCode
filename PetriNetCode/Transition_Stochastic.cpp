//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Stochastic.cpp - Stochastic Transition class, inherits 
// functions from the Transition_Abstract class
//=======================================================================
#include "pch.h"
#include "Transition_Stochastic.h"

using namespace std;

//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_Stochastic::Transition_Stochastic(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, char DistributionCode, unsigned int NumberParameters, vector<double> Parameters)
{
	mTransitionName = TransitionName;
	mNumberInputPlaces = NumberIn;
	mNumberOutputPlaces = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;

	mDistributionCode = DistributionCode;
	mNumberParameters = NumberParameters;
	mpParameters = new vector<double>[mNumberParameters];
	*mpParameters = Parameters;

	mTransitionEnabled = false;
	mTransitionInhibited = false;

	// Initalising Arrays 
	mpInputPlaces = new vector<Place*>[mNumberInputPlaces];
	mpOutputPlaces = new vector<Place*>[mNumberOutputPlaces];
	mpInhibitorPlaces = new vector<Place*>[mNumberInhibitorArcs];
	mpInputWeights = new vector<unsigned int>[mNumberInputPlaces];
	mpOutputWeights = new vector<unsigned int>[mNumberOutputPlaces];
	mpInhibitorWeights = new vector<unsigned int>[mNumberInhibitorArcs];

	mTransitionEnabled = 0.0;

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
		mTransitionDelay = alpha * pow((-1 * log(randNum)), (1 / beta));
	}

}

//=======================================================================
// Checks if the transition is enabled because of the marking of its 
// input places
//=======================================================================
void Transition_Stochastic::Transition_Enabled_Check()
{
	
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