#include "pch.h"
#include "Transition_Deterministic.h"

//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_Deterministic::Transition_Deterministic()
{
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
// Fires the transition when executed
//=======================================================================
void Transition_Deterministic::Transition_Fire()
{
	// Remove Tokens from Input Places
	for (unsigned int i = 0; i < mNumberInputPlaces; i++)
	{
		mpInputPlaces->at(i)->Remove_Tokens(mpInputWeights->at(i));
	}

	// Add Tokens to Output Places
	for (unsigned int i = 0; i < mNumberOutputPlaces; i++)
	{
		mpOutputPlaces->at(i)->Add_Tokens(mpOutputWeights->at(i));
	}
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
// Function used to assess if the marking of the input places mean that 
// the transition is enabled.
//=======================================================================
void Transition_Deterministic::Transition_Enabled_Check()
{

}

//=======================================================================
// Used to change/update the firing time of the deterministic transition
//=======================================================================
void Transition_Deterministic::Set_Transition_Delay(double TransitionDelay)
{
	assert(TransitionDelay >= 0);
	mTransitionDelay = TransitionDelay;
}