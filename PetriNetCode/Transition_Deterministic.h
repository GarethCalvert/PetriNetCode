//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Deterministic.cpp - A derived class from the 
// Transition_Abstract base class. Used for deterministic transitions.
//=======================================================================
#pragma once
#include "Transition_Abstract.h"
//=======================================================================

class Transition_Deterministic :
	public Transition_Abstract
{
public:
	// Specialised Constructor
	Transition_Deterministic(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, double Transition_Firing_Delay);
	
	// Destructor
	~Transition_Deterministic();

	// Pure virtual functions from Transition_Abstract that require a definition
	void Transition_Resample();

	// Public Functions specific to Transition_Stochastic
	void Set_Transition_Delay(double TransitionDelay);

	// Function to print out properties
	void Transition_Type_Properties();
};

