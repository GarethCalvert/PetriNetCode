//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Stochastic.cpp - Stochastic Transition class, inherits 
// functions from the Transition_Abstract class
//=======================================================================
#include "pch.h"
#include "Transition_BN.h"
using namespace std;
//=======================================================================


//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_BN::Transition_BN(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, unsigned int NumberCausalArcs, unsigned int NumberMarkingPermutations, vector<double> Parameters, double Transition_Firing_Delay)
{
	// Transition Properties
	mTransitionName = TransitionName;
	mNumberInputArcs = NumberIn;
	mNumberOutputArcs = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;
	mNumberCausalArcs = NumberCausalArcs;
	mNumberMarkingPermutations = mNumberMarkingPermutations;
	mTransitionDelay = Transition_Firing_Delay;
	mTransitionCode = 4; // Code is 1 for Deterministic Transitions

	// Initalising Arrays 
	mpInputPlaces = new vector<Place*>[mNumberInputArcs];
	mpOutputPlaces = new vector<Place*>[mNumberOutputArcs];
	mpInhibitorPlaces = new vector<Place*>[mNumberInhibitorArcs];
	mpInputWeights = new vector<unsigned int>[mNumberInputArcs];
	mpOutputWeights = new vector<unsigned int>[mNumberOutputArcs];
	mpInhibitorWeights = new vector<unsigned int>[mNumberInhibitorArcs];


	mpCausalPlaces = new vector<Place*>[mNumberCausalArcs];

	mpCausalStateMarkings = new vector<unsigned int>[mNumberCausalArcs];

	mpConditionalProbabilityValues = new vector<double>[mNumberMarkingPermutations];

	mpCausalStatePermutations = new vector<vector<unsigned int>>(mNumberMarkingPermutations, vector<unsigned int>(mNumberCausalArcs, 1));

	mFireTest = false;
}

//=======================================================================
// Destructor
//=======================================================================
Transition_BN::~Transition_BN()
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
void Transition_BN::Transition_Resample()
{

}

//=======================================================================
// Function samples a new time from the specified distribution for the 
// transition
//=======================================================================
void Transition_BN::Transition_Fire()
{
	// Reset Fire Test
	mFireTest = false;

	// Check what the markings of the causal arcs are
	for (int i = 0; i < mNumberCausalArcs; i++)
	{
		mpCausalStateMarkings->at(i) = mpCausalPlaces->at(i)->Get_Place_Marking();
	}

	bool MarkingDetermined = false;
	int index = 0;
	int MarkingPermutationIndex = 0;
	double SampleProbability;
	double RandomSample;

	// Determining the marking of the causal places
	while (MarkingDetermined == false && index < mNumberMarkingPermutations)
	{
		if (*mpCausalStateMarkings == mpCausalStatePermutations->at(index))
		{
			MarkingPermutationIndex = index;
			MarkingDetermined = true;
		}

		index++;
	}

	if (MarkingDetermined == false)
	{
		cout << "\n Marking not determined for causal places, check to see if sufficient marking permutations are being included.";
	}

	// Determine the correct probability to use given the causal markings
	SampleProbability = mpConditionalProbabilityValues->at(MarkingPermutationIndex);

	// Sample a random number to determine whether the transition should fire in this time step
	RandomSample = Get_Uniform_Distributed_Random_Number();
	if (RandomSample > SampleProbability)
	{
		mFireTest = true;
	}
	else
	{
		mTransitionEnabled = false;
	}

	// If the sampled probability results in a positive result, fire the transition as normal
	if (mFireTest == true)
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
	}

}