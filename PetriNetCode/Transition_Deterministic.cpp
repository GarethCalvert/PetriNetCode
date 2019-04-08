#include "pch.h"
#include "Transition_Deterministic.h"

//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_Deterministic::Transition_Deterministic(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, double Transition_Firing_Delay)
{
	// Transition Properties
	mTransitionName = TransitionName;
	mNumberInputPlaces = NumberIn;
	mNumberOutputPlaces = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;

	// Initalising Arrays 
	mpInputPlaces = new vector<Place*>[mNumberInputPlaces];
	mpOutputPlaces = new vector<Place*>[mNumberOutputPlaces];
	mpInhibitorPlaces = new vector<Place*>[mNumberInhibitorArcs];
	mpInputWeights = new vector<unsigned int>[mNumberInputPlaces];
	mpOutputWeights = new vector<unsigned int>[mNumberOutputPlaces];
	mpInhibitorWeights = new vector<unsigned int>[mNumberInhibitorArcs];

	// Reset of timing variables
	mTransitionEnabled = false;
	mTransitionInhibited = false;
	mCumulativeTime = 0.0;
	mTransitionDelay = Transition_Firing_Delay;
	mRemainingDelay = mTransitionDelay;
	
}

//=======================================================================
// Destructor
//=======================================================================
Transition_Deterministic::~Transition_Deterministic()
{
	delete[] mpInputPlaces;
	delete[] mpOutputPlaces;
	delete[] mpInhibitorPlaces;
	delete[] mpInputWeights;
	delete[] mpOutputWeights;
	delete[] mpInhibitorWeights;
}


//=======================================================================
// Resamples transition delay - required from Transition_Abstract
// As this class is deterministic, resampling should do nothing
//=======================================================================
void Transition_Deterministic::Transition_Resample()
{
	// This should do nothing
}


//=======================================================================
// Used to change/update the firing time of the deterministic transition
//=======================================================================
void Transition_Deterministic::Set_Transition_Delay(double TransitionDelay)
{
	assert(TransitionDelay >= 0);
	mTransitionDelay = TransitionDelay;
}