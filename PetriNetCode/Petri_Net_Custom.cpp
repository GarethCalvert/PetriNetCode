//=======================================================================
// Gareth Calvert - University of Nottingham
// PetriNetCode.cpp : This file contains the 'main' function. 
//=======================================================================
#include "pch.h"
#include "Petri_Net_Custom.h"

//=======================================================================
// Specialised Constructor
//=======================================================================
Petri_Net_Custom::Petri_Net_Custom(std::string PetriNetName, int NumberPlaces, int NumberTransitions,
	std::vector<Place*>* Places, std::vector<Transition_Abstract*>* Transitions, double InitialTime,
	double FinalTime)
{
	mPetriNetName = PetriNetName;
	mNumberPlaces = NumberPlaces;
	mNumberTransitions = NumberTransitions;
	mpPlaces = &*Places;
	mpTransitions = &*Transitions;
	mInitialTime = InitialTime;
	mFinalTime = FinalTime;
	
}

//=======================================================================
// Destructor
//=======================================================================
Petri_Net_Custom::~Petri_Net_Custom()
{

}
