//=======================================================================
// Gareth Calvert - University of Nottingham
// PetriNetCode.cpp : This file contains the 'main' function. 
//=======================================================================
#include "pch.h"
#include "Petri_Net_Custom.h"

//=======================================================================
// Specialised Constructor
//=======================================================================
Petri_Net_Custom::Petri_Net_Custom(std::string PetriNetName, double InitialTime, double FinalTime)
{
	mPetriNetName = PetriNetName;
	mInitialTime = InitialTime;
	mFinalTime = FinalTime;
	Create_Places_Vector();
	Create_Transitions_Vector();

}

//=======================================================================
// Destructor
//=======================================================================
Petri_Net_Custom::~Petri_Net_Custom()
{

}
