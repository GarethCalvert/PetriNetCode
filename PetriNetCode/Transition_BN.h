#pragma once
#include "Transition_Abstract.h"
class Transition_BN : public Transition_Abstract
{
public:
public:
	// Specialised Constructor
	Transition_BN(string TransitionName, unsigned int NumberIn, unsigned int NumberOut, unsigned int NumberInhibitorArcs, unsigned int NumberCausalArcs, unsigned int NumberMarkingPermutations, vector<double> Parameters, double Transition_Firing_Delay);
	// Destructor
	~Transition_BN();

	// Virtual functions from Transition_Abstract that require a definition
	void Transition_Resample();

	void Transition_Fire();

	// Public Functions specific to Transition_BN
	

private:

	// Distribution Variables
	unsigned int mNumberMarkingPermutations;
	vector<Place*>* mpCausalPlaces;
	vector<unsigned int>* mpCausalStateMarkings;
	vector<vector<unsigned int>>* mpCausalStatePermutations;
	vector<double>* mpConditionalProbabilityValues;
	
	bool mFireTest;
	
};

