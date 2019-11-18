//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Deterministic.cpp - A derived class from the 
// Transition_Abstract base class. Used for deterministic transitions.
//=======================================================================
#include "pch.h"
#include "Transition_Deterministic.h"
//=======================================================================

//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_Deterministic::Transition_Deterministic(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, double Transition_Firing_Delay)
{
	// Transition Properties
	mTransitionName = TransitionName;
	mNumberInputArcs = NumberIn;
	mNumberOutputArcs = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;
	mTransitionCode = 1; // Code is 1 for Deterministic Transitions

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

	mTransitionEnabled = false;
	mTransitionInhibited = false;
	mCumulativeTime = 0.0;
	mRemainingDelay = mTransitionDelay;
}


//=======================================================================
// Used to change/update the firing time of the deterministic transition
//=======================================================================
void Transition_Deterministic::Set_Transition_Delay(double TransitionDelay)
{
	assert(TransitionDelay >= 0);
	mTransitionDelay = TransitionDelay;
}