#pragma once
#include "Transition_Abstract.h"
class Transition_Deterministic :
	public Transition_Abstract
{
public:
	// Specialised Constructor
	Transition_Deterministic();
	
	// Destructor
	~Transition_Deterministic();

	// Virtual functions from Transition_Abstract that require a definition
	void Transition_Fire();
	void Transition_Resample();
	void Transition_Enabled_Check();

	// Public Functions specific to Transition_Stochastic
	void Set_Transition_Delay(double TransitionDelay);
};

