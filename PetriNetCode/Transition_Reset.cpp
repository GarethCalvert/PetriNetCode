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
Transition_Reset::Transition_Reset()
{
	mNumberResetArcs = 1; // needs changed to an input variable
	mTransitionCode = 3; // Code is 1 for Deterministic Transitions
}

//=======================================================================
// Destructor
//=======================================================================
Transition_Reset::~Transition_Reset()
{

}

//=======================================================================
// Definition for the pure virtual function from Transition_Abstract
//=======================================================================
void Transition_Reset::Transition_Resample()
{

}