#pragma once
#include "Transition_Abstract.h"
class Transition_BN : public Transition_Abstract
{
public:
public:
	// Specialised Constructor
	Transition_BN(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, char DistributionCode, unsigned int NumberParameters, vector<double> Parameters);
	// Destructor
	~Transition_BN();

	// Virtual functions from Transition_Abstract that require a definition
	void Transition_Resample();

	// Public Functions specific to Transition_BN
	

private:
	
};

